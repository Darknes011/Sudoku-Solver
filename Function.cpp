#include "Function.h"
/*
                ***** fileParserReader*****

Description:  Reads in the file, removes white space and returns it as a string.
Author:       Jeremy Goens
Class:        CSC 461 Artificial Intelligence
Date:         Spring 2018
Compilation   g++ -std=c++11 -g *.cpp
*/
bool fileParserReader(string filename, string& map){
	fstream fin;
	char str;
	fin.open(filename);

	if (!fin) {
    	cerr << "Unable to open file datafile.txt";
    	exit(1);   // call system to stop
	}

	while(fin >> str){
		//std::cout << str;
		map.append(1,str);
	}

	return true;

}
/*
                ***** printLayout *****

Description:  Prints out the basic units for the GA
Author:       Jeremy Goens
Class:        CSC 461 Artificial Intelligence
Date:         Spring 2018
Compilation   g++ -std=c++11 -g *.cpp
*/
void printLayout(string file, int size, int gen, int pop, double select, double mutation, int threshold){
	std::cout << "Sudoku: " << file << "\n";
	printf("population size = %d \nnumber of generations = %d \nselection rate = %g \n",pop, gen, select);
	printf( "mutation rate = %g \nrestart threshold = %d \n\n", mutation, threshold);
}

/*
                ***** printFile *****

Description:  Outputs the basic information before the puzzle is solved
Author:       Jeremy Goens
Class:        CSC 461 Artificial Intelligence
Date:         Spring 2018
Compilation   g++ -std=c++11 -g *.cpp
*/
void printFile(string map){

	int count = 0;
	int size = sqrt(sqrt(map.size()));

	std::cout << "Initial configuration (" << size*size << "x" <<size*size << " grid): \n";

	for(int h = 0; h < size; ++h){
		for(int i = 0; i < size; ++i){
			for(int j = 0; j < size; ++j){
				for(int k = 0; k < size; ++k){
					std::cout << map[count++] << " ";
				}
				std::cout << " ";	
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}
	
}
/*
                ***** printMap *****

Description:  Prints out the map with basic formatting
Author:       Jeremy Goens
Class:        CSC 461 Artificial Intelligence
Date:         Spring 2018
Compilation   g++ -std=c++11 -g *.cpp
*/
void printMap(string map){

	int count = 0;
	int size = sqrt(sqrt(map.size()));

	for(int h = 0; h < size; ++h){
		for(int i = 0; i < size; ++i){
			for(int j = 0; j < size; ++j){
				for(int k = 0; k < size; ++k){
					std::cout << map[count++] << " ";
				}
				std::cout << " ";	
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}
}

/*
                ***** printStats *****

Description:  Prints the basic scores and stats for the GA
Author:       Jeremy Goens
Class:        CSC 461 Artificial Intelligence
Date:         Spring 2018
Compilation   g++ -std=c++11 -g *.cpp
*/
void printStats(int gen, int best, int worst){

	//Generation    0: best score =   22, worst score =   4
	printf("Generation    %d: best score =   %d, worst score =   %d \n\n", gen, best, worst);
}

//Generate a string of number for the map size
/*
                ***** generateString *****

Description:  Generates a character string map copy
Author:       Jeremy Goens, Aaron Gibbs
Class:        CSC 461 Artificial Intelligence
Date:         Spring 2018
Compilation   g++ -std=c++11 -g *.cpp
*/
string generateString(string map){
	int size = sqrt(map.size());
	string chr;
	string str;

	for(int i = 0; i < size ; ++i){
		chr = std::to_string(i+1);
		str.append(chr);
	}

	return str;
}
