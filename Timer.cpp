#include "Timer.h"


Timer::Timer(float time) : time(time)
{
	clock = sf::Clock();
	clock.restart();
};

bool Timer::timeIsUp()
{
	if (clock.getElapsedTime().asSeconds() >= time)
	{
		clock.restart();
		return true;
	}
	else return false;
};