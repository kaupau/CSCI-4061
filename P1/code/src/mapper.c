#include "mapper.h"

/**
 * Write word count that is stored in a intermediate data structure to files.
 * The file should be in a corresponding folder in output/IntermediateData/ 
 */
void writeInterDSToFiles(void) {
  char outputFilePath[2*maxFileNameLength] = "";
  char outputFileFolder[maxFileNameLength] = "";
  char outputFileName[maxFileNameLength] = "";
  // name of file for this mapper is always the same
  sprintf(outputFileName, "/m%d.txt", mapperID);

  for(int i = 0; i < MaxWordLength;i++) {
    if(interDS[i] > 0) {
      // construct path to output file
      strcpy(outputFilePath,intermediateDir);
      sprintf(outputFileFolder, "/%d", i+1);
      strcat(outputFilePath,outputFileFolder);
      strcat(outputFilePath,outputFileName);
      
      // write word length and number of words
      FILE* outputFile = fopen(outputFilePath,"w");
      if(outputFile == NULL) {
        printf("Error when opening output file %s\n",outputFilePath);
        continue;
      }
      fprintf(outputFile,"%d %d",i+1,interDS[i]);
      fclose(outputFile);
    }
  }
}

/**
 * Read lines from files, and count words by word length
 */
void map(char * inputFileName) {
  FILE* inputFile = getFilePointer(inputFileName);
  int charIn; // for storing characters read from file

  int wordSize = 0; // for keeping track of length of the current word
  // loop through every character in the file
  while(1) {
    if(feof(inputFile)) // break when end of file reached
      break;

    charIn = fgetc(inputFile); // gets a single character from file
    // a word has ended when a space or a newline has been reached
    if(charIn == ' ' || charIn == '\n' || feof(inputFile)) {
      if(wordSize > 0) {
        // element i-1 of interDS corresponds to words of length i
        interDS[wordSize-1] += 1;
        wordSize = 0;
      }
    } else {
    wordSize++;
    }
  }

  fclose(inputFile);

}

int main(int argc, char *argv[]) {

    if(argc != 4) {
      printf("Mapper received incorrect number of arguments\n");
      return -1;
    }
    mapperID = strtol(argv[1], NULL, 10);
    int nMappers = strtol(argv[2], NULL, 10);
    inputFileDir = argv[3];
    if(!isValidDir(inputFileDir)) {
        printf("Input file directory is invalid\n");
        exit(EXIT_FAILURE);
    }

    //getMapperTasks function returns a list of input file names that this mapper should process
    char *myTasks[MaxNumInputFiles] = {NULL};
    int nTasks = getMapperTasks(nMappers, mapperID, inputFileDir, &myTasks[0]);

    int tIdx;
    for (tIdx = 0; tIdx < nTasks; tIdx++) {
        printf("mapper[%d] - %s\n", mapperID, myTasks[tIdx]);
        map(myTasks[tIdx]);
        free(myTasks[tIdx]);
    }

    writeInterDSToFiles();

    return EXIT_SUCCESS;
}
