#include "Function.h"

/*
                ***** toASCII *****

Description:
Author:       Aaron Gibbs
Class:        CSC 461 Artificial Intelligence
Date:         Spring 2018
Compilation   g++ -std=c++11 -g *.cpp
*/
string toASCII(string solution)
{
    string out = "";
    char tmp = BLANK;
    
    for ( auto cell : solution )
    {
        tmp = ((int)cell - OFFSET_ASCII + 256) % 256; //correct for negatives
        out += tmp;
    }
    
    return out;
}

/*
                ***** generateValueSet *****

Description:
Author:       Aaron Gibbs
Class:        CSC 461 Artificial Intelligence
Date:         Spring 2018
Compilation   g++ -std=c++11 -g *.cpp
*/
set<char> generateValueSet( int size )
{
    set<char> values;
    
    for (int i=0; i < size; ++i)
        values.insert((char)i);
        
    return values;
}
/*
                ***** calculateFitness *****

Description:
Author:       Aaron Gibbs
Class:        CSC 461 Artificial Intelligence
Date:         Spring 2018
Compilation   g++ -std=c++11 -g *.cpp
*/
int calculateFitness(string solution)
{
    int groupSize = sqrt(solution.size());
    int fitness = solution.size(); //initilised at minimum fitness
    
    set<char> cellValues = generateValueSet(groupSize);
    solution = transposeSolution(solution);
    
    //check each row for number of unique entries
    for (int i=0; i<groupSize; ++i)
    {
        set<char> currentRowSet(cellValues); //copy full set
        for (int j=0; j<groupSize; ++j)
            if (currentRowSet.erase(solution[groupSize*i+j]))
                fitness -= 1;
    }
    
    return fitness;
}

/*
                ***** transposeSolution *****

Description:
Author:       Aaron Gibbs
Class:        CSC 461 Artificial Intelligence
Date:         Spring 2018
Compilation   g++ -std=c++11 -g *.cpp
*/
string transposeSolution(string solution)
{
    string transpose = "";
    int rowSize = sqrt(solution.size());
    
    for (int col=0; col<rowSize; ++col)
        for (int row=0; row<rowSize; ++row)
        {
            transpose += solution.at(col + row*rowSize);
        }
    
    return transpose;
}

/*
                ***** chooseCrossoverPoint *****

Description:
Author:       Aaron Gibbs
Class:        CSC 461 Artificial Intelligence
Date:         Spring 2018
Compilation   g++ -std=c++11 -g *.cpp
*/
int chooseCrossoverPoint(string solution)
{
    int numSubgrids = sqrt(solution.size());
    int subgridLength = sqrt(numSubgrids);
    
    int crossoverpoint = 0;
    
    do {
        //pick point on grid
        int horizontal = rand() % subgridLength;
        int vertical = rand() % subgridLength + 1;

        crossoverpoint = subgridLength * numSubgrids*vertical - subgridLength*horizontal;
    } while (crossoverpoint == (int)solution.size());
    
    return crossoverpoint;
}

/*
                ***** recombination *****

Description:
Author:       Aaron Gibbs
Class:        CSC 461 Artificial Intelligence
Date:         Spring 2018
Compilation   g++ -std=c++11 -g *.cpp
*/
void recombination(string& left, string& right)
{
    int crossoverpoint = chooseCrossoverPoint(left);
    
    string tmp1(left, 0, crossoverpoint);
    string tmp2(right, 0, crossoverpoint);
    
    tmp1 += right.substr(crossoverpoint);
    tmp2 += left.substr(crossoverpoint);
    
    left = tmp1;
    right = tmp2;
}

/*
                ***** selectFit *****

Description:
Author:       Aaron Gibbs
Class:        CSC 461 Artificial Intelligence
Date:         Fall 2017
Compilation   g++ -std=c++11 -g *.cpp
*/
vector<string> selectFit(vector<string> solutions, double selectionRate)
{
    multimap<int, string> ranking;
    vector<string> fitSolutions;
    int fitness = -1;
    
    for( auto grid : solutions )
    {
        fitness = calculateFitness(grid);
        ranking.emplace(fitness, grid);
    }
    
    double startingSize = ranking.size();
    multimap<int, string>::reverse_iterator it = ranking.rbegin();
    
    while(fitSolutions.size()/startingSize < selectionRate)
    {
        fitSolutions.push_back( it->second );
        ++it;
    }
    
    cout << fitSolutions.size() << " fit solutions selected.\n";
    
    return fitSolutions;
}

/*
                ***** evolveNewGeneration *****

Description:
Author:       Aaron Gibbs
Class:        CSC 461 Artificial Intelligence
Date:         Fall 2017
Compilation   g++ -std=c++11 -g *.cpp
*/
vector<string> evolveNewGeneration(vector<string> civilization, int populationSize, double selectionRate)
{
    vector<string> fitSolutions = selectFit(civilization, selectionRate);
    vector<string> newGeneration;
    int fitSize = fitSolutions.size();
    string grid1;
    string grid2;
    
    for(int i=0; i<populationSize/2; ++i)
    {
        grid1 = fitSolutions.at( rand() % fitSize );
        grid2 = fitSolutions.at( rand() % fitSize );
        
        recombination( grid1, grid2 );
        
        //add mutation here
        
        newGeneration.push_back(grid1);
        newGeneration.push_back(grid2);
    }
    
    cout << newGeneration.size() << " new solutions evolved.\n";
    
    return newGeneration;
}
