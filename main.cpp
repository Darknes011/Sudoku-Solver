#include <chrono>
#include <ctime>
#include "Function.h"
using namespace std;

//Parallelize?
//#pragma omp parallel for

/*
                ***** main.cpp *****

Description:
Author:       Jeremy Goens, Aaron Gibbs
Class:        CSC 461 Artificial Intelligence
Date:         Spring 2018
Compilation   g++ -std=c++11 -g *.cpp
*/
int main( int argc, char** argv ){
	//default values if none are provided
	double mutation = 0.05;
	double selection = 0.5;
	int generations = 100;
	int population = 100;
	int threshold = 100;
	int size = 0;
	std::string filename;
	std::string map;

//sudoku filename population generations selection mutation
	switch(argc) {
		case 6:
			mutation = atof(argv[5]);
		case 5:
			selection = atoi(argv[4]);
		case 4:
			generations = atoi(argv[3]);
		case 3:
			population = atoi(argv[2]);
		case 2:
			filename = argv[1];
			break;
		default:
			std::cout << "Incorrect syntax: sudoku <filename> <population> <generations> <selection> <mutation>\n";
	}

	//Read in file - Function file
	fileParserReader(filename, map);

	printLayout(filename, size, generations, population, selection,  mutation, threshold);
	printFile(map);


	//Run through the trivial cases for the easy puzzles, make sure they can be solved - Trivial Solutions
	//fix to loop until no more are changed
	// int test;
	bool flag = true;
	while(flag == true){
		flag = TrivialSolution(map);
	}
	std::cout << "Fill in predetermined singles:\n";
	printMap(map);


	//When all exhaused, run through the GA - Genetic Algorithms/Population Generations

	vector<string> civilization = generatePopulation(map, population);

    //Evlove new generation until a solution is found or generation limit is reached
//    for(int i=0; i<10; ++i)
        civilization = evolveNewGeneration(civilization, population, selection);

	printStats(0, 81, 81);

	std::cout << "Best solution: \n\n";
	printMap(map);

	//Print outs - Functions File
	return 0;
}
