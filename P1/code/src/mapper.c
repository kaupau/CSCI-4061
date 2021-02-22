#include "mapper.h"

/**
 * Write word count that is stored in a intermeidate data structure to files.
 * The file should be in a corresponding folder in output/IntermediateData/ 
 */
void writeInterDSToFiles(void) {
  char outputFilePath[2*maxFileNameLength] = "";
  char outputFileFolder[maxFileNameLength] = "";
  char outputFileName[maxFileNameLength] = "";
  sprintf(outputFileName, "/m%d.txt", mapperID);
  printf("Mapper %d final DS:\n",mapperID);
  for(int i = 0; i < MaxWordLength;i++) {
    if(interDS[i] > 0) {
      strcpy(outputFilePath,intermediateDir);
      sprintf(outputFileFolder, "/%d", i+1);
      strcat(outputFilePath,outputFileFolder);
      strcat(outputFilePath,outputFileName);
      printf("Writing to file: %s\n",outputFilePath);
      FILE* outputFile = fopen(outputFilePath,"w");

      fprintf(outputFile,"%d %d",i+1,interDS[i]);

      fclose(outputFile);

      printf("Length: %d Num: %d\n",i+1,interDS[i]);
    }
  }
}

/**
 * Read lines from files, and count words by word length
 */
void map(char * inputFileName) {
  FILE* inputFile = getFilePointer(inputFileName);
  int charIn;

  int wordSize = 0;
  while(1) {
    if(feof(inputFile))
      break;

    charIn = fgetc(inputFile);
    if(charIn == ' ' || charIn == '\n' || feof(inputFile)) {
      if(wordSize > 0) {
        //printf("Writing word of size %d\n",wordSize);
        interDS[wordSize-1] += 1;
        wordSize = 0;
      }
    } else {
    wordSize++;
    }
  }

}

int main(int argc, char *argv[]) {

    mapperID = strtol(argv[1], NULL, 10);
    int nMappers = strtol(argv[2], NULL, 10);
    inputFileDir = argv[3];

    //getMapperTasks function returns a list of input file names that this mapper should process
    char *myTasks[MaxNumInputFiles] = {NULL};
    int nTasks = getMapperTasks(nMappers, mapperID, inputFileDir, &myTasks[0]);

    printf("In mapper %d of %d with %d tasks\n",mapperID,nMappers,nTasks);

    int tIdx;
    for (tIdx = 0; tIdx < nTasks; tIdx++) {
        printf("mapper[%d] - %s\n", mapperID, myTasks[tIdx]);
        map(myTasks[tIdx]);
        free(myTasks[tIdx]);
    }

    writeInterDSToFiles();

    return EXIT_SUCCESS;
}
