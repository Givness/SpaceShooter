#include "Animation.h"

Animation::Animation(float fps) : timer(1.f / fps) {}

void Animation::addImage(sf::Image image)
{
	images.push_back(image);
};

void Animation::addImage(std::string imageFileName)
{
	sf::Image img;
	img.loadFromFile(imageFileName);
	images.push_back(img);
};

sf::Image Animation::nextFrame()
{
	std::list<sf::Image>::iterator iterator = images.begin();
	std::advance(iterator, frame);
	if (timer.timeIsUp()) frame++;
	if (frame >= images.size()) frame = 0;
	return *iterator;
};