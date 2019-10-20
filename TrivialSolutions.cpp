#include "Function.h"
/*
                ***** TrivialSolution *****

Description:  Solves the trivial solutions for a basic sudoku puzzle
Author:       Jeremy Goens, Aaron Gibbs
Class:        CSC 461 Artificial Intelligence
Date:         Spring 2018
Compilation   g++ -std=c++11 -g *.cpp
*/
bool TrivialSolution(string& map){
	string vals = generateString(map);
	std::vector<std::string> potential((map.size()));
	std::vector<int> horz((sqrt(map.size()))+1);
	std::vector<int> vert((sqrt(map.size()))+1);
	bool flag = false;
	bool flagRow = false;
	bool flagCol = false;
	bool flagSqr = false;

	for( unsigned int i = 0; i < (map.size()); ++i){
		for( unsigned int j = 0; j < (vals.size()); ++j){
			if(map[i] == '-'){
				if(isValid(map, vals[j], i) ){
					//If the checks return true, change the value on map to
					potential[i].append(1, vals[j]);
				}
			}
		}
	}
	
	//Find all potential numbers for a given set
	for(unsigned int i = 0; i < potential.size();++i){
		if(potential[i].size() == 1){
			flag = true;
			map[i] = potential[i][0];
		}
	}

	//fills all given numbers for all rows
	for(unsigned int i = 0; i < (sqrt(map.size())); ++i){
		flagRow = fillRow(map, (i*(sqrt(map.size()))), potential);
	}

	for(unsigned int i = 0; i < (sqrt(map.size())); ++i){
		flagCol = fillCol(map, i, potential);
	}

	//map[21]
	for(unsigned int i = 0; i < (sqrt(map.size())); i+=sqrt(sqrt(map.size()))){
		for(unsigned int j = 0; j < (sqrt(map.size())); j+=sqrt(sqrt(map.size())))
			flagCol = fillSquare(map, (i*(sqrt(map.size())))+j, potential);
	}

	return (flag || flagRow || flagCol || flagSqr);
}

/*
                ***** isValid *****


Description:  Checks if the position can hold any given number
Author:       Jeremy Goens
Class:        CSC 461 Artificial Intelligence
Date:         Spring 2018
Compilation   g++ -std=c++11 -g *.cpp
*/
bool isValid(string map, char value, int position){

	if(clearRow(map,value, position) && clearColumn(map,value, position) && clearSquare(map,value, position)){
		return true;
	}

	else
		return false;
}

//Checks row for character to be put in
/*
                ***** clearRow *****

Description:  Checks to make sure the row does not contain a number
Author:       Jeremy Goens
Class:        CSC 461 Artificial Intelligence
Date:         Spring 2018
Compilation   g++ -std=c++11 -g *.cpp
*/
bool clearRow(string map, char value, int position){
	int size = sqrt(map.size());
	int row = position/size; // will cut off decimal places
	row = row*size;

	for( int i = 0; i < size; ++i){
		if(map[row+i] == value){
			return false;
		}
	}

	return true;
}

//Checks column for character to be put in
/*
                ***** clearColumn *****

Description:  Checks to make sure the Column does not contain a number
Author:       Jeremy Goens
Class:        CSC 461 Artificial Intelligence
Date:         Spring 2018
Compilation   g++ -std=c++11 -g *.cpp
*/
bool clearColumn(string map, char value, int position){
	int size = sqrt(map.size());
	int col = position%size;

	for( int i = 0; i < size; ++i){
		if(map[(i*size)+col] == value){
			return false;
		}
	}

	return true;
}

//Checks square for character to be put in
/*
                ***** clearSquare *****


Description:  Checks to make sure the subgrid does not contain a number
Author:       Jeremy Goens
Class:        CSC 461 Artificial Intelligence
Date:         Spring 2018
Compilation   g++ -std=c++11 -g *.cpp
*/
bool clearSquare(string map, char value, int position){
	int size = sqrt(map.size());
	int corner = sqrt(size);
	int row = position%size;
	int col = position/size; // will cut off decimal places
	int rowCorner = (row/corner)*corner;
	int colCorner = (col/corner)*corner;

	for(int i = rowCorner; i < rowCorner + corner; ++i){
		for(int j = colCorner; j < colCorner + corner; ++j){
			if(map[(j*9)+i] == value){
				return false;
			}
		}
	}
	return true;
}

