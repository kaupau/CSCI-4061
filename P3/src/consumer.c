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
    //TODO: keep reading from queue and process the data
    // feel free to change

    struct consumerArgs* args = (struct consumerArgs*) arg;
    struct sharedBuffer* buffer = (struct sharedBuffer*) args->buffer;
    printf("consumer %d\n", args->consumerID);

    int localHist[MaxWordLength] = {0};
    while(1){
        if(buffer->bufferLen > 1) {
            pthread_mutex_lock(buffer->mutex);
            struct node *current = buffer->head;
            // printf("%s\n", current->line);
            if(buffer->head->next == NULL) {
                buffer->head = NULL;
            } else {
                buffer->head = buffer->head->next;
            }
            
            char *line = current->line;
            int lineNumber = current->lineNumber;
            free(current);
            buffer->bufferLen--;
            pthread_mutex_unlock(buffer->mutex);

            printf("consumer %d: %d\n", args->consumerID, lineNumber);
            
            parse(line,localHist);
        }        
    }
    
    //TODO: update the global array
    
    return NULL; 
}


