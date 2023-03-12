#pragma once
#include <sfml/Graphics.hpp>
#include "Profile.h"
class Ranking
{
public:
	Ranking(float width, float height);
	~Ranking();
	void draw(RenderWindow &window);
	
private:
	
	Font font;
	Text title, scoreR, nameR;
};



