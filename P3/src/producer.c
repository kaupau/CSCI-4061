#include "producer.h"

/**
 *
 * Producer thread will read from the file and write data to 
 * the end of the shared queue
 */
void *producer(char* filename, void *arg){
    printf("producer\n");
    //TODO: open the file and read its content line by line
    //Send data to the shared queue
    //When reaching the end of the file, send EOF message to the shared queue
    FILE *inputFile = getFilePointer(filename);
    struct sharedBuffer* buffer = (struct sharedBuffer*) arg;
    int lineNumber = 0;

    char line[maxFileNameLength];
    while( getLineFromFile(inputFile, line, maxFileNameLength) != -1 ) {
        printf("producer: %d\n", lineNumber++);

        line[strlen(line)-1] = '\0';
        
        pthread_mutex_lock(buffer->mutex);
        struct node *current = buffer->head;
        while(current->next != NULL) {
            current = current->next;
        }
        current->next = malloc(sizeof(struct node));
        *(current->next) = (struct node) {NULL, line};
        pthread_mutex_unlock(buffer->mutex);
    }

    pthread_cond_broadcast(buffer->EOFSignal);

    // cleanup and exit
    return NULL; 
}