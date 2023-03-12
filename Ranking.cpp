#include "Ranking.h"
#include <fstream>

Ranking::Ranking(float width, float height)
{
	font.loadFromFile("font/font.ttf");

	nameR.setFont(font);
	scoreR.setFont(font);
	nameR.setCharacterSize(20);
	scoreR.setCharacterSize(20);

	title.setFillColor(Color::White);
	
	title.setFont(font);
	title.setString("Ranking");
	title.setPosition(330,10);
	title.setCharacterSize(30);
}
Ranking::~Ranking(){
}

void Ranking::draw(RenderWindow & window)
{
	window.clear(Color(0, 0, 0));
	window.draw(title);
	float length = 6;
	int rank = 1;
	std::ifstream readFromFile;
	readFromFile.open("Ranking.txt");
	nameR.setString("Nazwa:");
	scoreR.setString("Punkty:");

	nameR.setPosition(20,10* length);
	scoreR.setPosition(200,10* length);
	
	window.draw(nameR);
	window.draw(scoreR);

	while (!readFromFile.eof()) {
		length += 3;
		PlayerData player;
		readFromFile >> player.name;
		if (player.name.empty()) continue;
		nameR.setString(std::to_string(rank) + " - " + player.name);
		readFromFile >> player.score;
		scoreR.setString(std::to_string(player.score));

		nameR.setPosition(20,10* length);
		scoreR.setPosition(200,10*length);
		
		window.draw(nameR);
		window.draw(scoreR);
		
		++rank;
	}


	readFromFile.close();
}