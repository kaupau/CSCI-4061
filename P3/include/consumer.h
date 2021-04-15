#ifndef CONSUMER_H
#define CONSUMER_H

#include "utils.h"

void *consumer(void *arg);

struct consumerArgs {
    int consumerID;
    struct sharedBuffer* buffer;
    int* globalHist;
    pthread_mutex_t* globalHistMutex;
};

#endif
