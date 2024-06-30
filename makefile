all:
	g++ -o game game.cpp `sdl2-config --cflags --libs`
	./game