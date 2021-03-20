#include "mapreduce.h"

char** getTxtFiles(char* path, char** txtFileBuffer);

int isTxtFile(char* filename);

char* constructPath(char* pathto, char* filename);

char* intToString(int n);

void waitForAll(int num) {
	pid_t pid_child;
	for(int i=0; i<num; i++) {
		pid_child = wait(NULL);
		if(pid_child < 0) {
			printf("Waited for non-existant child\n");
			exit(EXIT_FAILURE);
		}
		printf("mapreduce has waited for %d of %d childs\n",i+1,num);
	}
}


int main(int argc, char *argv[]) {

	if(argc < 4) {
		printf("Incorrect number of arguments\n");
		exit(EXIT_FAILURE);
	}

	int nMappers 	= strtol(argv[1], NULL, 10);
	int nReducers 	= strtol(argv[2], NULL, 10);

	if( nMappers < 1 || nReducers < 1) {
		printf("Number of mappers or reducers must be at least 1 each\n");
		exit(EXIT_FAILURE);
	}

	inputFileDir = argv[3];
	if(!isValidDir(inputFileDir))
		exit(EXIT_FAILURE);

	bookeepingCode();

	//TODO: Traverse Input File Directory (Hint: Recursively find all the text files inside directory)
	// and create MapperInput directory which will contain MapperID.txt files
	char* txtFiles[MaxNumInputFiles];
	getTxtFiles(inputFileDir, txtFiles);

	if(mkdir("MapperInput",0777) < 0) {
		printf("Making MapperInput folder failed, try make clean\n");
	}

	FILE** mapperIDtxtfiles = malloc(nMappers * sizeof(FILE*));
	char* filepath;
	char filename[maxFileNameLength];
	for(int i = 0; i < nMappers; i++) {
		sprintf(filename, "Mapper%d.txt",i+1);
		filepath = constructPath("MapperInput",filename);
		mapperIDtxtfiles[i] = fopen(filepath,"w");
		free(filepath);
	}

	printf("\nWriting to Mapper_xx.txt files...\n");
	int mapperID = 0;
	for(char** txtname = txtFiles; *txtname != NULL; txtname++) {
		printf("\t%s assigned to mapper mapperID %d\n",*txtname, mapperID+1);
		fprintf(mapperIDtxtfiles[mapperID],"%s\n",*txtname);
		free(*txtname);
		mapperID = (mapperID + 1)%nMappers;
	}

	for(int i = 0; i < nMappers; i++) {
		fclose(mapperIDtxtfiles[i]);
	}
	free(mapperIDtxtfiles);

	//TODO: spawn stream processes
	int pipefds[nMappers][2];

	for(int i = 0; i < nMappers; i++) {
		if(pipe(pipefds[i]) < 0) {
			printf("Pipe creation failed\n");
			exit(0);
		}
		pid_t pid = fork();
		if(pid == 0) {
			int stdout = dup(1); // save stdout just in case
			dup2(pipefds[i][1],1); // dup write end of pipe
			close(pipefds[i][0]); // close read end of pipe
			for(int j = 0; j < nMappers; j++) { // close all other pipes
				if(j!=i) {
					close(pipefds[j][0]);
					close(pipefds[j][1]);
				}
			}

			execl("./stream","./stream",intToString(i+1),intToString(nMappers),NULL);
			dup2(stdout,1);
			printf("Exec stream failed\n"); exit(0);
		}
	}

	// TODO: spawn mappers
	for(int i = 0; i < nMappers; i++) {
		pid_t pid = fork();
		if(pid == 0) {
			dup2(pipefds[i][0],0); // dup read end of pipe to stdin
			close(pipefds[i][1]); // close write end of pipe
			for(int j = 0; j < nMappers; j++) { // close all other pipes
				if(j!=i) {
					close(pipefds[j][0]);
					close(pipefds[j][1]);
				}
			}

			execl("./mapper","./mapper",intToString(i+1),NULL);
			printf("Exec mapper failed\n"); exit(0);
		}
	}

	for(int i = 0; i < nMappers; i++) {
		close(pipefds[i][0]);
		close(pipefds[i][1]);
	}

	// TODO: wait for all children to complete execution
	waitForAll(nMappers*2); // waiting for both mappers and streams
	printf("\nDone\n\n");

	// TODO: spawn reducers

	// TODO: wait for all children to complete execution

	return EXIT_SUCCESS;
}


char** getTxtFiles(char* path, char** txtFileBuffer) {
	DIR* dr = opendir(path);
	if(dr == NULL) {
		printf("Directory failed to open\n");
		exit(0);
	}
	printf("Opened directory %s\n",path);
	struct dirent* de;
	while((de = readdir(dr)) != NULL) {
		if(de->d_type == DT_DIR) {
			printf("\tDirectory: %s\n",de->d_name);
			if(de->d_name[0]=='.') {
				if(strlen(de->d_name)==1) { continue; }
				if(strlen(de->d_name)==2 && de->d_name[1]=='.') { continue; }
			}
			char* newpath = constructPath(path,de->d_name);
			txtFileBuffer = getTxtFiles(newpath, txtFileBuffer);
			free(newpath);
		} else {
			printf("\tFile: %s\n",de->d_name);
			if(isTxtFile(de->d_name)) {
				printf("\tTxt file found\n");
				*txtFileBuffer = malloc(maxFileNameLength * sizeof(char));
				(*txtFileBuffer)[0] = '\0';
				char* newpath = constructPath(path,de->d_name);
				strcat(*txtFileBuffer,newpath);
				free(newpath);
				printf("\tSaved filename: %s\n",*txtFileBuffer);
				txtFileBuffer++;
			}
		}
	}
	*txtFileBuffer = NULL;
	return txtFileBuffer;
}

int isTxtFile(char* filename) {
	int nameLen = strlen(filename);
	return (filename[nameLen-1]=='t' && filename[nameLen-2]=='x' && filename[nameLen-3]=='t' && filename[nameLen-4]=='.');
}

char* constructPath(char* pathto, char* filename) {
	char* newpath = malloc((strlen(pathto)+strlen(filename)+5) * sizeof(char));
	newpath[0] = '\0';
	char path_delimiter[] = "/";
	strncat(newpath,pathto,strlen(pathto));
	strncat(newpath,path_delimiter,1);
	strncat(newpath,filename,strlen(filename));
	return newpath;
}

char* intToString(int n) {
	char* output = malloc(64 * sizeof(char));
	sprintf(output, "%d",n);
	return output;
}

