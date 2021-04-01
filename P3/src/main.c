#include "header.h"
#include "semaphore.h"

/**
 * Write final word count to a single file.
 * The path name should be output/result.txt
 */
void writeFinalDSToFiles(void) {
}

int main(int argc, char *argv[]){
    
    //TODO: Argument check

    bookeepingCode();
    
    //TODO: Initialize global variables, like shared queue, histogram
    

    //TODO: create producer and consumer threads
    pthread_t producerThread;
    pthread_t consumerThread;
    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    //TODO: wait for all threads to complete execution
    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);
    
    //Write the final output
    writeFinalDSToFiles();
    
    return 0; 
}