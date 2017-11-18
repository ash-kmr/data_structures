default: output

output: main.o
	g++ main.o -o output

main.o: main.cpp
	g++ -c main.cpp -o main.o

clean:
	rm -f *.o ./output