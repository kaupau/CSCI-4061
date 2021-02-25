#include "reducer.h"

/**
 * Write final word count to files.
 * The file should be in a corresponding folder in output/FinalData/ 
 */
void writeFinalDSToFiles(void) {
    // create file descriptor
    char outputFileName[maxFileNameLength] = "";
    FILE* outputFile;

    // for every word length in our data structure, create a new file and put the word count on it
    for(int wordLength = 0; wordLength <= MaxWordLength; wordLength++) {
        if(finalDS[wordLength] > 0) {
            // format the file path name
            sprintf(outputFileName, "%s/%d.txt", finalDir, wordLength);
            outputFile = fopen(outputFileName,"w");

            // format the file path name
            fprintf(outputFile, "%d %d", wordLength, finalDS[wordLength]);
            fclose(outputFile);
        }
    }
}


/**
 * Read lines from files, and calculate a total count for a specific word length
 */
void reduce(char * intermediateFileName) {
    FILE* inputFile = getFilePointer(intermediateFileName);

    int wordLength;
    int count = 0;

    char line[maxFileNameLength];
    getLineFromFile(inputFile, line, maxFileNameLength);
    
    // Split the line into the word length and it's corresponding count
    char *lineSplitter;
    lineSplitter = strtok(line, " ");
    wordLength = strtol(lineSplitter, NULL, 10);
    lineSplitter = strtok(NULL, " ");
    count = strtol(lineSplitter, NULL, 10);        

    fclose(inputFile);
    finalDS[wordLength] += count;     // stores the total count for a particular word length in an intermediate structure
}

int main(int argc, char *argv[]) {
    if(argc != 3) {
      printf("Reducer received incorrect number of arguments\n");
      return -1;
    }
	  // initialize 
	  reducerID = strtol(argv[1], NULL, 10);
	  int nReducers = strtol(argv[2], NULL, 10);

    //getReducerTasks function returns a list of intermediate file names that this reducer should process
    char *myTasks[MaxNumIntermediateFiles] = {NULL};
    int nTasks = getReducerTasks(nReducers, reducerID, intermediateDir, &myTasks[0]);

    int tIdx;
    for (tIdx = 0; tIdx < nTasks; tIdx++) {
        printf("reducer[%d] - %s\n", reducerID, myTasks[tIdx]);
        reduce(myTasks[tIdx]);
        free(myTasks[tIdx]);
    }

    writeFinalDSToFiles();

	return EXIT_SUCCESS;
}
