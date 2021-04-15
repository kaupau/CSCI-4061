#include "producer.h"

/**
 *
 * Producer thread will read from the file and write data to 
 * the end of the shared queue
 */
void *producer(void *arg) {
    printf("producer\n");

    //TODO: open the file and read its content line by line
    //Send data to the shared queue
    //When reaching the end of the file, send EOF message to the shared queue

    struct producerArgs* args = (struct producerArgs*) arg;
    FILE *inputFile = getFilePointer(args->filename);
    struct sharedBuffer* buffer = (struct sharedBuffer*) args->buffer;
    int lineNumber = 0;
    int fileStatus = 0;
    
    while( fileStatus != -1 ) {
        char* line = malloc(sizeof(char) * maxFileNameLength);
        fileStatus = getLineFromFile(inputFile, line, maxFileNameLength);

        printf("producer: %d\n", lineNumber++);
        buffer->bufferLen++;
        
        line[strlen(line)-1] = '\0';
        
        pthread_mutex_lock(buffer->mutex);
        if(buffer->head == NULL) {
            buffer->head = malloc(sizeof(struct node));
            *(buffer->head) = (struct node) {NULL, line, lineNumber};
        } else {
            struct node *current = buffer->head;
            while(current->next != NULL) {
                current = current->next;
            }
            current->next = malloc(sizeof(struct node));
            *(current->next) = (struct node) {NULL, line, lineNumber};
        }
        pthread_mutex_unlock(buffer->mutex);
    }

    pthread_cond_broadcast(buffer->EOFSignal);

    // cleanup and exit
    return NULL; 
}