
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML\Window.hpp> 
#include <SFML/Audio.hpp>
#include "Game.h"
#include "Settings.h"
#include "Ranking.h"
#include "Menu.h"


using namespace std;
using namespace sf;


enum { startMenu, gierka ,ustawienia, profileKont, rankingGraczy };
int currentMenu;
int main()
{
	RenderWindow window{ VideoMode(740,600), "Pac-Xon",Style::Default };
	Game game(window.getSize().x, window.getSize().y);;
	Menu menu(window.getSize().x, window.getSize().y);
	Settings settings(window.getSize().x, window.getSize().y);
	Profile profile(window.getSize().x, window.getSize().y);
	Ranking ranking(window.getSize().x, window.getSize().y);
	Music music;
	music.openFromFile("music.wav");
	music.play();
	music.setLoop(true);
	float setVolume();
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)window.close();
			if (currentMenu == startMenu)
			{
				if (event.type == Event::KeyReleased)
				{
					if (event.key.code == Keyboard::Up)menu.moveUp();
					else if (event.key.code == Keyboard::Down)menu.moveDown();
					else if (event.key.code == Keyboard::Return)
					{
						if (menu.menuPres() == 0) {
							currentMenu = gierka;
						}
						else if (menu.menuPres() == 1)currentMenu = profileKont;
						else if (menu.menuPres() == 2)currentMenu = rankingGraczy;
						else if (menu.menuPres() == 3)currentMenu = ustawienia;

						else window.close();
					}
				}
			}
			else if (currentMenu == gierka)
			{
				if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape) {
					profile.setScore(game.getScore());
					
					currentMenu = startMenu;
					
				}
			}
			else if (currentMenu == profileKont)
			{

				if (event.type == Event::TextEntered)
				{
					profile.TypeOn(event);
					
				}
				else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Return && !profile.getString().empty())
				{
					currentMenu = startMenu;
					profile.addToFile();
					}
				else if (event.key.code == Keyboard::Escape)currentMenu = startMenu;


			}
			else if (currentMenu == rankingGraczy)
			{
				if (event.key.code == Keyboard::Escape) {
					currentMenu = startMenu;
				}
			}

			else if (currentMenu == ustawienia)
			{
				if (event.type == Event::TextEntered)
				{
					settings.TypeOn(event);
				}
				else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Return)
				{
					music.setVolume(settings.getVolumee());
					currentMenu = startMenu;
				}
				else if (event.key.code == Keyboard::Escape)
				{
					currentMenu = startMenu;
				}


			}
		}
		window.clear();
		menu.draw(window);

		if (currentMenu == ustawienia)
			settings.draw(window);
		else if (currentMenu == gierka)
			{	
			game.play(window);
			profile.setScore(game.getScore());
			}

		else if (currentMenu == profileKont)
			profile.draw(window);
		else if (currentMenu == rankingGraczy)
			ranking.draw(window);
		
		
		window.display();
	}

	return 0;
}
