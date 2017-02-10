SRC := $(wildcard *.cpp)
OBJ := $(SRC:.cpp=.o)
EXC := test
CXX := g++
FLAG := -std=c++11 -Wall -Wextra

all: $(EXC)

$(EXC): $(OBJ)
	$(CXX) $(FLAG) $? -o $@

%.o:%.cpp
	$(CXX) $(FLAG) -c $< -o $@

.PHONY:clean
clean: $(EXC) $(OBJ)
	$(RM) $?

