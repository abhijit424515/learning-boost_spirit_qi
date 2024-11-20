all: main.cc
	g++ -o runme main.cc -lboost_system -lboost_filesystem

clean:
	rm -f runme