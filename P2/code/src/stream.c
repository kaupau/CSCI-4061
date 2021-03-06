#include "stream.h"

/**
 * read lines from input file and write each line to pipes
 * each line will contain words as in Project 1 (Use STDOUT for writing)
 */
void emit(char * inputFileName) {
    FILE* inputFile = getFilePointer(inputFileName);
    if(inputFile == NULL) {
        printf("Failed to open file\n");
    }
    char line[maxFileNameLength];
    while( getLineFromFile(inputFile, line, maxFileNameLength) != -1 ) {
        // send the words to pipes
        // STDOUT redirection to write the data into pipes
        // fprintf(stderr, "Printing to stderr from stream %d, working with line %s\n",mapperID,line);
        fprintf(stdout, "%s", line);
    }
    fclose(inputFile);
}
/***
 *
 * Stream process will read from the files created by Master
 */
int main(int argc, char *argv[]) {

    mapperID = strtol(argv[1], NULL, 10);
    int nMappers = strtol(argv[2], NULL, 10);

    // printf("Printing to stdout from stream %d\n",mapperID);

    char filename[maxFileNameLength];
    sprintf(filename,"MapperInput/Mapper%d.txt", mapperID);
    FILE *mapperFile = getFilePointer(filename);
    // printf("Reading from %s\n",filename);

    char line[maxFileNameLength];
    while( getLineFromFile(mapperFile, line, maxFileNameLength) != -1 ) {
        line[strlen(line)-1] = '\0';
        emit(line);
    }

    //TODO: Read lines from Mapper files and get the file names that will be processes in emit function
    //Each MapperInput/MapperID.txt file will contain file names
    // example of one line will be test/T1/subfolder/0.txt
    fclose(mapperFile);
    return EXIT_SUCCESS;
}