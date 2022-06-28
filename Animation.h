#pragma once
#include "Timer.h"
#include <SFML/Graphics.hpp>
#include <list>

class Animation
{
public:
	Animation(float fps);
	void addImage(sf::Image image);
	void addImage(std::string imageFileName);
	sf::Image nextFrame();

private:
	short frame;
	std::list<sf::Image> images;
	Timer timer;
};