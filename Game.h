#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML\Window.hpp> 

using namespace sf;
using namespace std;
class Game
{
public:
	static const int width = 50;
	static const int height = 35;
	const int rozmiar = 15;
	int plansza[width][height] = { 0 };
	Clock clock;
	Game(float w, float h);
	~Game();
	void Drop(int x, int y);
	void lives();
	void table();
	void play(RenderWindow & window);
	int getScore();
	struct aEnemy
	{
		int x = 350;
		int y = 250;
		int dx = rand() % 2 - rand() % 5;
		int dy = rand() % 2 - rand() % 5;

		void move()
		{
			if (dx == 0){dx++;}
			if (dy == 0){dy++;}
			x += dx;
			y += dy;
		}
	};
	int live = 3;
private:
	int x = 0;
	int y = 0;
	int dx = 0;
	int dy = 0;
	
	int enemies = 3;
	int score= 0;
	int maxScore= 1050;
	bool koniec = false;
	bool windowBool = true;
	Font font;
	Text textScore,textLive,przegrana, wygrana;
	bool game = true;
	bool checkWin = true;
	
};
