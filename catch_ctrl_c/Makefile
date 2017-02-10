SRC := $(wildcard *.cpp)
OBJ := $(SRC:.cpp=.o)
EXC = test
CPPFLAG = -Wall -g

all:$(EXC)

$(EXC):$(OBJ)
	$(CXX) $(CPPFLAG) $? -o $@

%.o:%.cpp
	$(CXX) -c $< -o $@

.PHONY:clean
clean:
	$(RM) $(EXC) $(OBJ)
