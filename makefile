# CS 530 Program 2 - Ben Shen
# Student: Anthony Norderhaug
# RedID: 823899304
# Date: 11-6-22

# compiles the program into an executable named 'disassem'
# compile by typing 'make'
# remove previously compiled files by typing 'make clean'
# to ensure you are using your latest code when compiling

CXX=g++
# Make variable for compiler options
# -std=c++11  C/C++ variant to use, e.g. C++ 2011
# -Wall       show verbose warning messages
# -g3         include information for symbolic debugger e.g. gdb
CXXFLAGS=-std=c++11 -Wall -g3 -c

# object files
OBJS = main.o Conversion.o Disassembly.o Formatting.o Instruction.o Library.o Table.o

# Program name
PROGRAM = disassem

# Rules format:
# target : dependency1 dependency2 ... dependencyN
#     Command to make target, uses default rules if not specified

# First target is the one executed if you just type make
# make target specifies a specific target
# $^ is an example of a special variable.  It substitutes all dependencies
$(PROGRAM) : $(OBJS)
	$(CXX) -o $(PROGRAM) $^

main.o : main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

Conversion.o : Conversion.cpp Conversion.h
	$(CXX) $(CXXFLAGS) Conversion.cpp

Disassembly.o : Disassembly.cpp Disassembly.h
	$(CXX) $(CXXFLAGS) Disassembly.cpp

Formatting.o : Formatting.cpp Formatting.h
	$(CXX) $(CXXFLAGS) Formatting.cpp

Instruction.o : Instruction.cpp Instruction.h
	$(CXX) $(CXXFLAGS) Instruction.cpp

Library.o : Library.cpp Library.h
	$(CXX) $(CXXFLAGS) Library.cpp

Table.o : Table.cpp Table.h
	$(CXX) $(CXXFLAGS) Table.cpp

# clean all *.o files and executables
clean:
	rm -f *.o $(PROGRAM)

# clean all *.o files
cleano:
	rm -f *.o