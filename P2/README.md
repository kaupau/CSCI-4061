test machine: csel-kh1260-03
date: 2/24/2021
name: Kaushik Kanna, Alan Wang
x500: kanna114, wang7200

# Project 1 : MapReduce - Word counts of different lengths

## Contributions
Kaushik: mapreduce.c, reducer.c, README.md
Alan: mapreduce.c, mapper.c, README.md

## Master function (mapreduce.c)

The master mapreduce uses map and reduce logic paradigm for counting the number of words of different lengths in a large collection of documents by executing mappers and reducers accordingly.
The first argument is the number of mapper processes, and the second is the number of reducer processes. The third argument is the path to the folder which contains the text files with words to be counted.
The result of executing this program is the folder ./output, which contains the word count data.

## Stream function (stream.c)
The stream processes will read the text files from the file directories and send
the data to mappers process. There will 1:1 relationship between stream and mapper process. So
number of stream processes will be equal to the mapper processes.

## Map function (mapper.c)

The map function takes in <key, value> pairs, processes them and produces a set of intermediate <key, value> pairs. The key and value(s) are determined from input files. The intermediate pairs are then grouped based on the key. It sends them to the receive.

## Reduce function (reducer.c)

The reduce function will then reduce/merge the grouped intermediate values based on the key to produce the final result. In this assignment, you will use map and reduce logic paradigm for counting the number of words of different lengths in a large collection of documents.

## Compile
	> make clean
	> make

	or

	> gcc -g -Iinclude  lib/utils.o src/reducer.c -o reducer
	> gcc -g -Iinclude lib/utils.o src/mapreduce.c -o mapreduce

## Execution
	// always call make clean and make before you start execution
	// ./mapreduce nMappers nReducer inputFileDir
	> ./mapreduce 5 3 test/T0

## Result
Check output folder for all the results. Results of 'make test' is shown below.
```
Spawning 3 reducers
reducer[3] - output/IntermediateData/3/m2.txt
reducer[2] - output/IntermediateData/2/m2.txt
reducer[3] - output/IntermediateData/3/m3.txt
reducer[3] - output/IntermediateData/3/m1.txt
reducer[3] - output/IntermediateData/3/m4.txt
reducer[2] - output/IntermediateData/2/m3.txt
reducer[3] - output/IntermediateData/3/m5.txt
reducer[2] - output/IntermediateData/2/m1.txt
reducer[3] - output/IntermediateData/3/m6.txt
reducer[2] - output/IntermediateData/2/m4.txt
reducer[2] - output/IntermediateData/2/m5.txt
reducer[2] - output/IntermediateData/2/m6.txt
reducer[1] - output/IntermediateData/1/m2.txt
reducer[1] - output/IntermediateData/1/m3.txt
reducer[1] - output/IntermediateData/1/m1.txt
reducer[1] - output/IntermediateData/1/m4.txt
mapreduce has waited for 1 of 3 childs
mapreduce has waited for 2 of 3 childs
reducer[1] - output/IntermediateData/1/m5.txt
reducer[1] - output/IntermediateData/1/m6.txt
mapreduce has waited for 3 of 3 childs
Pass test T0
================================================
Testcase T1 starts
Spawning 3 reducers
reducer[1] - output/IntermediateData/1/m2.txt
reducer[1] - output/IntermediateData/1/m3.txt
reducer[1] - output/IntermediateData/1/m1.txt
reducer[1] - output/IntermediateData/1/m4.txt
reducer[1] - output/IntermediateData/1/m5.txt
reducer[1] - output/IntermediateData/1/m6.txt
reducer[2] - output/IntermediateData/2/m2.txt
mapreduce has waited for 1 of 3 childs
reducer[2] - output/IntermediateData/2/m3.txt
reducer[2] - output/IntermediateData/2/m1.txt
reducer[2] - output/IntermediateData/2/m4.txt
reducer[2] - output/IntermediateData/2/m5.txt
reducer[2] - output/IntermediateData/2/m6.txt
mapreduce has waited for 2 of 3 childs
reducer[3] - output/IntermediateData/3/m2.txt
reducer[3] - output/IntermediateData/3/m3.txt
reducer[3] - output/IntermediateData/3/m1.txt
reducer[3] - output/IntermediateData/3/m4.txt
reducer[3] - output/IntermediateData/3/m5.txt
reducer[3] - output/IntermediateData/3/m6.txt
mapreduce has waited for 3 of 3 childs
Key difference : expected - observed
{'4'}
================================================
Testing ended....
```
