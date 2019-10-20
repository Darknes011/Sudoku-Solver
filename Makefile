# Makefile
SOURCE = main.cpp \
          Function.cpp \
          PopulationGeneration.cpp \
          TrivialSolutions.cpp \
          GeneticAlgorithms.cpp 

OBJS = $(SOURCE:.cpp=.o)

#GNU C/C++ Compiler
GCC = g++

# GNU C/C++ Linker
LINK = g++

# Compiler flags
CFLAGS = -Wall -O -std=c++11
CXXFLAGS = $(CFLAGS)

# Fill in special libraries needed here
LIBS = 

.PHONY: clean

# Targets include all, clean, debug, tar

all : sudoku

sudoku: $(OBJS)
	$(LINK) -o $@ $^ $(LIBS)

clean:
	rm -rf *.o *.d core sudoku

debug: CXXFLAGS = -DDEBUG -g -std=c++11
debug: sudoku

tar: clean
	tar zcvf sudoku.tgz $(SOURCE) *.h Makefile

help:
	@echo "	make sudoku  - same as make all"
	@echo "	make all   - builds the main target"
	@echo "	make       - same as make all"
	@echo "	make clean - remove .o .d core main"
	@echo "	make debug - make all with -g and -DDEBUG"
	@echo "	make tar   - make a tarball of .cpp and .h files"
	@echo "	make help  - this message"

-include $(SOURCE:.cpp=.d)

%.d: %.cpp
	@set -e; /bin/rm -rf $@;$(GCC) -MM $< $(CXXFLAGS) > $@
