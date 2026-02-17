all:
	g++ -O3 main.cpp util.cpp -o a.out
clean:
	rm -f a.out output-*.txt