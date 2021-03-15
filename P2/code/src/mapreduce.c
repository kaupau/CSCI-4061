#include "mapreduce.h"

char** getTxtFiles(char* path, char** txtFileBuffer);

int main(int argc, char *argv[]) {

	//TODO: number of argument check

	int nMappers 	= strtol(argv[1], NULL, 10);
	int nReducers 	= strtol(argv[2], NULL, 10);

	inputFileDir = argv[3];
	if(!isValidDir(inputFileDir))
		exit(EXIT_FAILURE);

	bookeepingCode();

	//TODO: Traverse Input File Directory (Hint: Recursively find all the text files inside directory)
	// and create MapperInput directory which will contain MapperID.txt files
	char* txtFiles[MaxNumInputFiles];
	getTxtFiles(inputFileDir, txtFiles);
	printf("\n\nFinal array of txt files:\n");
	char** txtname = txtFiles;
	while(*txtname != NULL) {
		printf("\t%s\n",*txtname);
		txtname++;
	}
	printf("Done\n\n");
	//TODO: spawn stream processes

	// TODO: spawn mappers	

	// TODO: wait for all children to complete execution

	// TODO: spawn reducers

	// TODO: wait for all children to complete execution

	return EXIT_SUCCESS;
}

int isTxtFile(char* filename);

char* constructPath(char* pathto, char* filename);

char** getTxtFiles(char* path, char** txtFileBuffer) {
	DIR* dr = opendir(path);
	if(dr == NULL) {
		printf("Directory failed to open\n");
		return 0;
	}
	printf("Opened directory %s\n",path);
	struct dirent* de;
	while((de = readdir(dr)) != NULL) {
		if(de->d_type == DT_DIR) {
			printf("Directory: %s\n",de->d_name);
			if(de->d_name[0]=='.') {
				if(strlen(de->d_name)==1) { continue; }
				if(strlen(de->d_name)==2 && de->d_name[1]=='.') { continue; }
			}
			char* newpath = constructPath(path,de->d_name);
			txtFileBuffer = getTxtFiles(newpath, txtFileBuffer);
			free(newpath);
		} else {
			printf("File: %s\n",de->d_name);
			if(isTxtFile(de->d_name)) {
				printf("Txt file found\n");
				*txtFileBuffer = malloc(maxFileNameLength * sizeof(char));
				(*txtFileBuffer)[0] = '\0';
				char* newpath = constructPath(path,de->d_name);
				strcat(*txtFileBuffer,newpath);
				free(newpath);
				printf("Saved filename: %s\n",*txtFileBuffer);
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


