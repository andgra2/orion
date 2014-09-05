all:
	g++ -std=c++11 -Wall -Wextra main.cpp code.cpp machine.cpp program.cpp -o test
clean:
	rm -f *.o test

