#ifndef PRODUCER_H
#define PRODUCER_H

#include "utils.h"

void *producer(void *arg);

struct producerArgs {
    char* filename;
    struct sharedBuffer* buffer;
};

struct globalHistogram {
    int histogram[MaxWordLength];
    pthread_mutex_t* mutex;
};

struct globalHistogram* globHist;

#endif