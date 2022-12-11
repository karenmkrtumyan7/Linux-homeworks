compile_prog1:
	@gcc ../T1/t1.c -c
compile_prog2:
	@gcc ../T2/t2.c -c
link:
	@gcc t1.o -o prog1
	@gcc t2.o -o prog2

run: compile_prog1 compile_prog2 link
	@./prog1 10000 0 100 data
	@./prog2 1000 2 data
