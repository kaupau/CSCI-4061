#include "header.h"
#include "semaphore.h"

/**
 * Write final word count to a single file.
 * The path name should be output/result.txt
 */
void writeFinalDSToFiles(void) {
    FILE* outputFile;
    outputFile = fopen("output/result.txt","w");
    fprintf(outputFile, "a a");
    fclose(outputFile);
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
    writeFinalDSToFiles();
    //TODO: Initialize global variables, like shared queue, histogram
    // Shared Queue
    struct sharedBuffer* buffer = (struct sharedBuffer*) malloc(sizeof(struct sharedBuffer));
    buffer->mutex = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
    buffer->cond = (pthread_cond_t*) malloc(sizeof(pthread_cond_t));
    pthread_mutex_init(buffer->mutex, NULL);
    pthread_cond_init(buffer->cond, NULL);
    buffer->head = NULL;
    buffer->bufferLen = 0;
    // Global Histogram
    for(int i = 0; i < MaxWordLength+1; i++) {
        buffer->histogram[i] = 0;
    }
    EOFStatus = 1;

    // Create producer and consumer threads
    struct producerArgs* pArgs = malloc(sizeof(struct producerArgs));
    *pArgs = (struct producerArgs) {inputFile, buffer};
    
    pthread_t producerThread;
    pthread_t consumerThreads[nConsumers];
    pthread_create(&producerThread, NULL, producer, (void *) pArgs);

    for(int i = 0; i < nConsumers; i++) {
        struct consumerArgs* cArgs = malloc(sizeof(struct consumerArgs));
        *cArgs = (struct consumerArgs) {i, buffer};
        pthread_create(&(consumerThreads[i]), NULL, consumer, (void *) cArgs);
    }

    // Wait for all threads to complete execution
    pthread_join(producerThread, NULL);
    for(int i = 0; i < nConsumers; i++) {
        pthread_join(consumerThreads[i], NULL);
    }
    
    //Write the final output
    // writeFinalDSToFiles();
    FILE* outputFile;
    outputFile = fopen("output/result.txt","w");
    for(int i = 1; i < MaxWordLength+1; i++)  {
        fprintf(outputFile, "%d %d\n", i, buffer->histogram[i]);
    }
    fclose(outputFile);
    
    return 0; 
}