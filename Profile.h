#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Game.h"
#define Delete_Key 8
#define Enter_Key 13
#define Escape_Key 27
#define Space_Key 32

using namespace sf;
struct PlayerData {
	int score;
	std::string name;
};

class Profile
{
public:

	Profile(float width, float height);
	void draw(RenderWindow& window);
	void TypeOn(Event input);
	void addChar(int charTyped);
	void DeleteLastChar();
	void setScore(int n_score);
	void addToFile();
	std::string getString();

private:

	int fileScore;
	std::ostringstream text;
	int limit;
	Text message,message1,textbox;
	Font font;
};