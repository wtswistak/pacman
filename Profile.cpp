#include "Profile.h"
#include <iostream>

using namespace std;


bool compare(PlayerData a, PlayerData b)
{
	return a.score > b.score;
}
Profile::Profile(float width, float height)
{
	font.loadFromFile("font/font.ttf");

	textbox.setFont(font);
	textbox.setFillColor(Color::White);
	textbox.setPosition(20, 20);
	textbox.setCharacterSize(20);
	textbox.setString("Podaj swoja nazwe: ");
	
	message.setFillColor(Color::White);
	message.setFont(font);
	message.setString("Nacisnij enter aby zatwierdzic");
	message.setPosition(20,50);
	message.setCharacterSize(18);

	message1.setFont(font);
	message1.setFillColor(Color::Red);
	message1.setString("Nacisnij ESC aby wrocic");
	message1.setCharacterSize(18);
	message1.setPosition(20, 500);
	limit = 9;
}

void Profile::TypeOn(Event input)
{
	int charTyped = input.text.unicode;
	if (charTyped < 126)
	{
		if (text.str().length() <= limit)
			addChar(charTyped);
		else if (text.str().length() > limit && charTyped == Delete_Key)
			DeleteLastChar();
	}
}

void Profile::addChar(int charTyped)
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
	textbox.setString("Podaj swoja nazwe: " + text.str() + "_");
	textbox.setPosition(20, 20);
}

void Profile::DeleteLastChar()
{
	std::string modifiedString = text.str();
	if (!modifiedString.empty())
		modifiedString.pop_back();
	text.str("");
	text << modifiedString;
	textbox.setString("Podaj swoja nazwe: " + text.str());
	textbox.setPosition(20, 20);
}

void Profile::setScore(int n_score)
{
	fileScore = n_score;

}

void Profile::addToFile()
{
	vector <PlayerData> playersData;

	ifstream readFromFile;
	readFromFile.open("Ranking.txt");

	while (!readFromFile.eof()) {

		PlayerData player;
		readFromFile >> player.name;
		if (player.name.empty()) continue;
		readFromFile >> player.score;
		playersData.push_back(player);
	}

	readFromFile.close();

	playersData.push_back({ fileScore, text.str() });
	sort(playersData.begin(), playersData.end(), compare);

	ofstream writeToFile;
	writeToFile.open("Ranking.txt");

	for (int i = 0; i < min(10, int(playersData.size())); ++i) {

		writeToFile << playersData[i].name;
		writeToFile << ' ';
		writeToFile << playersData[i].score;
		writeToFile << ' ';
		writeToFile << '\n';
	}
	writeToFile.close();
	text.str("");
	textbox.setString("Podaj swoja nazwe: ");
	textbox.setPosition(20, 20);
}

std::string Profile::getString()
{
	return text.str();
}

void Profile::draw(RenderWindow & window)
{
	window.clear(Color(0, 0, 0));
	window.draw(textbox);
	window.draw(message);
	window.draw(message1);

}