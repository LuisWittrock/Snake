all:
	g++ -c src/main.cpp -I/include
	g++ main.o -o snake -L/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio 