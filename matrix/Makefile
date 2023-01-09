all: main.o matrix.o Verifier.o
	g++ -std=c++17 -g -Wall $^

main.o: main.cpp
	g++ -std=c++17 -c -g -Wall $^ -o $@

matrix.o: matrix.cpp matrix.h
	g++ -std=c++17 -c -g -Wall $< -o $@

Verifier.o: Verifier.cpp Verifier.h
	g++ -std=c++17 -c -g -Wall $< -o $@

clean:
	rm -f *.o *.out