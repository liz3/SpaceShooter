//
// Created by Yann Holme Nielsen on 09.09.17.
//

#ifndef UNTITLED_OBJECT_H
#define UNTITLED_OBJECT_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio.hpp>


struct Astroid {
	unsigned x, y, health;
	sf::Sprite sprite;
	bool dead = false;
	bool outOfRange = false;

};
struct Projectile {
	unsigned x,y;
	bool hit = false;
};
struct Sound {
private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
public:
	Sound(std::string file) {

		if(buffer.loadFromFile(file)) {
			sound.setBuffer(buffer);
		}

	}
	void play() {
		sound.play();
	}



};

#endif //UNTITLED_OBJECT_H
