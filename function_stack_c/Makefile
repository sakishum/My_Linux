SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)
EXC = test
CXXFLAG =  -Wall

all:$(EXC)

$(EXC):$(OBJ)
	gcc $(CXXFLAG) $? -o $@

%.o:%.cpp
	gcc $(CXXFLAG) -c $? -o $@

.PHONY:clean
claen: 
	$(RM) $(OBJ) $(EXC)
