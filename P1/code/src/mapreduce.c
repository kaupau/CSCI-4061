#include "mapreduce.h"

void spawnMapper(int nMappers) {
	int process;
	for(int i=1; i<=nMappers; i++) {
		process = fork();
		if(process == 0) {
			char iString[4];
			char nMappersString[4];
			sprintf(iString,"%d",i);
			sprintf(nMappersString,"%d",nMappers);
			execl("./mapper", "./mapper",iString, nMappersString, inputFileDir, NULL);
      printf("execlp mapper failed\n");
      exit(EXIT_FAILURE);
    }
  }
}

void spawnReducers(int nReducers) {
	int process;
	for(int i=1; i<=nReducers; i++) {
		process = fork();
		if(process == 0) {
			char iString[4];
			char nReducersString[4];
			sprintf(iString,"%d",i);
			sprintf(nReducersString,"%d",nReducers);
			execl("./reducer", "./reducer", iString, nReducersString, NULL);
      printf("execlp reducer failed\n");
      exit(EXIT_FAILURE);
    }
  }
}

void waitForAll(int num) {
	pid_t pid_child;
  for(int i=0; i<num; i++) {
		pid_child = wait(NULL);
    if(pid_child < 0) {
      printf("Waited for non-existant child\n");
      exit(EXIT_FAILURE);
    }
	}
}

int main(int argc, char *argv[]) {
	
	// check number of arguments
  if(argc < 4) {
    printf("Incorrect number of arguments\n");
    exit(EXIT_FAILURE);
  }

	int nMappers 	= strtol(argv[1], NULL, 10);
	int nReducers 	= strtol(argv[2], NULL, 10);
  if( nMappers < 1 || nReducers < 1) {
    printf("Number of mappers or reducers must be at least 1 each\n");
    exit(EXIT_FAILURE);
  }

  inputFileDir = argv[3];
  if(!isValidDir(inputFileDir))
    exit(EXIT_FAILURE);

	bookeepingCode();

	// spawn mappers	
	spawnMapper(nMappers);

	// wait for all children to complete execution
	waitForAll(nMappers);

	// spawn reducers
	spawnReducers(nReducers);

	// wait for all children to complete execution
	waitForAll(nReducers);

	return EXIT_SUCCESS;
}
