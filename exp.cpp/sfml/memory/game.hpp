#pragma once

#include "menu.hpp"
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();

	bool ok() const;

	void process();
	void update();
	void draw();
	void play();
	void options();

	void old();

private:		
	int scene_ = 1;
	int playingScene_ = 0;
 	sf::RenderWindow window_;
 	sf::Text text_;
 	sf::Font font_;
 	sf::Texture texture_;
 	sf::Sprite sprite_;
 	Menu menu_;
 	bool menuIsActive_ = true;
};
