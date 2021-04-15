#ifndef HEADER_H
#define HEADER_H

#include "utils.h"
#include "producer.h"
#include "consumer.h"

char *finalDir = "output/result.txt";
char *logDir = "output/log.txt";

pthread_mutex_t globalHistMutex;
int globalHist[MaxWordLength] = {0};

#endif
