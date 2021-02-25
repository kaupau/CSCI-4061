#ifndef REDUCER_H
#define REDUCER_H

#include "utils.h"

int reducerID;
char *intermediateDir = "output/IntermediateData";
char *finalDir = "output/FinalData";
int finalDS[MaxWordLength+1] = {0}; // want to initialize array to all zeros

void reduce(char *key);

#endif