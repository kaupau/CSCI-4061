#include "utils.h"

void writeLineToFile(char *filepath, char *line) {
    int fd = open(filepath, O_CREAT | O_WRONLY, 0777);
    if (fd < 0){
        printf("ERROR: Cannot open the file %s\n", filepath);
        fflush(stdout);
        exit(EXIT_FAILURE);
    }
    int ret = write(fd, line, strlen(line));
    if(ret < 0){
        printf("ERROR: Cannot write to file %s\n", filepath);
        fflush(stdout);
        exit(EXIT_FAILURE);
    }
}

FILE * getFilePointer(char *inputFileName) {
    return fopen(inputFileName, "r");
}

ssize_t getLineFromFile(FILE *fp, char *line, size_t len) {
    memset(line, '\0', len);
    return getline(&line, &len, fp);
}

//TODO
// return: The number of intermediate files the reducer should process
// The list of intermediate file names are stored in myTasks array
char* intToString(int n) {
	char* output = malloc(64 * sizeof(char));
	sprintf(output, "%d",n);
	return output;
}

int getReducerTasks(int nReducers, int reducerID, char *intermediateDir, char **myTasks) {
    // nAllTasks / nReducers = tasks per each reducer
    int nAllTasks = 0;
    char *allTasks[20] = {NULL};
    for(int i = 1; i < MaxWordLength; i++) {
        char filename[maxFileNameLength];
        strcpy(filename, intermediateDir);
        strcat(filename, "/");
        strcat(filename, intToString(i));
        DIR *dir = opendir(filename);
        struct dirent *de;

        de = readdir(dir);
        while( (de = readdir(dir)) != NULL ) {
            if( strcmp(de->d_name, "..") != 0 && strcmp(de->d_name, ".") != 0 ) {
                char newFilename[maxFileNameLength];
                strcpy(newFilename, filename);
                strcat(newFilename, "/");
                strcat(newFilename, de->d_name);
                
                allTasks[nAllTasks] = malloc(sizeof(char)*maxFileNameLength);
                strcpy(allTasks[nAllTasks], newFilename);

                nAllTasks++;
            } 
        }
    }
    
    int nTasks = floor(nAllTasks / nReducers);
    int j = 0;
    if(reducerID==nReducers) {
        for(int i = nTasks*(reducerID-1); i < nAllTasks; i++) {
            // printf("Task: %d \t%s\n", i, allTasks[i]);
            myTasks[j] = malloc(sizeof(char)*maxFileNameLength);
            strcpy(myTasks[j], allTasks[i]);
            j++;
        }
    } else {
        for(int i = nTasks*(reducerID-1); i < nTasks*(reducerID-1)+nTasks; i++) {
            // printf("Task: %d \t%s\n", i, allTasks[i]);
            myTasks[j] = malloc(sizeof(char)*maxFileNameLength);
            strcpy(myTasks[j], allTasks[i]);
            j++;
        }
    }

    return nTasks;
}

//TODO: traverse inputfile directory and create MapperInput directory
void traverseFS(int mappers, char *path){

}

int isValidDir(char *folder) {
    struct stat sb;
    return (stat(folder, &sb) == 0 && S_ISDIR(sb.st_mode));
}

void _removeOutputDir(){
    pid_t pid = fork();
    if(pid == 0){
        char *argv[] = {"rm", "-rf", "output", NULL};
        if (execvp(*argv, argv) < 0) {
            printf("ERROR: exec failed\n");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    } else{
        wait(NULL);
    }
}

void _createOutputDir(){
    mkdir("output", ACCESSPERMS);
    mkdir("output/IntermediateData", ACCESSPERMS);
    mkdir("output/FinalData", ACCESSPERMS);
}

void _createInterFolders(){
    int wordLen;
    for(wordLen = 1; wordLen <= MaxWordLength; wordLen++) {
        char dirName[50];
        memset(dirName, '\0', 50);
        sprintf(dirName, "output/IntermediateData/%d", wordLen);
        mkdir(dirName, ACCESSPERMS);
    }
}

void bookeepingCode(){
    _removeOutputDir();
    sleep(1);
    _createOutputDir();
    _createInterFolders();
}