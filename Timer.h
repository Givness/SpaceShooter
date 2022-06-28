#pragma once
#include "SFML/System.hpp"

extern class Timer
{
public:
	Timer(float time);
	bool timeIsUp();

private:
	float time;
	sf::Clock clock;
};