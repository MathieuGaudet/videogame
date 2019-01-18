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
	int highestNumber = 4;
	int lowestNumber = 1;
	int range = highestNumber - lowestNumber;
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
	m_font.loadFromFile("fonts/OCRAEXT.ttf");

	sf::Text gameOver;
	sf::Vector2f gameOverPosition;
	gameOverPosition.x = 10;
	gameOverPosition.y = 200;
	gameOver.setFont(m_font);
	gameOver.setString("GAME OVER");
	gameOver.setCharacterSize(85);
	gameOver.setPosition(gameOverPosition);

	sf::Text attackText;
	sf::Vector2f attackTextPosition;
	attackTextPosition.x = 35;
	attackTextPosition.y = 350;
	attackText.setFont(m_font);
	attackText.setString("Attack");
	attackText.setCharacterSize(24);
	attackText.setPosition(attackTextPosition);

	sf::Text guardText;
	sf::Vector2f guardTextPosition;
	guardTextPosition.x = 35;
	guardTextPosition.y = 380;
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
	runText.setFont(m_font);
	runText.setString("Run");
	runText.setCharacterSize(24);
	runText.setPosition(runTextPosition);

	sf::Text introText[2];
	sf::Vector2f introTextPosition[2];
	introTextPosition[0].x = 35;
	introTextPosition[0].y = 100;
	introText[0].setFont(m_font);
	introText[0].setString("To move, use wasd or the arrow keys");
	introText[0].setCharacterSize(20);
	introText[0].setPosition(introTextPosition[0]);

	introTextPosition[1].x = 12;
	introTextPosition[1].y = 200;
	introText[1].setFont(m_font);
	introText[1].setString("To select an option in combat, use \"J\"");
	introText[1].setCharacterSize(20);
	introText[1].setPosition(introTextPosition[1]);

	sf::Text combatText1[3];
	sf::Vector2f combatText1Position[3];
	combatText1Position[0].x = 125;
	combatText1Position[0].y = 350;
	combatText1[0].setFont(m_font);
	combatText1[0].setString("");
	combatText1[0].setCharacterSize(15);
	combatText1[0].setPosition(combatText1Position[0]);

	combatText1Position[1].x = 125;
	combatText1Position[1].y = 380;
	combatText1[1].setFont(m_font);
	combatText1[1].setString("");
	combatText1[1].setCharacterSize(15);
	combatText1[1].setPosition(combatText1Position[1]);
	
	combatText1Position[2].x = 125;
	combatText1Position[2].y = 400;
	combatText1[2].setFont(m_font);
	combatText1[2].setString("");
	combatText1[2].setCharacterSize(15);
	combatText1[2].setPosition(combatText1Position[2]);

	std::string combatTextString[2];

	// run option math
	int chanceOfSuccess = 75;
	bool runSuccess = false;
	int runProbabilityRange = 100;
	int runRandomNumberValue;

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
	int textCycle = 0;
	bool firstTime = true;
// Start of Event loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (firstTime == false) {
			if (characterHPLeft > 0) {
				// Resets Values
				encounterChance = 10;
				runSuccess = false;
				if (inCombat == false) {
					monsterHPLeft = monsterStats.hitpoints;
					combatText1[0].setString("");
					combatText1[1].setString("");
					combatText1[2].setString("");
					chanceOfSuccess = 75;
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
				// lets the user pick an option for combat
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
					switch (cursorCycle)
					{
					case 0:
						damage = (characterStats.attack * (characterStats.attack) * 10) / (characterStats.attack + monsterStats.defense);
						damage = addRandomness(damage);
						combatTextString[0] = "You deal ";
						combatTextString[1] = " damage to the monster";
						combatTextString[0] += std::to_string(damage);
						combatTextString[0] += combatTextString[1];
						combatText1[textCycle].setString(combatTextString[0]);
						textCycle++;
						if (textCycle >= 3)
						{
							textCycle = 0;
						}
						monsterHPLeft -= damage;
						if (monsterHPLeft <= 0) {
							combatText1[textCycle].setString("You have slain the fiend");
							textCycle++;
							if (textCycle >= 3)
							{
								textCycle = 0;
							}
						}
						else {

							damage = (monsterStats.attack* (monsterStats.attack) * 10) / (monsterStats.attack + characterStats.defense);
							damage = addRandomness(damage);
							characterHPLeft -= damage;
							combatTextString[0] = "The monster deals ";
							combatTextString[1] = " damage to you";
							combatTextString[0] += std::to_string(damage);
							combatTextString[0] += combatTextString[1];
							combatText1[textCycle].setString(combatTextString[0]);
							textCycle++;
							if (textCycle >= 3)
							{
								textCycle = 0;
							}

							combatTextString[0] = "You have ";
							combatTextString[1] = " HP left";
							combatTextString[0] += std::to_string(characterHPLeft);
							combatTextString[0] += combatTextString[1];
							combatText1[textCycle].setString(combatTextString[0]);
							textCycle++;
							if (textCycle >= 3)
							{
								textCycle = 0;
							}
						}
						break;
					case 1:

						damage = ((monsterStats.attack* (monsterStats.attack) * 10) / (monsterStats.attack + characterStats.defense)) / 2;
						damage = addRandomness(damage);
						characterHPLeft -= damage;
						combatTextString[0] = "The monster deals ";
						combatTextString[1] = " damage to you";
						combatTextString[0] += std::to_string(damage);
						combatTextString[0] += combatTextString[1];
						combatText1[textCycle].setString(combatTextString[0]);
						textCycle++;
						if (textCycle >= 3)
						{
							textCycle = 0;
						}

						combatTextString[0] = "You have ";
						combatTextString[1] = " HP left";
						combatTextString[0] += std::to_string(characterHPLeft);
						combatTextString[0] += combatTextString[1];
						combatText1[textCycle].setString(combatTextString[0]);
						textCycle++;
						if (textCycle >= 3)
						{
							textCycle = 0;
						}
						break;
					case 2:
						runRandomNumberValue = (rand() % runProbabilityRange) + 0;
						if (runRandomNumberValue <= chanceOfSuccess) {
							combatText1[spriteCycle].setString("You have escaped successfully!");
							runSuccess = true;
						}
						else {
							combatText1[spriteCycle].setString("You could not escape!");

							damage = (monsterStats.attack* (monsterStats.attack) * 10) / (monsterStats.attack + characterStats.defense);
							damage = addRandomness(damage);
							characterHPLeft -= damage;
							combatTextString[0] = "The monster deals ";
							combatTextString[1] = " damage to you";
							combatTextString[0] += std::to_string(damage);
							combatTextString[0] += combatTextString[1];
							combatText1[textCycle].setString(combatTextString[0]);
							textCycle++;
							if (textCycle >= 3)
							{
								textCycle = 0;
							}

							combatTextString[0] = "You have ";
							combatTextString[1] = " HP left";
							combatTextString[0] += std::to_string(characterHPLeft);
							combatTextString[0] += combatTextString[1];
							combatText1[textCycle].setString(combatTextString[0]);
							textCycle++;
							if (textCycle >= 3)
							{
								textCycle = 0;
							}
							chanceOfSuccess += 10;
							break;
					default:
						std::cout << "Unexpected error switch statement failed in a way that should not be possible";
						break;
						}
					}
				}
				if (inCombat == true) {
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
				else if (inCombat == true) {
					dungeonMapLayout[displayCenter][displayCenter].setTexture(enemyTexture);
					dungeonMapLayout[cursorLocation[cursorCycle]][0].setTexture(cursorTexture);
					window.draw(attackText);
					window.draw(guardText);
					window.draw(runText);
					window.draw(combatText1[0]);
					window.draw(combatText1[1]);
					window.draw(combatText1[2]);
				}
				window.draw(dungeonMapLayout[displayCenter][displayCenter]);
				window.draw(dungeonMapLayout[cursorLocation[cursorCycle]][0]);

			}
			else {
			window.clear();
			window.draw(gameOver);
}

		}
		else {
		window.draw(introText[0]);
		window.draw(introText[1]);
}

			window.display();
			if (monsterHPLeft <= 0 || runSuccess == true) {
				inCombat = false;
				Sleep(500);
			}
			if (firstTime == true) {
				firstTime = false;
				Sleep(5000);
			}
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


