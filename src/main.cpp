#include <iostream>
#include "Game.h"

int main(int argc, char **argv) {

	std::cout << "Starting the Programm" << std::endl;
	Game game(800, 800);
	game.run();


	return 0;

}