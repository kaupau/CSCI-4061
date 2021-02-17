#include "mapreduce.h"

int main(int argc, char *argv[]) {
	
	//TODO: number of argument check

	int nMappers 	= strtol(argv[1], NULL, 10);
	int nReducers 	= strtol(argv[2], NULL, 10);

    inputFileDir = argv[3];
    if(!isValidDir(inputFileDir))
        exit(EXIT_FAILURE);

	bookeepingCode();

	// TODO: spawn mappers	
	execlp("mapper.exe", "mapper.exe", ,NULL);

	// TODO: wait for all children to complete execution
	for(int i=0; i<nMappers; i++) {
		wait(NULL);
	}

	// TODO: spawn reducers
	execlp("reducer.exe", "reducer.exe", ,NULL);

	// TODO: wait for all children to complete execution
	for(int i=0; i<nMappers; i++) {
		wait(NULL);
	}

	return EXIT_SUCCESS;
}