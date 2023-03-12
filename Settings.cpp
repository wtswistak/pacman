#include "Settings.h"
#include <vector>
#include <fstream>
#include <algorithm>

Settings::Settings(float w, float h)
{
	font.loadFromFile("font/font.ttf");
	textbox.setFont(font);
	textbox.setFillColor(Color::White);
	textbox.setPosition(20,20);
	textbox.setCharacterSize(20);
	textbox.setString("Wpisz poziom glosnosci od 1-100: ");

	message.setFont(font);
	message.setString("Nacisnij enter zaby zatwierdzic");
	message.setPosition(20, 50);
	message.setCharacterSize(18);

	message1.setFont(font);
	message1.setFillColor(Color::Red);
	message1.setString("Nacisnij ESC aby wrocic");
	message1.setCharacterSize(18);
	message1.setPosition(20, 500);

	limit = 2;
	
}

Settings::~Settings()
{
}



	void Settings::TypeOn(Event input)
	{
	int charTyped = input.text.unicode;
	if (charTyped > 1 && charTyped < 58)
	{
		if (text.str().length() <= limit)
			addChar(charTyped);
		else if (text.str().length() > limit && charTyped == Delete_Key)
			DeleteLastChar();
	}
	}
	void Settings::addChar(int charTyped)
	{
		if (charTyped != Delete_Key && charTyped != Escape_Key && charTyped != Enter_Key && charTyped != Space_Key)
		{
			text << char(charTyped);
		}
		else if (charTyped == Delete_Key)
		{
			if (text.str().size() > 0)
			{
				DeleteLastChar();
			}
		}
		textbox.setString("Wpisz poziom glosnosci od 1-100: " + text.str() + "_");
		textbox.setPosition(20,20);
	}

	void Settings::DeleteLastChar()
	{
		std::string modifiedString = text.str();
		if (!modifiedString.empty())
			modifiedString.pop_back();
		text.str("");
		text << modifiedString;
		textbox.setString("Wpisz poziom glosnosci od 1-100: "+ text.str());
		textbox.setPosition(20, 20);
	}
	int Settings::getVolumee()
	{
		std::string str_num = getString();
		volume = std::stoi(str_num);
		return volume;
	}
	

	std::string Settings::getString()
	{
		return text.str();
	}
	void Settings::draw(RenderWindow& window)
	{
		window.clear(Color(0, 0, 0));
		window.draw(textbox);
		window.draw(message);
		window.draw(message1);
	}

