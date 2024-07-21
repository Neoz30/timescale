all:
	g++ -o game game.cpp `sdl2-config --cflags --libs`
	./game
windows:
	g++ -I src\include -L src\lib -o game.exe game.cpp -Wall -lSDL2main -lSDL2