#pragma once
#include <SFML/Graphics.hpp>

#define MAX_NUMBER_OF_ITEMS 3

class Menu
{
public:
	Menu(float with, float height);
	~Menu();
	
	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() {return selectedItemIndex;}
	void Play(sf::RenderWindow &window);

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
}; 