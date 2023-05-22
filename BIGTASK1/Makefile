run: main.cpp
	g++ main.cpp -o main

compile: run

release: compile
	./main 4

debug:
	g++ main.cpp -o run -Wall -Werror -g -fsanitize=address,undefined
