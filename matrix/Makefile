all: main.o matrix.o
	g++ -std=c++17 -g -Wall $^

main.o: main.cpp
	g++ -std=c++17 -c -g -Wall $^ -o $@

matrix.o: matrix.cpp
	g++ -std=c++17 -c -g -Wall $^ -o $@

clean:
	rm -f *.o *.out