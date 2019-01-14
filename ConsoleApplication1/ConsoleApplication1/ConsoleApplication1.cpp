// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "pch.h"
#include <stdlib.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include "DungeonMap.h"
#include "Combat.h"

// Game specifications
constexpr int spriteSize = 32;


struct location
{
	int x;
	int y;
};

enum characterDirection {
	LEFT = 0,
	RIGHT,
	UP,
	DOWN
};

int main()
{


	struct location playerLocation;
	int displayedSection[dungeonDisplay][dungeonDisplay];

	playerLocation.x = startLocationX;
	playerLocation.y = startLocationY;


	sf::RenderWindow window(sf::VideoMode(spriteSize * dungeonDisplay, spriteSize * dungeonDisplay), "Mathieu's Game");


	//0 = Left, 1 = Right, 2 = Up, 3 = down
	sf::Texture playerTextures[4][3];

	if (!playerTextures[0][0].loadFromFile("sprites/KnightLeft1v2.png"))
	{
		std::cout << "error: Image \"KnightLeft1v2\" not found";
	}

	if (!playerTextures[0][1].loadFromFile("sprites/KnightLeft2v2.png"))
	{
		std::cout << "error: Image \"KnightLeft2v2\" not found";
	}

	if (!playerTextures[0][2].loadFromFile("sprites/KnightLeft3v2.png"))
	{
		std::cout << "error: Imag \"KnightLeft3v2\"e not found";
	}
	if (!playerTextures[1][0].loadFromFile("sprites/knightRight1v2.png"))
	{
		std::cout << "error: Image \"KnightRight1v2\" not found";
	}
	if (!playerTextures[1][1].loadFromFile("sprites/knightRight2v2.png"))
	{
		std::cout << "error: Image \"KnightRight2v2\" not found";
	}
	if (!playerTextures[1][2].loadFromFile("sprites/knightRight3v2.png"))
	{
		std::cout << "error: Image \"KnightRight3v2\" not found";
	}
	if (!playerTextures[2][0].loadFromFile("sprites/knightUp1.png"))
	{
		std::cout << "error: Image \"KnightUp1\" not found";
	}
	if (!playerTextures[2][1].loadFromFile("sprites/knightUp2.png"))
	{
		std::cout << "error: Image \"KnightUp2\" not found";
	}
	if (!playerTextures[2][2].loadFromFile("sprites/knightUp3.png"))
	{
		std::cout << "error: Image \"KnightUp3\" not found";
	}
	if (!playerTextures[3][0].loadFromFile("sprites/knightDown1.png"))
	{
		std::cout << "error: Image \"KnightDown1\" not found";
	}
	if (!playerTextures[3][1].loadFromFile("sprites/knightDown2.png"))
	{
		std::cout << "error: Image \"KnightDown2\" not found";
	}
	if (!playerTextures[3][2].loadFromFile("sprites/knightDown3.png"))
	{
		std::cout << "error: Image \"KnightDown3\" not found";
	}

	// enemy textures
	sf::Texture enemyTexture;
	if (!enemyTexture.loadFromFile("sprites/SpriteMagic1s.png"))
	{
		std::cout << "error: Image \"SpriteMagic1s.png\" not found";
	}

	// terrain textures
	sf::Texture wallTexture;
	if (!wallTexture.loadFromFile("sprites/Wall.png"))
	{
		std::cout << "error: Image \"Wall\" not found";
	}

	sf::Texture wallShadowTexture;
	if (!wallShadowTexture.loadFromFile("sprites/WallShadow.png"))
	{
		std::cout << "error: Image \"WallShadow\" not found";
	}

	sf::Texture floorTexture;
	if (!floorTexture.loadFromFile("sprites/Floor.png"))
	{
		std::cout << "error: Image \"Floor\" not found";
	}

	sf::Texture blankTexture;
	if (!blankTexture.loadFromFile("sprites/Blank.png"))
	{
		std::cout << "error: Image \"Blank\" not found";
	}

	//Text implementation 

	sf::Font m_font;
	sf::Text m_content;

	sf::Vector2f textPosition;
	textPosition.x = 20;
	textPosition.y = 20;
	m_font.loadFromFile("fonts/arial.ttf");
	m_content.setFont(m_font);
	m_content.setString("Example text ");
	m_content.setCharacterSize(30);
	m_content.setPosition(textPosition);

	sf::Sprite dungeonMapLayout[dungeonDisplay][dungeonDisplay];

	for (int y = 0; y < dungeonDisplay; y++)
	{
		for (int x = 0; x < dungeonDisplay; x++) {
			dungeonMapLayout[y][x].setPosition(sf::Vector2f((float)(x * spriteSize), (float)(y * spriteSize)));
		}
	}

	bool inCombat = true;

	enum characterDirection lastDirection = DOWN;
	int spriteCycle = 0;
	int idle = 0;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		getMapLayout(playerLocation.x, playerLocation.y, displayedSection);

		// Moves player leftwards
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			lastDirection = LEFT;
			if (displayedSection[displayCenter][displayCenter - 1] == tileFloor)
			{
				playerLocation.x--;
			}
		}

		// Moves player rightwards
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			lastDirection = RIGHT;

			if (displayedSection[displayCenter][displayCenter + 1] == tileFloor)
			{
				playerLocation.x++;
			}
		}

		// Moves player upwards
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			lastDirection = UP;

			if (displayedSection[displayCenter - 1][displayCenter] == tileFloor)
			{
				playerLocation.y--;
			}
		}

		// Moves player downwards
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			lastDirection = DOWN;

			if (displayedSection[displayCenter + 1][displayCenter] == tileFloor)
			{
				playerLocation.y++;
			}
		}
		// If no direction is being pressed, this will make it so that the character won't move.

		else
		{
			spriteCycle = 0;
		}
		if (++spriteCycle >= 3)
		{
			spriteCycle = 0;
		}


		window.clear();
	
		for (int y = 0; y < dungeonDisplay; y++)
		{
			for (int x = 0; x < dungeonDisplay; x++) {
				// Set texture and location on the screen
				if (inCombat == false) {
					switch (displayedSection[y][x])
					{
						/*case tileBlank:
							dungeonMapLayout[y][x].setTexture(blankTexture);
							break;*/
					case tileWall:
						dungeonMapLayout[y][x].setTexture(wallTexture);
						//std::cout << "[]";
						break;
					case tileWallShadow:
						dungeonMapLayout[y][x].setTexture(wallShadowTexture);
						//std::cout << "()";
						break;
					case tileFloor:
						dungeonMapLayout[y][x].setTexture(floorTexture);
						//std::cout << "00";
						break;

					default:
						dungeonMapLayout[y][x].setTexture(blankTexture);
						//std::cout << "@@";
						break;
					}
				}
				else {
					dungeonMapLayout[y][x].setTexture(blankTexture);
				}

				window.draw(dungeonMapLayout[y][x]);

			}

			//std::cout << "\n";
		}
		if (inCombat == false) {
			if (lastDirection == DOWN) {
				dungeonMapLayout[displayCenter][displayCenter].setTexture(playerTextures[3][spriteCycle]);
			}
			else if (lastDirection == RIGHT)
			{
				dungeonMapLayout[displayCenter][displayCenter].setTexture(playerTextures[1][spriteCycle]);
			}
			else if (lastDirection == LEFT)
			{
				dungeonMapLayout[displayCenter][displayCenter].setTexture(playerTextures[0][spriteCycle]);
			}
			else if (lastDirection == UP)
			{
				dungeonMapLayout[displayCenter][displayCenter].setTexture(playerTextures[2][spriteCycle]);
			}

		}
		else {
			dungeonMapLayout[displayCenter][displayCenter].setTexture(enemyTexture);
			window.draw(m_content);
		}
		window.draw(dungeonMapLayout[displayCenter][displayCenter]);
		window.display();
		Sleep(100);
		//		std::cout << "\n";
	}

	return 0;
}




