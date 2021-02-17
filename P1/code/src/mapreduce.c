#include "mapreduce.h"

void spawnMapper(int nMappers) {
	int process;
	for(int i=1; i<=nMappers; i++) {
		process = fork();
		if(process == 0)
			execlp("mapper.exe", "mapper.exe", i, nMappers, NULL);
	}
}

void spawnReducers(int nReducers) {
	int process;
	for(int i=1; i<=nReducers; i++) {
		process = fork();
		if(process == 0)
			execlp("reducer.exe", "reducer.exe", i, nReducers, NULL);
	}
}

int main(int argc, char *argv[]) {
	
	//TODO: number of argument check

	int nMappers 	= strtol(argv[1], NULL, 10);
	int nReducers 	= strtol(argv[2], NULL, 10);

    inputFileDir = argv[3];
    if(!isValidDir(inputFileDir))
        exit(EXIT_FAILURE);

	bookeepingCode();

	// TODO: spawn mappers	
	spawnMapper(nMappers);

	// TODO: wait for all children to complete execution
	for(int i=0; i<nMappers; i++) {
		wait(NULL);
	}

	// TODO: spawn reducers
	spawnReducers(nReducers);

	// TODO: wait for all children to complete execution
	for(int i=0; i<nMappers; i++) {
		wait(NULL);
	}

	return EXIT_SUCCESS;
}