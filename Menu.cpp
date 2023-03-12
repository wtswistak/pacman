#include "Menu.h"
#include <iostream>
using namespace std;


Menu::Menu(float w, float h) {
	font.loadFromFile("font/font.ttf");

	menu[0].setFont(font);
	menu[0].setFillColor(Color::White);
	menu[0].setString("Graj");
	menu[0].setCharacterSize(30);
	menu[0].setPosition(20, 80);

	menu[1].setFont(font);
	menu[1].setFillColor(Color::White);
	menu[1].setString("Zarzadzanie profilami");
	menu[1].setCharacterSize(30);
	menu[1].setPosition(20, 120);

	menu[2].setFont(font);
	menu[2].setFillColor(Color::White);
	menu[2].setString("Ranking");
	menu[2].setCharacterSize(30);
	menu[2].setPosition(20, 160);

	menu[3].setFont(font);
	menu[3].setFillColor(Color::White);
	menu[3].setString("Ustawienia");
	menu[3].setCharacterSize(30);
	menu[3].setPosition(20, 200);

	menu[4].setFont(font);
	menu[4].setFillColor(Color::White);
	menu[4].setString("Wyjdz");
	menu[4].setCharacterSize(30);
	menu[4].setPosition(20, 240);

	menuSelect = -1;
}
Menu::~Menu()
{

}
void Menu::draw(RenderWindow& window)
{
	window.clear(Color(0, 0, 0));
	for (int i = 0; i < maxNum; ++i)
	{
		window.draw(menu[i]);
	}
}

void Menu::moveUp()
{
	if (menuSelect - 1 >= 0)
	{
		menu[menuSelect].setFillColor(Color::White);
		menuSelect--;
		menu[menuSelect].setFillColor(Color::Blue);
	}

}

void Menu::moveDown() {
	if (menuSelect + 1 <= maxNum)
	{
		menu[menuSelect].setFillColor(Color::White);


		menuSelect++;
		if (menuSelect == 5)
		{
			menuSelect = 4;
		}
		menu[menuSelect].setFillColor(Color::Blue);

	}

}
