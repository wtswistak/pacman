#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\Window.hpp> 

using namespace sf;
#define maxNum 5
class Menu
{
public:
	Menu(float w, float h);
	~Menu();
	void draw(RenderWindow& window);
	void moveUp();
	void moveDown();

	int menuPres()
	{
		return menuSelect;
	}

	
private:
	int menuSelect;
	Font font;
	Text menu[maxNum];

};