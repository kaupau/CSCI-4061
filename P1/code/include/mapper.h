#ifndef MAPPER_H
#define MAPPER_H

#include "utils.h"

int mapperID;
char *inputFileDir;
char *intermediateDir = "output/IntermediateData";
int interDS[MaxWordLength] = {0}; // want to initialize array to all zeros

void map(char * inputFileName);

#endif
