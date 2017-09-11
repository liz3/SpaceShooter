//
// Created by Yann Holme Nielsen on 09.09.17.
//

#include <vector>
#include <iostream>
#include "Game.h"

Game::Game(unsigned width, unsigned height)
		: window({width, height}, "Super shooter") {

	window.setFramerateLimit(30);

	currentPos = height / 2;

	if (texture.loadFromFile("/Users/liz3/CLionProjects/untitled/assets/rocket.png")) {
		texture.setSmooth(true);
		texture.setRepeated(false);
		sprite.setTexture(texture);
	}
	if (asteroidTexture.loadFromFile("/Users/liz3/CLionProjects/untitled/assets/asteroid.png")) {
		asteroidTexture.setSmooth(true);
		asteroidTexture.setRepeated(false);
	}

	m_font.loadFromFile("/Users/liz3/CLionProjects/Conway-s-Game-Of-Life/font/arial.ttf");
	player_text.setFont(m_font);
	player_text.setFillColor(sf::Color::White);
	player_text.setOutlineColor(sf::Color::Black);
	player_text.setOutlineThickness(3);
	player_text.setCharacterSize(15);
	player_text.setPosition(5, 5);
}

void Game::drawRectangle(std::vector<sf::Vertex> &array, float x, float y, float width, float height, sf::Color color) {

	array.push_back(sf::Vertex({x, y}, color));
	array.push_back(sf::Vertex({x + width, y}, color));
	array.push_back(sf::Vertex({x + width, y + height}, color));
	array.push_back(sf::Vertex({x, y + height}, color));
}

void Game::run() {


	while (window.isOpen()) {
		renderArray.clear();
		checkInputs();
		moveObjects();
		checkCollision();
		checkVals();
		draw();
	}
}

void Game::checkInputs() {

	checkCollision();
	sf::Event event{};
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (currentPos >= 20) currentPos -= 15;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (currentPos <= window.getSize().y - 60) currentPos += 15;

	}

	if (!btnPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		btnPressed = true;
		Projectile projectile{};
		projectile.x = 50;
		projectile.y = static_cast<unsigned int>(currentPos + 20);
		bullets.push_back(projectile);
		shootSound.play();
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && btnPressed) {
		btnPressed = false;
	}
}


void Game::moveObjects() {

	//Bullets
	std::vector<Projectile> newVector = std::vector<Projectile>();
	for (Projectile &proj : bullets) {
		if (proj.x > window.getSize().x - 10 || proj.hit) {

		} else {
			proj.x += 40;
			newVector.push_back(proj);
		}
	}
	bullets.clear();
	bullets = newVector;


	//Asteroids
	std::vector<Astroid> newAsteroids = std::vector<Astroid>();

	for (Astroid &current : enemies) {

		if (current.x > 20 && !current.dead) {
			current.x -= 5;
			newAsteroids.push_back(current);
		} else {
			if(!current.outOfRange && !current.dead) {
				life -= 5;
				current.outOfRange = true;
			}
		}
	}
	if (createCount == 0) {
		for (int i = 0; i < 1; ++i) {
			auto random = randomPos();

			Astroid a = Astroid{};
			a.x = window.getSize().x - 10;
			a.y = random;
			sf::Sprite newSprite;
			newSprite.setTexture(asteroidTexture);
			a.sprite = newSprite;

			newAsteroids.push_back(a);
		}
	}
	createCount++;

	if (createCount >= createNeed) {
		createCount = 0;
	}

	enemies.clear();
	enemies = newAsteroids;

}

void Game::checkCollision() {

	for(Astroid& current : enemies) {
		if(current.dead) continue;
		for (Projectile &proj : bullets) {
			if(proj.hit) continue;
			if(proj.x > current.sprite.getPosition().x - 4&& proj.x < current.sprite.getPosition().x + 40) {
				if(proj.y > current.sprite.getPosition().y - 10&& proj.y < current.sprite.getPosition().y + 40) {
					std::cout << points << "\n";
					std::cout << createNeed << "\n";
					current.dead = true;
					points++;
					proj.hit = true;
					break;
				}
			}
		}
}

	if(points == 10) {

		total++;
		points = 1;
		createNeed -= 2;
	}
}

void Game::draw() {

	window.clear();


	for (Projectile &proj : bullets) {
		drawRectangle(renderArray, proj.x, proj.y - 2, 10, 4);
	}
	for (Astroid &current : enemies) {
		if(current.dead) continue;
		current.sprite.setPosition(current.x, current.y);
		window.draw(current.sprite);
	}

	sprite.setPosition(sf::Vector2f(10, currentPos)); // absolute position

	player_text.setString("Asteroids: " + std::to_string(enemies.size()) + "\nProjectiles: " + std::to_string(bullets.size()) +
			                      "\nRender Objects: " + std::to_string(renderArray.size()) +
			                      "\nPoints: " + std::to_string(points) +
			                      "\nTotal: " + std::to_string(total) +
			                      "\nNeed: " + std::to_string(createNeed) +
			                      "\nCreate Count: " + std::to_string(createCount) +
			                      "\nLife: " + std::to_string(life));

	window.draw(player_text);
	drawRectangle(renderArray, 10, currentPos - 15, static_cast<float>(life / 2), 5, sf::Color::Green);
	window.draw(renderArray.data(), renderArray.size(), sf::Quads);
	window.draw(sprite);
	window.display();

}

void Game::checkVals() {

	if(life == 0) {
		life = 100;
		total = 0;
		points = 0;
		createNeed = 60;

	}
}