/*
                ***** fillSquare *****

Description:  Fills in each square with the hidden singles that are able to be found
Author:       Jeremy Goens
Class:        CSC 461 Artificial Intelligence
Date:         Spring 2018
Compilation   g++ -std=c++11 -g *.cpp
*/
bool fillSquare(string& map, int position, std::vector<std::string> potential){
	int size = sqrt(map.size());
	int corner = sqrt(size);
	int row = position/size; //34 = 3
	int col = position%size; //34 = 7
	int rowCorner = (row/corner)*corner; // upmost row in set
	int colCorner = (col/corner)*corner; // leftmost column in set
	std::vector<int> pot;
	std::vector<int> fill(size+1); // array size 10
	char temp;
	int count = 0;
	bool flag = false;

//Walk through somehow and get all potentials

	for(int i = rowCorner; i < rowCorner + corner; ++i){
		for(int j = colCorner; j < colCorner + corner; ++j){
			for(unsigned int k = 0; k < potential[((i*size)+j)].size(); ++k){
				temp = potential[((i*size)+j)][k];
				pot.resize(count+1);
				pot[count] = (int)temp - 48;
				count += 1;
			}
		}
	}

	for( unsigned int i = 0; i < pot.size(); ++i){
		fill[pot[i]] += 1;
	}

	//cout << "\nFill Array: ";
	for( unsigned int k = 0; k < fill.size(); ++k){
		if(fill[k] == 1){
			flag = true;
			temp = (char)(k + 48); // outputs found number
			for(int i = rowCorner; i < rowCorner + corner; ++i){
				for(int j = colCorner; j < colCorner + corner; ++j){
					for(unsigned int k = 0; k < potential[((i*size)+j)].size(); ++k){
						if(temp == potential[i][j]){
							map[i] = temp;	

						}				
					}
				}
			}
		}
	}

	return flag;
}

/*
                ***** fillRow *****

Description:  Fills in each row with the hidden singles that are able to be found
Author:       Jeremy Goens
Class:        CSC 461 Artificial Intelligence
Date:         Spring 2018
Compilation   g++ -std=c++11 -g *.cpp
*/
bool fillRow(string& map, int position, std::vector<std::string> potential){
	int size = sqrt(map.size());
	int row = position/size; //34 = 3
	std::vector<int> pot;
	std::vector<int> fill(size+1); // array size 10
	char temp;
	int count = 0;
	bool flag = false;

	//Converts string of potential values to ints
	for (int i = (row*size); i < ((row*size)+size) ; ++i){
		for(unsigned int j = 0; j < potential[i].size(); ++j){
			temp = potential[i][j];
			pot.resize(count+1);
			pot[count] = (int)temp - 48;
			count += 1;
		}
	}

	//copy pasta
	for( unsigned int i = 0; i < pot.size(); ++i){
		fill[pot[i]] += 1;
	}
	
	//find the position and changes the map
	for( unsigned int k = 0; k < fill.size(); ++k){
		//cout << fill[i] << ", ";
		if(fill[k] == 1){
			flag = true;
			temp = (char)(k + 48); // outputs found number
			for (int i = (row*size); i < ((row*size)+size) ; ++i){
				for(unsigned int j = 0; j < potential[i].size(); ++j){
					if(temp == potential[i][j]){
						map[i] = temp;					
					}
				}
			}
		}
	}

	return flag;
}

/*
                ***** fillCol *****

Description:  Fills in each column with the hidden singles that are able to be found
Author:       Jeremy Goens
Class:        CSC 461 Artificial Intelligence
Date:         Spring 2018
Compilation   g++ -std=c++11 -g *.cpp
*/
bool fillCol(string& map, int position, std::vector<std::string> potential){
	int size = sqrt(map.size());
	int col = position%size; //34 = 7
	std::vector<int> pot;
	std::vector<int> fill(size+1); // array size 10
	char temp;
	int count = 0;
	bool flag = false;

	//find here
	//Converts string of potential values to ints
	for (int i = 0; i < (size) ; ++i){
		for(unsigned int j = 0; j < potential[((i*size)+col)].size(); ++j){
			temp = potential[((i*size)+col)][j];
			pot.resize(count+1);
			pot[count] = (int)temp - 48;
			count += 1;
		}
	}
	
	//Checks for numbers that only appear once
	for( unsigned int i = 0; i < pot.size(); ++i){
		fill[pot[i]] += 1;
	}

	//Walks through filled array, outputs numbers that can only be used once into the correct position
	for( unsigned int k = 0; k < fill.size(); ++k){
		if(fill[k] == 1){
			flag = true;
			temp = (char)(k + 48); // outputs found number
			for (int i = 0; i < (size) ; ++i){
				for(unsigned int j = 0; j < potential[((i*size)+col)].size(); ++j){
					if(temp == potential[((i*size)+col)][j]){
						map[((i*size)+col)] = temp;					
					}
				}
			}
		}
	}

	return flag;
}

