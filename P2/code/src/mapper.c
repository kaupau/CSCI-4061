#include "mapper.h"

/**
 * Write word count that is stored in an intermediate data structure to files.
 * The file should be in a corresponding folder in output/IntermediateData/ 
 */
void writeInterDSToFiles(void) {
}

/**
 * parse lines from pipes, and count words by word length
 */
void parse(char * line) {
}

int main(int argc, char *argv[]) {

    mapperID = strtol(argv[1], NULL, 10);
printf("In mapper %d\n",mapperID);
exit(0);

    // you can read lines from pipes (from STDIN) (read lines in a while loop)
    // feel free to change
    while(1) {
        parse("test");
    }

    writeInterDSToFiles();

    return EXIT_SUCCESS;
}
