all:
	g++ -c src/main.cpp src/panel.cpp src/frame.cpp src/frame.cpp -I/include
	g++ main.o -o snake -L/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	rm main.o panel.o frame.o 