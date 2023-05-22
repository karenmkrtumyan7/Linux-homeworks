buildlib:
	g++ -std=c++11 -shared -fPIC colorprint.cpp -o libcolorprint.so
	g++ -std=c++11 -c colorprint.cpp
	ar rcs libcolorprint.a colorprint.o

clean:
	rm libcolorprint.so libcolorprint.a library.o
