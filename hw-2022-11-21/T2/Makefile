compile_prog1:
	@gcc prog1.c -c
compile_prog2:
	@gcc prog2.c -c
link:
	@gcc prog1.o -o prog1
	@gcc prog2.o -o prog2

run: compile_prog1 compile_prog2 link
	@./prog2 2
