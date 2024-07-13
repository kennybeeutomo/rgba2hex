output: main.cpp
	g++ -O2 main.cpp -o $(HOME)/bin/rgba2hex

test:
	rgba2hex rgba(2,3,4,5)
