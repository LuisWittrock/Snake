all:
	g++ -c src\main.cpp -Isrc\include
	g++ main.o -o snake -Lsrc\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio 