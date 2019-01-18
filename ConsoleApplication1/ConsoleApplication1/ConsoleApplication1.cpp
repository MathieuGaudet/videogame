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

int addRandomness(int rawNumber);

int main()
{


	struct location playerLocation;
	int displayedSection[dungeonDisplay][dungeonDisplay];

	playerLocation.x = startLocationX;
	playerLocation.y = startLocationY;


	sf::RenderWindow window(sf::VideoMode(spriteSize * dungeonDisplay, spriteSize * dungeonDisplay), "Mathieu's Game");


	struct statBlock
	{
		int attack;
		int defense;
		int hitpoints;
	};
	// equipment
	const struct statBlock empty = { 0, 0, 0 };
	const struct statBlock clothShirt = { 0, 2, 0 };
	const struct statBlock clothPants = { 0, 2, 0 };
	const struct statBlock simpleHat = { 0, 1, 0 };
	const struct statBlock simpleShoes = { 0, 1, 0 };
	const struct statBlock wornDagger = { 2, 0, 0 };

	// equipment slots
	struct statBlock chest = clothShirt;
	struct statBlock legs = clothPants;
	struct statBlock head = simpleHat;
	struct statBlock feet = simpleShoes;
	struct statBlock mainHand = wornDagger;
	struct statBlock offHand = empty;

	int characterLevel = 1;

	// equipment stats added together
	struct statBlock equipmentTotalStats;
	equipmentTotalStats.attack = chest.attack + legs.attack + head.attack + feet.attack + mainHand.attack + offHand.attack;
	equipmentTotalStats.defense = chest.defense + legs.defense + head.defense + feet.defense + mainHand.defense + offHand.defense;
	equipmentTotalStats.hitpoints = chest.hitpoints + legs.hitpoints + head.hitpoints + feet.hitpoints + mainHand.hitpoints + offHand.hitpoints;

	// the character's stats
	struct statBlock characterStats;
	characterStats.attack = (characterLevel*characterLevel) + equipmentTotalStats.attack;
	characterStats.defense = (characterLevel*characterLevel) + equipmentTotalStats.defense;
	characterStats.hitpoints = 90 + (characterLevel*characterLevel) + equipmentTotalStats.hitpoints;

	int characterHPLeft = characterStats.hitpoints;

	// monster's stats
	struct statBlock monsterStats = { 2, 3, 45 };
	int monsterHPLeft = monsterStats.hitpoints;

	// random number generating stuff
	srand(time(NULL));
	int randomNumberValue;
	int highestNumber = 4;
	int lowestNumber = 1;
	int range = highestNumber - lowestNumber;

	// run option math
	int chanceOfSuccess = 75;
	bool runSuccess = false;
	int runProbabilityRange = 100;
	int damage = 0;


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
	sf::Texture cursorTexture;
	if (!cursorTexture.loadFromFile("sprites/cursor.png"))
	{
		std::cout << "error: Image \"cursor\" not found";
	}

	// random number generating stuff for the enccounters
	srand(time(NULL));
	int encounterChance = 10;
	int encounterChanceHigh = 36;
	int encounterChanceLow = 1;
	int encouterRange = encounterChanceHigh - encounterChanceLow;

	// Text implementation 
	sf::Font m_font;
	sf::Text attackText;

	sf::Vector2f attackTextPosition;
	attackTextPosition.x = 35;
	attackTextPosition.y = 350;
	m_font.loadFromFile("fonts/OCRAEXT.ttf");
	attackText.setFont(m_font);
	attackText.setString("Attack");
	attackText.setCharacterSize(24);
	attackText.setPosition(attackTextPosition);

	sf::Text guardText;
	sf::Vector2f guardTextPosition;
	guardTextPosition.x = 35;
	guardTextPosition.y = 380;
	m_font.loadFromFile("fonts/OCRAEXT.ttf");
	guardText.setFont(m_font);
	guardText.setString("Guard");
	guardText.setCharacterSize(24);
	guardText.setPosition(guardTextPosition);

	sf::Text runText;
	sf::Vector2f runTextPosition;
/*
	std::string testThis = "amazing";
	int maybeWork = 4;
	std::string forTesting = "work? ";
	forTesting += std::to_string(maybeWork);
	forTesting += testThis;
	*/
	runTextPosition.x = 35;
	runTextPosition.y = 410;
	m_font.loadFromFile("fonts/OCRAEXT.ttf");
	runText.setFont(m_font);
	runText.setString("Run");
	runText.setCharacterSize(24);
	runText.setPosition(runTextPosition);

	sf::Sprite dungeonMapLayout[dungeonDisplay][dungeonDisplay];

	for (int y = 0; y < dungeonDisplay; y++)
	{
		for (int x = 0; x < dungeonDisplay; x++) {
			dungeonMapLayout[y][x].setPosition(sf::Vector2f((float)(x * spriteSize), (float)(y * spriteSize)));
		}
	}

	bool inCombat = false;
	int cursorLocation[3] = { 11, 12, 13 };

	enum characterDirection lastDirection = DOWN;
	int spriteCycle = 0;
	int cursorCycle = 0;
	int idle = 0;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (inCombat == false) {
			getMapLayout(playerLocation.x, playerLocation.y, displayedSection);

			// Moves player leftwards
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				lastDirection = LEFT;
				if (displayedSection[displayCenter][displayCenter - 1] == tileFloor)
				{
					playerLocation.x--;
				}
				encounterChance = (rand() % encouterRange) + encounterChanceLow;
			}

			// Moves player rightwards
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				lastDirection = RIGHT;

				if (displayedSection[displayCenter][displayCenter + 1] == tileFloor)
				{
					playerLocation.x++;
				}
				encounterChance = (rand() % encouterRange) + encounterChanceLow;
			}

			// Moves player upwards
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				lastDirection = UP;

				if (displayedSection[displayCenter - 1][displayCenter] == tileFloor)
				{
					playerLocation.y--;
				}
				encounterChance = (rand() % encouterRange) + encounterChanceLow;
			}

			// Moves player downwards
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				lastDirection = DOWN;

				if (displayedSection[displayCenter + 1][displayCenter] == tileFloor)
				{
					playerLocation.y++;
				}
				encounterChance = (rand() % encouterRange) + encounterChanceLow;
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

			if (encounterChance == 1)
			{
				inCombat = true;
			}
		}
		else {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				++cursorCycle;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				--cursorCycle;
			}
			if (cursorCycle >= 3) {
				cursorCycle = 0;
			}
			if (cursorCycle < 0) {
				cursorCycle = 2;
			}
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
			dungeonMapLayout[cursorLocation[cursorCycle]][0].setTexture(cursorTexture);
			window.draw(attackText);
			window.draw(guardText);
			window.draw(runText);
		}
		window.draw(dungeonMapLayout[displayCenter][displayCenter]);
		window.draw(dungeonMapLayout[cursorLocation[cursorCycle]][0]);
		window.display();
		Sleep(100);
		//		std::cout << "\n";
	}

	return 0;
}




int addRandomness(int rawNumber) {
	const int percentRange = 10;
	double temp = (double)rawNumber / 100.0;
	int range = (int)(temp * percentRange);
	if (range < 3) {
		range = 3;
	}
	int lowestNumber = (range / 2 * -1) + rawNumber;
	int randomNumberValue = (rand() % range) + lowestNumber;

	return randomNumberValue;
}


