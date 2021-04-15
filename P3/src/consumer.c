#include "consumer.h"

/**
 * parse lines from the queue, and count words by word length
 */
void parse(char* line, int* localHist){
    int lineLength = strlen(line);
    int wordLen = 0;
    for(int i = 0; i < lineLength; i++) {
        if(line[i] != ' ') {
            ++wordLen;
        } else {
            if(wordLen > 0 && wordLen < MaxWordLength) {
                ++localHist[wordLen - 1];
            }
            wordLen = 0;
        }
    }
}

// consumer function
void *consumer(void *arg){
    // keep reading from queue and process the data
    struct consumerArgs* args = (struct consumerArgs*) arg;
    struct sharedBuffer* buffer = (struct sharedBuffer*) args->buffer;
    int localHist[MaxWordLength+1] = {0};
    printf("consumer %d\n", args->consumerID);
    
    while(buffer->bufferLen > 0 || EOFStatus == 1){
    // while(1) {
        pthread_mutex_lock(buffer->mutex);
        
        if(EOFStatus == 1) {
            pthread_cond_wait(buffer->cond, buffer->mutex);
        }
        
        struct node *current = buffer->head;
        
        if(buffer->head->next == NULL) {
            buffer->head = NULL;
        } else {
            buffer->head = buffer->head->next;
        }
        
        char *line = current->line;
        int lineNumber = current->lineNumber;
        free(current);
        buffer->bufferLen -=1;

        printf("consumer %d: %d\n", args->consumerID, lineNumber);
        // printf("EOFStatus: %d   BufferLen: %d \n", EOFStatus, buffer->bufferLen);
        
        pthread_mutex_unlock(buffer->mutex);
        
        
        
        
        // current = buffer->head;
        // while(current->next != NULL) {
        //     printf("**** Line: %d\n", current->lineNumber);
        //     current = current->next;
        // }
        // printf("***");

        parse(line,localHist);
             
    }
    printf("consumer %d over\n", args->consumerID);
    
    //TODO: update the global array
    pthread_mutex_lock(buffer->mutex);
    pthread_cond_wait(buffer->cond, buffer->mutex);
    for(int i = 0; i < MaxWordLength; i++) {
        buffer->histogram[i] += localHist[i];
        printf("hist[%d] = %d \n", i, buffer->histogram[i]);
    }
    pthread_mutex_unlock(buffer->mutex);
    
    return NULL; 
}


