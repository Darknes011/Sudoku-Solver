#include "Function.h"


/*
                ***** generatePopulation *****

Description:
Author:       Aaron Gibbs
Class:        CSC 461 Artificial Intelligence
Date:         Spring 2018
Compilation   g++ -std=c++11 -g *.cpp
*/
vector<string> generatePopulation(string map, int popSize)
{
	printf("Generating Population \n");
    vector<string> population;

    map = replaceDashes(map);
    map = toASCII(map);
    for (int i=0; i<popSize; ++i)
    {
        population.push_back(generateSolution(map));
    }
    
	return population;
}

/*
                ***** replaceDashes *****

Description:
Author:       Aaron Gibbs
Class:        CSC 461 Artificial Intelligence
Date:         Spring 2018
Compilation   g++ -std=c++11 -g *.cpp
*/
string replaceDashes(string map)
{
    char blank = (int(BLANK) + OFFSET_ASCII) % 256;
    
    string out = "";
    
    for (auto cell : map)
        if (cell == '-') out += blank;
        else out += cell;
    
    return out;
}

/*
                ***** fillRow *****

Description:
Author:       Aaron Gibbs
Class:        CSC 461 Artificial Intelligence
Date:         Spring 2018
Compilation   g++ -std=c++11 -g *.cpp
*/
string fillRow(string emptyRow)
{
    set<char> cellValues = generateValueSet(emptyRow.size());
    
    string filledRow = "";
    
    for ( auto cell : emptyRow )
        cellValues.erase(cell);
        
    for ( auto cell : emptyRow )
    {
        if ( cell == BLANK )
        {
            int rng = rand() % cellValues.size();
            set<char>::iterator it = cellValues.begin();
            
            for ( int i=0; i<rng; ++i) ++it;
            
            filledRow += *it;
            cellValues.erase(it);
        }
        else
            filledRow += cell;
    }
    
    return filledRow;
}

/*
                ***** generateSolution *****

Description:
Author:       Aaron Gibbs
Class:        CSC 461 Artificial Intelligence
Date:         Spring 2018
Compilation   g++ -std=c++11 -g *.cpp
*/
string generateSolution(string map)
{
    int groupSize = sqrt(map.size());
    
    string solution = "";
    
    for (int i=0; i<groupSize; ++i)
    {
        string currentRow(map, i*groupSize, groupSize);
        solution += fillRow(currentRow);
    }
    
    return solution;
}
