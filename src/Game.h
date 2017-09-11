//
// Created by Yann Holme Nielsen on 09.09.17.
//

#ifndef UNTITLED_GAME_H
#define UNTITLED_GAME_H

#include "Object.h"
#include <SFML/Graphics.hpp>



class Game {
public:
	Game(unsigned width, unsigned height);
	void run();

private:
	//Voids
	void drawRectangle(std::vector<sf::Vertex> &array, float x, float y, float width, float height, sf::Color color = sf::Color::White);
	void checkInputs();
	void moveObjects();
	void checkCollision();
	void checkVals();
	void draw();

	int randomPos() {
		return 0 + (rand() % static_cast<int>((window.getSize().y - 30) - 30 + 1));
	}

	//Properties
	int createCount = 0;
	int createNeed = 60;
	int points = 0;
	int total = 0;
	double life = 100;

	bool btnPressed;
	int currentPos = 0;

	sf::Font m_font;
	sf::Text player_text;


	Sound shootSound = Sound("/Users/liz3/CLionProjects/untitled/assets/151022__bubaproducer__laser-shot-silenced.wav");

	//Arrays
	std::vector<Astroid> enemies = std::vector<Astroid>();
	std::vector<Projectile> bullets = std::vector<Projectile>();
	std::vector<sf::Vertex> renderArray = std::vector<sf::Vertex>();

	//Player
	sf::Texture texture;
	sf::Sprite sprite;

	//AstroidTexture
	sf::Texture asteroidTexture;

	//Render
	sf::RenderWindow window;


};


#endif //UNTITLED_GAME_H
