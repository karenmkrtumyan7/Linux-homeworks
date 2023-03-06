CPP=g++
FLAGS=-Wall

init:
	$(CPP) $(FLAGS) -o init init.cpp

destroy:
	$(CPP) $(FLAGS) -o destroy destroy.cpp

check:
	$(CPP) $(FLAGS) -o check check.cpp

set:
	$(CPP) $(FLAGS) -o set set.cpp

run: init destroy check set
	./init
	./set
	./check 3
	./destroy
