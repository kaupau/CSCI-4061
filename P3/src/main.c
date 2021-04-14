#include "header.h"
#include "semaphore.h"

/**
 * Write final word count to a single file.
 * The path name should be output/result.txt
 */
void writeFinalDSToFiles(void) {
}

int main(int argc, char *argv[]){
    
    // Argument check
    if(argc < 3) {
		printf("Incorrect number of arguments\n");
		exit(EXIT_FAILURE);
	}

    int nConsumers 	= strtol(argv[1], NULL, 10);
    char *inputFile = argv[2];
    // TODO: OPTIONS, is there any built in parser option for flags??
    char *options   = argv[3];   
    
    bookeepingCode();
    
    //TODO: Initialize global variables, like shared queue, histogram


    // Create producer and consumer threads
    pthread_t producerThread;
    pthread_t consumerThread;
    pthread_create(&producerThread, NULL, producer, NULL);
    for(int i = 0; i < nConsumers; i++) {
        pthread_create(&consumerThread, NULL, consumer, NULL);
    }

    // Wait for all threads to complete execution
    pthread_join(producer, NULL);
    for(int i = 0; i < nConsumers; i++) {
        pthread_join(consumer, NULL);
    }
    
    //Write the final output
    writeFinalDSToFiles();
    
    return 0; 
}