#include "mapreduce.h"

void spawnMapper(int nMappers) {
	int process;
	for(int i=1; i<=nMappers; i++) {
		process = fork();
		if(process == 0)
			execlp("mapper.exe", "mapper.exe", i, nMappers, "output/IntermediateData/", NULL);
	}
}

void spawnReducers(int nReducers) {
	int process;
	for(int i=1; i<=nReducers; i++) {
		process = fork();
		if(process == 0)
			execlp("reducer.exe", "reducer.exe", i, nReducers, "output/IntermediateData/", NULL);
	}
}

void waitForAll(int num) {
	for(int i=0; i<num; i++) {
		wait(NULL);
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
	waitForAll(nMappers);

	// TODO: spawn reducers
	spawnReducers(nReducers);

	// TODO: wait for all children to complete execution
	waitForAll(nReducers);

	return EXIT_SUCCESS;
}