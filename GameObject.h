#pragma once
#include <SFML/Graphics.hpp>

extern class GameObject : public sf::Sprite
{
public:
	GameObject(const std::string imageFileName);
	void setImage(const std::string imageFileName);
	void setImage(sf::Image image);
	bool isTouching(GameObject* object);
	void setScale(float scale);
	void setActive(bool value);
	bool activeSelf();

protected:
	bool isActive;
	float scale;
	sf::Texture texture;
	float top();
	float bottom();
	float left();
	float right();
};

extern class Bullet : public GameObject
{
public:
	Bullet();
	Bullet(const std::string imageFileName);
	void move();
	void setPlayerOwn(bool playerOwner);
	static void setBlue(const std::string imageFileName);
	static void setRed(const std::string imageFileName);

private:
	bool playerOwner;
	static float speed;
	static sf::Image blue;
	static sf::Image red;
};

extern class Player : public GameObject
{
public:
	Player(const std::string imageFileName);
};

extern class Enemy : public GameObject
{
public:
	Enemy();
	Enemy(const std::string imageFileName);
	void move();

private:
	float speed;
};

extern class Star : public sf::RectangleShape
{
public:
	Star();
	void move();

private:
	float speed;
	float radius;
};