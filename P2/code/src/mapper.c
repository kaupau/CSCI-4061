#include "mapper.h"

/**
 * Write word count that is stored in an intermediate data structure to files.
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


int main(int argc, char *argv[]) {

    if(argc != 2) {
      printf("Mapper received incorrect number of arguments\n");
      return -1;
    }

    mapperID = strtol(argv[1], NULL, 10);
    printf("In mapper %d\n",mapperID);
    int charIn = 1; // for storing characters read from file
    int wordSize = 0; // for keeping track of length of the current word

    // you can read lines from pipes (from STDIN) (read lines in a while loop)
    // feel free to change
    while(1) {
        if(charIn <= 0) // break when stdin is closed
            break;
        charIn = getchar();
        printf("Mapper %d got %c\n", mapperID, ((char)charIn));
        if(charIn == ' ' || charIn == '\n' || charIn <= 0) {
          if(wordSize > 0) {
            // element i-1 of interDS corresponds to words of length i
            interDS[wordSize-1] += 1;
            wordSize = 0;
          }
        } else {
          wordSize++;
        }
    }

    writeInterDSToFiles();

    return EXIT_SUCCESS;
}
