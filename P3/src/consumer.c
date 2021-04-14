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
void *consumer(int consumerID, void *arg){
    printf("consumer %d\n", consumerID);
    //TODO: keep reading from queue and process the data
    // feel free to change
    struct sharedBuffer* buffer = (struct sharedBuffer*) arg;

    int localHist[MaxWordLength] = {0};

    while(1){
        printf("consumer %d: %d\n", consumerID);
        
        pthread_mutex_lock(buffer->mutex);
        struct node *current = buffer->head;
        buffer->head = buffer->head->next;
        char *line = current->line;
        free(current);
        pthread_mutex_unlock(buffer->mutex);

        parse(line,localHist);
    }
    
    //TODO: update the global array
    
    return NULL; 
}


