linux:
	g++ -o game game.cpp `sdl2-config --cflags --libs` -lSDL2_image

windows:
	g++ -I src\include -L src\lib -o game.exe game.cpp -Wall -lSDL2main -lSDL2 -lSDL2_image