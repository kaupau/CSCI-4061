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

    char line[maxFileNameLength];
    
    while( getLineFromFile(inputFile, line, maxFileNameLength) != -1 ) {
        printf("producer: %d\n", lineNumber++);

        line[strlen(line)-1] = '\0';
        printf("Producer got line: %s\n",line);

        pthread_mutex_lock(buffer->mutex);
        buffer->bufferLen++;

            struct node *current = buffer->head;
            buffer->head = malloc(sizeof(struct node));
            buffer->head->next = current;
            buffer->head->lineNumber = lineNumber;
            strcpy(buffer->head->line,line);

        pthread_mutex_unlock(buffer->mutex);
    }

    buffer->EOFSignal = 1;

    // cleanup and exit
    return NULL; 
}
