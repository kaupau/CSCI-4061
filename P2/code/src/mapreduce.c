#include "mapreduce.h"

void traverseInputFileDirectory(char *inputFileDir) {
	DIR *dir = opendir(inputFileDir);
	struct dirent *de = readdir(dir);
	if(de != NULL) {
		de->d_name;
	}
}

int main(int argc, char *argv[]) {
	
	// number of argument check
	if(argc < 4) {
		printf("Incorrect number of arguments\n");
		exit(EXIT_FAILURE);
	}

	int nMappers 	= strtol(argv[1], NULL, 10);
	int nReducers 	= strtol(argv[2], NULL, 10);

    inputFileDir = argv[3];
    if(!isValidDir(inputFileDir))
        exit(EXIT_FAILURE);

	bookeepingCode();

	//TODO: Traverse Input File Directory (Hint: Recursively find all the text files inside directory)
	// and create MapperInput directory which will contain MapperID.txt files
	traverseInputFileDirectory(inputFileDir);

	//TODO: spawn stream processes

	// TODO: spawn mappers	

	// TODO: wait for all children to complete execution

	// TODO: spawn reducers

	// TODO: wait for all children to complete execution

	return EXIT_SUCCESS;
}