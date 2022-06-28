#include "main.h"
#include "GameObject.h"
#include "Timer.h"
#include "Animation.h"
#include <iostream>

const int gameWidth = 540;
const int gameHeight = 960;

const float gameBorder = 50.f;

sf::Clock deltaClock;
float deltaTime = 0.f;

float clamp(float value, float min, float max)
{
	return (value > max) ? (max) : (value < min ? min : value);
};

int main()
{
	// Create the window of the application
	sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight, 32), "Space Shooter", sf::Style::None);
	window.setVerticalSyncEnabled(true);

	srand(time(0));

	#pragma region PlayerInitialization
	Player player("resources/Player1.png");
	player.setPosition(gameWidth / 2, 900.f);
	player.setScale(0.5f);
	short playerAnimState = 0;
	short playerAnimStateOld = 0;
	Timer timeToChangeAnimation(0.4f);

	Animation idle(5.f);
	idle.addImage("resources/Player1.png");
	idle.addImage("resources/Player2.png");

	Animation moveRight(5.f);
	moveRight.addImage("resources/PlayerRight1.png");
	moveRight.addImage("resources/PlayerRight2.png");

	Animation moveLeft(5.f);
	moveLeft.addImage("resources/PlayerLeft1.png");
	moveLeft.addImage("resources/PlayerLeft2.png");
	#pragma endregion

	#pragma region StarsInitialization
	const int starNumber = 50;
	Star s[starNumber];
	for (int i = 0; i < starNumber; ++i) s[i].setPosition(rand() % gameWidth, rand() % gameHeight);
	#pragma endregion

	#pragma region BulletsInitialization
	int currentBullet = 0;

	Bullet::setBlue("resources/PlayerBullet.png");
	Bullet::setRed("resources/EnemyBullet.png");

	const int bulletsNumber = 20;
	Bullet b[bulletsNumber];

	for (int i = 0; i < bulletsNumber; ++i)
	{
		b[i].setPosition(-50.f, -50.f);
		b[i].setScale(0.4f);
		b[i].setActive(false);
	}


	Timer shotTimer(0.2f);
	bool isShooting = false;
	#pragma endregion

	#pragma region EnemiesInitialization
	const int enemiesNumber = 5;
	Enemy e[enemiesNumber];

	for (int i = 0; i < enemiesNumber; ++i)
	{
		e[i].setPosition(rand() % (gameWidth - 2 * (int)gameBorder) + gameBorder, -i * 300.f);
		e[i].setScale(0.5f);
		e[i].setActive(true);
	}

	Animation enemyIdle(5.f);
	enemyIdle.addImage("resources/Enemy1.png");
	enemyIdle.addImage("resources/Enemy2.png");
	#pragma endregion

	deltaClock.restart();

	while (window.isOpen())
	{
		// Handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Window closed or escape key pressed: exit
			if ((event.type == sf::Event::Closed) ||
				((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
			{
				window.close();
				break;
			}

			if ((event.type == sf::Event::MouseButtonPressed) && (event.key.code == sf::Mouse::Left)) isShooting = true;
			if ((event.type == sf::Event::MouseButtonReleased) && (event.key.code == sf::Mouse::Left)) isShooting = false;
		}

		if (isShooting)
		{
			if (shotTimer.timeIsUp())
			{
				b[currentBullet].setPlayerOwn(true);
				//b[currentBullet].setImage("resources/PlayerBullet.png");
				b[currentBullet].setPosition(player.getPosition());
				b[currentBullet].setActive(true);
				if (++currentBullet >= bulletsNumber) currentBullet = 0;
			}
		}

		float playerX = clamp(sf::Mouse::getPosition().x - window.getPosition().x, gameBorder, gameWidth - gameBorder);
		float playerY = clamp(sf::Mouse::getPosition().y - window.getPosition().y, gameBorder, gameHeight - gameBorder);

		float playerXOld = player.getPosition().x;

		if (playerX - playerXOld > 5.f) playerAnimState = 1;
		else if (playerX - playerXOld < -5.f) playerAnimState = -1;
		else playerAnimState = 0;

		if (playerAnimState == playerAnimStateOld)
		{
			switch (playerAnimState)
			{
			case -1:
				player.setImage(moveLeft.nextFrame());
				break;
			case 0:
				player.setImage(idle.nextFrame());
				break;
			case 1:
				player.setImage(moveRight.nextFrame());
				break;
			}
		}
		else if (timeToChangeAnimation.timeIsUp()) playerAnimStateOld = playerAnimState;

		player.setPosition(sf::Vector2f(playerX, playerY));

		for (int i = 0; i < starNumber; ++i)
		{
			s[i].move();
		}


		for (int i = 0; i < bulletsNumber; ++i)
		{
			if (b[i].activeSelf())
			{
				b[i].move();
			}
		}

		for (int i = 0; i < enemiesNumber; ++i)
		{
			if (e[i].activeSelf())
			{
				e[i].move();
				e[i].setImage(enemyIdle.nextFrame());
				for (int j = 0; j < bulletsNumber; ++j)
				{
					if (b[j].activeSelf() && e[i].isTouching(&b[j]))
					{
						e[i].setActive(false);
						b[j].setActive(false);
					}
				}
			}
		}

		window.clear(sf::Color(10, 10, 24));
		deltaTime = deltaClock.restart().asSeconds();

		for (int i = 0; i < starNumber; ++i)
			window.draw(s[i]);

		for (int i = 0; i < bulletsNumber; ++i)
			if (b[i].activeSelf())
				window.draw(b[i]);
		
		for (int i = 0; i < enemiesNumber; ++i)
			if (e[i].activeSelf()) 
				window.draw(e[i]);

		window.draw(player);

		window.display();
	}

	return EXIT_SUCCESS;
}