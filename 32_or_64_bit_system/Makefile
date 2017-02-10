SOURCE := $(wildcard *.c)
HEADER := $(wildcard *.h*)
OBJECTS := $(SOURCE:.c=.o)
EXECUTE := test
CXX := gcc-4.7
CPPFLAG := -g 

all: $(EXECUTE)

$(EXECUTE): $(OBJECTS) $(HEADER)
	$(CXX) $(CPPFLAG) $? -o $@

%.o: %.cpp $(HEADER)
	$(CXX) -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(OBJECTS) $(EXECUTE)


