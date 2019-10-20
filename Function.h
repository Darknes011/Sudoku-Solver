#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <thread>
#include <array>
#include <vector>
#include <math.h>
#include <string.h>
#include <set>
#include <map>

const char BLANK = 255; //an empty cell
const int OFFSET_ASCII = 49; //shift from '0' to 0

using namespace std;
/*
                ***** Function.h *****

Description:  Contains all of the prototypes for the functions for the program 
Author:       Jeremy Goens
Class:        CSC 461 Artificial Intelligence
Date:         Spring 2018
Compilation   g++ -std=c++11 -g *.cpp
*/
void printLayout(string file, int size, int gen, int pop, double select, double mutation, int threshold);
void printStats(int gen, int best, int worst);
void printFile(string map);
void printMap(string map);
void fixMap(string& map);
bool TrivialSolution(string& map);
vector<string> generatePopulation(string map, int popSize);
string replaceDashes(string map);
string fillRow(string emptyRow);
string generateSolution(string map);
bool isValid(string map, char value, int position);
bool clearColumn(string map, char value, int position);
bool clearRow(string map, char value, int position);
bool clearSquare(string map, char value, int position);
bool fileParserReader(string filename, string& map);
bool fillSquare(string& map, int position, std::vector<std::string> potential);
bool fillRow(string& map, int position, std::vector<std::string> potential);
bool fillCol(string& map, int position, std::vector<std::string> potential);
string generateString(string map);
string toASCII(string solution);
set<char> generateValueSet( int size );
int calculateFitness(string solution);
string transposeSolution(string solution);
int chooseCrossoverPoint(string solution);
void recombination(string& left, string& right);
vector<string> selectFit(vector<string> solutions, double selectionRate);
vector<string> evolveNewGeneration(vector<string> civilization, int populationSize, double selectionRate);
