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

## Map function (mapper.c)

The map function takes in <key, value> pairs, processes them and produces a set of intermediate <key, value> pairs. The key and value(s) are determined from input files. The intermediate pairs are then grouped based on the key.

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
Testcase T0 starts
mapper[1] - test/T0/0.txt
mapper[2] - test/T0/1.txt
mapper[3] - test/T0/2.txt
mapper[6] - test/T0/5.txt
mapper[5] - test/T0/4.txt
mapper[4] - test/T0/3.txt
reducer[1] - output/IntermediateData/1/m6.txt
reducer[2] - output/IntermediateData/2/m6.txt
reducer[1] - output/IntermediateData/1/m1.txt
reducer[2] - output/IntermediateData/2/m1.txt
reducer[1] - output/IntermediateData/1/m4.txt
reducer[2] - output/IntermediateData/2/m2.txt
reducer[1] - output/IntermediateData/1/m3.txt
reducer[2] - output/IntermediateData/2/m5.txt
reducer[1] - output/IntermediateData/1/m2.txt
reducer[2] - output/IntermediateData/2/m4.txt
reducer[1] - output/IntermediateData/1/m5.txt
reducer[2] - output/IntermediateData/2/m3.txt
reducer[3] - output/IntermediateData/3/m3.txt
reducer[3] - output/IntermediateData/3/m4.txt
reducer[3] - output/IntermediateData/3/m5.txt
reducer[3] - output/IntermediateData/3/m2.txt
reducer[3] - output/IntermediateData/3/m1.txt
reducer[3] - output/IntermediateData/3/m6.txt
Pass test T0
================================================
Testcase T1 starts
mapper[1] - test/T1/F1.txt
reducer[3] - output/IntermediateData/3/m1.txt
reducer[1] - output/IntermediateData/1/m1.txt
reducer[2] - output/IntermediateData/2/m1.txt
reducer[3] - output/IntermediateData/6/m1.txt
reducer[2] - output/IntermediateData/5/m1.txt
reducer[1] - output/IntermediateData/4/m1.txt
reducer[3] - output/IntermediateData/9/m1.txt
reducer[2] - output/IntermediateData/8/m1.txt
reducer[3] - output/IntermediateData/12/m1.txt
reducer[1] - output/IntermediateData/7/m1.txt
reducer[2] - output/IntermediateData/11/m1.txt
reducer[3] - output/IntermediateData/15/m1.txt
reducer[1] - output/IntermediateData/10/m1.txt
reducer[2] - output/IntermediateData/14/m1.txt
reducer[3] - output/IntermediateData/18/m1.txt
reducer[1] - output/IntermediateData/13/m1.txt
reducer[2] - output/IntermediateData/17/m1.txt
reducer[2] - output/IntermediateData/20/m1.txt
reducer[1] - output/IntermediateData/16/m1.txt
reducer[1] - output/IntermediateData/19/m1.txt
Pass test T1
================================================
Testcase T2 starts
mapper[1] - test/T2/F2.txt
Pass test T2
================================================
Testing ended....
```
