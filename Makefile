all: compile link

compile:
	g++ -Isrc/include -c main.cpp

link:
	g++ main.o -o test -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system