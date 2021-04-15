#ifndef CONSUMER_H
#define CONSUMER_H

#include "utils.h"

void *consumer(void *arg);

struct consumerArgs {
    int consumerID;
    struct sharedBuffer* buffer;
    // struct globalHistogram* globalHist;
};

#endif