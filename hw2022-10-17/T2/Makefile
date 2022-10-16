compile_str:
	@gcc  str.c -c -Werror -Wall
compile_main:
	@gcc main.c -c -Werror -Wall
link_all:
	@gcc str.o main.o -o task2 -Werror -Wall -g -fsanitize=address,undefined

run: compile_str compile_main link_all
	@./task2 arg arg2 1234567890
