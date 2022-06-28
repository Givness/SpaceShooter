#include "main.h"
#include "GameObject.h"
#include <iostream>

#pragma region GameObject
GameObject::GameObject(const std::string imageFileName)
{
	texture.loadFromFile(imageFileName);
	setTexture(texture);
	setOrigin((sf::Vector2f)texture.getSize() * 0.5f);
};

void GameObject::setScale(float scale)
{
	__super::scale(scale, scale);
	this->scale = scale;
};

void GameObject::setImage(const std::string imageFileName)
{
	texture.loadFromFile(imageFileName);
	setOrigin((sf::Vector2f)texture.getSize() * 0.5f);
};

void GameObject::setImage(sf::Image image)
{
	texture.loadFromImage(image);
	setOrigin((sf::Vector2f)texture.getSize() * 0.5f);
};

void GameObject::setActive(bool value)
{
	isActive = value;
};

bool GameObject::activeSelf()
{
	return isActive;
}

bool GameObject::isTouching(GameObject* object)
{
	return (right() > object->left()) && (left() < object->right()) && (bottom() > object->top()) && (top() < object->bottom());
};

float GameObject::top()
{
	return getPosition().y - texture.getSize().y / 2 * scale;
};

float GameObject::bottom()
{
	return getPosition().y + texture.getSize().y / 2 * scale;
};

float GameObject::left()
{
	return getPosition().x - texture.getSize().x / 2 * scale;
};

float GameObject::right()
{
	return getPosition().x + texture.getSize().x / 2 * scale;
};
#pragma endregion

#pragma region Player
Player::Player(const std::string imageFileName) : GameObject(imageFileName) {}
#pragma endregion

#pragma region Enemy
Enemy::Enemy() : GameObject("resources/Enemy1.png")
{
	speed = 75.f;
};

Enemy::Enemy(const std::string imageFileName) : GameObject(imageFileName)
{
	speed = 75.f;
};

void Enemy::move()
{
	__super::move(0.f, speed * deltaTime);
}
#pragma endregion

#pragma region Bullet
Bullet::Bullet() : GameObject("resources/PlayerBullet.png"), playerOwner(false) {};

Bullet::Bullet(const std::string imageFileName) : GameObject(imageFileName), playerOwner(false) {};

void Bullet::move()
{
	__super::move(0.f, -speed * deltaTime);
	if (getPosition().y < -30.f) isActive = false;
};

void Bullet::setPlayerOwn(bool playerOwner)
{
	if (!this->playerOwner && playerOwner) setImage(blue);
	else if (this->playerOwner && !playerOwner) setImage(red);
	this->playerOwner = playerOwner;
}

void Bullet::setBlue(const std::string imageFileName)
{
	blue.loadFromFile(imageFileName);
}

void Bullet::setRed(const std::string imageFileName)
{
	red.loadFromFile(imageFileName);
}

float Bullet::speed = 400.f;
sf::Image Bullet::blue = sf::Image();
sf::Image Bullet::red = sf::Image();
#pragma endregion

#pragma region Star
Star::Star()
{
	radius = (rand() % 3 + 1) * 1.5;
	setSize(sf::Vector2f(radius, radius));
	setFillColor(sf::Color::White);
	setOrigin(radius / 2, radius / 2);
	speed = 30.f * radius;
};

void Star::move()
{
	__super::move(0.f, speed * deltaTime);
	if (getPosition().y > gameHeight)
	{
		Star();
		setPosition(rand() % gameWidth, 0);
	}
};
#pragma endregion