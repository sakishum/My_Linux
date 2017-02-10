EXEC := test

all:
	g++ -std=c++11 -o $(EXEC) main.cpp -lpthread -O3

check:
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --dsymutil=yes ./$(EXEC)

clean:
	rm -f test
