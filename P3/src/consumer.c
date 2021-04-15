#include "consumer.h"

/**
 * parse lines from the queue, and count words by word length
 */
int parse(char* line, int* localHist, int prevCount){
  printf("Parsing %s\n",line);
  int lineLength = strlen(line);
  int wordLen = prevCount;
  for(int i = 0; i < lineLength; i++) {
    if(line[i] != ' ' && line[i] != '\n') {
      ++wordLen;
    } else {
      if(wordLen > 0 && wordLen <= MaxWordLength) {
        ++localHist[wordLen - 1];
        printf("Found word of length %d\n",wordLen);
      }
      wordLen = 0;
    }
  }

  if(wordLen > 0 && wordLen <= MaxWordLength) {
        ++localHist[wordLen - 1];
        printf("Found word of length %d\n",wordLen);
      }
      wordLen = 0;

  return wordLen;
}

// consumer function
void *consumer(void *arg){
    //TODO: keep reading from queue and process the data
    // feel free to change

    struct consumerArgs* args = (struct consumerArgs*) arg;
    struct sharedBuffer* buffer = (struct sharedBuffer*) args->buffer;
    int* globalHist = (int*) args->globalHist;
    pthread_mutex_t* globalHistMutex = args->globalHistMutex;
    printf("consumer %d\n", args->consumerID);

    int localHist[MaxWordLength] = {0};
    int prevCount = 0;
    while(1){
      pthread_mutex_lock(buffer->mutex);
        if(buffer->head == NULL && buffer->EOFSignal) {
          pthread_mutex_unlock(buffer->mutex);
          break;
        }
        if(buffer->bufferLen > 0 && buffer->head != NULL) {
            struct node *current = buffer->head;
            // printf("%s\n", current->line);
            buffer->head = buffer->head->next;
            
            char *line = current->line;
            int lineNumber = current->lineNumber;

            printf("consumer %d: %d\n", args->consumerID, lineNumber);
            
            prevCount = parse(line,localHist,prevCount);

            buffer->bufferLen--;

            free(current);
         }
      pthread_mutex_unlock(buffer->mutex);
    }

    if(prevCount > 0 && prevCount <= MaxWordLength) {
        ++localHist[prevCount - 1];
        printf("File ended with word of length %d\n",prevCount);
    }

    
    //TODO: update the global array
    printf("Returning from consumer %d\n", args->consumerID);
    pthread_mutex_lock(globalHistMutex);
    for(int i = 0; i < MaxWordLength; i++) {
      printf("Local hist: %d, %d\n",i,localHist[i]);
      globalHist[i] += localHist[i];
    }
    pthread_mutex_unlock(globalHistMutex);

    return NULL; 
}


