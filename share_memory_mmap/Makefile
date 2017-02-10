SRC := $(wildcard *.cpp)
OBJ := $(SRC:.cpp=.o)
EXC = test
LBOOST = -L/usr/local/Cellar/boost/1.58.0/lib -lpthread -lboost_system-mt -lboost_filesystem-mt -lboost_thread-mt
IBOOST = -I/usr/local/Cellar/boost/1.58.0/include
CXXFLAG = -std=c++11 -Wall -lpthread

all: $(EXC)

$(EXC):$(OBJ)
	$(CXX) $(CXXFLAG) $(LBOOST) -o $@ $? 

%.o:%.cpp
	$(CXX) $(CXXFLAG) $(IBOOST) -c $< -o $@

.PHONY:clean
clean:
	rm -f test *.o
