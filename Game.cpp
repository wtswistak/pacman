#pragma once
#include"Game.h"


Game::Game(float w, float h)
{
	font.loadFromFile("font/font.ttf");
	textScore.setFillColor(Color::White);
	textScore.setFont(font);
	textScore.setPosition(10, 525);
	textScore.setCharacterSize(20);
	
	textLive.setFillColor(Color::White);
	textLive.setFont(font);
	textLive.setPosition(10, 550);
	textLive.setCharacterSize(20);

	przegrana.setFillColor(Color::White);
	przegrana.setFont(font);
	przegrana.setCharacterSize(70);
	przegrana.setString("Przegrana");
	przegrana.setPosition(200, 80);

	wygrana.setFillColor(Color::White);
	wygrana.setFont(font);
	wygrana.setCharacterSize(70);
	wygrana.setString("Wygrana");
	wygrana.setPosition(200, 80);
}

Game::~Game()
{


}
void Game::lives() {
		live--;
		x = 1;
		y = 1;

		if (live == 0)
		{
			game = false;
		}
	}
void Game::Drop(int x, int y)
{
	if (plansza[x][y] == 0){plansza[x][y] = -1;}
	if (plansza[x - 1][y] == 0){Drop(x - 1, y);}
	if (plansza[x + 1][y] == 0){Drop(x + 1, y);}
	if (plansza[x][y - 1] == 0){Drop(x, y - 1);}
	if (plansza[x][y + 1] == 0){Drop(x, y + 1);}
}


void Game::table() {
	for (int i = 1; i < width; i++)
	{
		for (int j = 1; j < height; j++)
		{
			if (i == 1 || j == 1  || i == width - 1 || j == height - 1)
			{
				plansza[i][j] = 1;
			}
			else
			{
				plansza[i][j] = 0;
			}
		}
	}
}

void Game::play(RenderWindow & window) {
	
	window.setFramerateLimit(60);
	Texture tWall, tEnemy, tPac;

	tPac.loadFromFile("obrazy/pac.png");
	tWall.loadFromFile("obrazy/sciana.png");
	tEnemy.loadFromFile("obrazy/enemy.png");

	aEnemy a[10];
	Sprite sWall(tWall), sEnemy(tEnemy), sPac(tPac);

	sPac.setOrigin(15, 15);
	sWall.setOrigin(15, 15);
	sEnemy.setOrigin(20, 20);
	
	table();
	while (window.isOpen())
	{


		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
				windowBool = false;
			}
		
			if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape) { windowBool = false;}
		}	
		if(windowBool == false) break;
		if (Keyboard::isKeyPressed(Keyboard::Up)) { dx = 0; dy = -1; }	
		if (Keyboard::isKeyPressed(Keyboard::Down)) { dx = 0; dy = 1; }
		if (Keyboard::isKeyPressed(Keyboard::Right)) { dx = 1; dy = 0; }
		if (Keyboard::isKeyPressed(Keyboard::Left)) { dx = -1; dy = 0; }

		if (clock.getElapsedTime().asSeconds() > 0.06)
		{

			x += dx;
			y += dy;

			if (x < 1)
			{
				x = 1;
			}if (y < 1)
			{
				y = 1;
			}if (x > width - 1)
			{
				x = width - 1;
			}if (y > height - 1)
			{
				y = height - 1;
			}if (!game)
			{
				continue;
			}if (!checkWin)
			{
				continue;
			}if (plansza[x][y] == 2)
			{
				lives();

			}for (int i = 0; i < enemies; i++)
			{
				if (x == a[i].x && y == a[i].y)
				{
					lives();
					a[i].dx = -a[i].dx;
					a[i].dy = -a[i].dy;

				}
			}
			if (plansza[x][y] == 0)
			{
				plansza[x][y] = 2;
			}

			clock.restart();
		}
		
		for (int i = 0; i < enemies; i++)
		{
			a[i].move();
			if (plansza[a[i].x / rozmiar][a[i].y / rozmiar] == 1)
			{
				a[i].dx = -a[i].dx;
				a[i].x += a[i].dx;
			}	if (plansza[a[i].x / rozmiar][a[i].y / rozmiar] == 1)
			{
				a[i].dy = -a[i].dy;
				a[i].y += a[i].dy;
			}
			if (plansza[a[i].x / rozmiar][a[i].y / rozmiar] == 2)
			{
				lives();
			}

		}

		if (plansza[x][y] == 1)
		{
			dx = dy = 0;
			for (int i = 0; i < enemies; i++)
			{
				Drop(a[i].x / rozmiar, a[i].y / rozmiar);
			}
			for (int i = 1; i < width - 1; i++)
			{
				for (int j = 1; j < height - 1; j++)
				{
					if (plansza[i][j] == -1)
					{
						plansza[i][j] = 0;
					}
					else
					{
						plansza[i][j] = 1;
					}
				}
			}
		}

		score = 0;
		for (int i = 2; i < 49; i++)
		{
			for (int j = 2; j < 34; j++)
			{
				if (plansza[i][j] == 1) { score++; }
				if (score > maxScore) { checkWin = false; }
			}
		}
		if (clock.getElapsedTime().asSeconds() >= 60)
		{
			game = false;
			clock.restart();
		}
		window.clear();

		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				if (plansza[i][j] == 0) {
					continue;
				}if (plansza[i][j] == 1) {
					sWall.setTextureRect(IntRect(0, 0, 15, 15));
				}if (plansza[i][j] == 2) {
					sWall.setTextureRect(IntRect(15, 0, 15, 15));
				}

				sWall.setPosition(i * rozmiar, j * rozmiar);
				window.draw(sWall);
			}
		}


		for (int i = 0; i < enemies; i++)
		{
			sEnemy.setPosition(a[i].x, a[i].y);
			window.draw(sEnemy);
		}
		if (game == false)window.draw(przegrana);
		if (checkWin == false)window.draw(wygrana);
		sPac.setPosition(x * rozmiar, y * rozmiar);
		window.draw(sPac);
		textScore.setString("Punkty: " + to_string(score));
		window.draw(textScore);
		textLive.setString("Zycia: " + to_string(live));
		window.draw(textLive);
		window.display();
		if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape) {windowBool = false; window.clear(); }
	

}

};
int Game::getScore() {
	return score;
}
