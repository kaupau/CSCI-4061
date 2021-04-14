#include "consumer.h"

/**
 * parse lines from the queue, and count words by word length
 */
void parse(){
    
}

// consumer function
void *consumer(int consumerID, void *arg){
    printf("consumer %d\n", consumerID);
    //TODO: keep reading from queue and process the data
    // feel free to change
    struct sharedBuffer* buffer = (struct sharedBuffer*) arg;

    while(1){
        printf("consumer %d: %d\n", consumerID);
        
        pthread_mutex_lock(buffer->mutex);
        struct node *current = buffer->head;
        buffer->head = buffer->head->next;
        char *line = current->line;
        free(current);
        pthread_mutex_unlock(buffer->mutex);

        parse();
    }
    
    //TODO: update the global array
    
    return NULL; 
}


