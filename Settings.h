#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
using namespace sf;
#define Delete_Key 8
#define Enter_Key 13
#define Escape_Key 27
#define Space_Key 32

class Settings
{
public:

	Settings(float w, float h);
	~Settings();
	void draw(RenderWindow& window);
	void TypeOn(Event input);
	void addChar(int charTyped);
	void DeleteLastChar();
	std::string getString();
	int getVolumee();

private:
	Font font;
	Text message,message1,textbox;
	int limit;
	int volume;
	std::ostringstream text;
	Texture texture;
};

