// CombatTesting.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

int main()
{
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
	characterStats.hitpoints = 90 +(characterLevel*characterLevel) + equipmentTotalStats.hitpoints;

	int characterHPLeft = characterStats.hitpoints;

	// monster's stats
	struct statBlock monsterStats = {2, 3, 90};
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
	
	char actionChoice;
	int damage = 0;
	std::cout << "An enemy approaches! ";
	while (1) {
		std::cout << "Would you like to attack (a), guard (b), or run (c)?\n";
		std::cin >> actionChoice;
		switch (actionChoice)
		{
		case 'a':
			
			randomNumberValue = (rand() % range) + lowestNumber;
			std::cout << "\n" << randomNumberValue << "\n\n";
			damage = (characterStats.attack* (characterStats.attack+randomNumberValue)*10) / (characterStats.attack + monsterStats.defense);
			std::cout << "\nYou deal " << damage << " damage to the monster\n";
			monsterHPLeft -= damage;
			if (monsterHPLeft <= 0) {
				std::cout << "You have slain the fiend!\n";
			}
			else {
				randomNumberValue = (rand() % range) + lowestNumber;
				damage = (monsterStats.attack* (monsterStats.attack + randomNumberValue) * 10) / (monsterStats.attack + characterStats.defense);
				characterHPLeft -= damage;
				std::cout << "\nThe monster deals " << damage << " damage to you.\nYou have " << characterHPLeft << " HP left\n";
			}
			break;
		case 'b':
			randomNumberValue = (rand() % range) + lowestNumber;
			damage = ((monsterStats.attack* (monsterStats.attack + randomNumberValue) * 10) / (monsterStats.attack + characterStats.defense))/2;
			characterHPLeft -= damage;
			std::cout << "\nThe monster deals " << damage << " damage to you.\nYou have " << characterHPLeft << " HP left\n";
			
			break;
		case 'c':
			randomNumberValue = (rand() % runProbabilityRange) + 0;
			if (randomNumberValue <= chanceOfSuccess) {
				std::cout << "You have escaped successfully! \n";
				runSuccess = true;
			}
			else {
				std::cout << "You could not escape!\n";
				randomNumberValue = (rand() % range) + lowestNumber;
				damage = (monsterStats.attack* (monsterStats.attack + randomNumberValue) * 10) / (monsterStats.attack + characterStats.defense);
				characterHPLeft -= damage;
				std::cout << "\nThe monster deals " << damage << " damage to you.\nYou have " << characterHPLeft << " HP left\n";
				chanceOfSuccess += 10;
			}
			break;
		default:
			break;
		}
		if (characterHPLeft <= 0) {
			std::cout << "You have died.\nGAME OVER\n";
		}
		if (monsterHPLeft <= 0 || characterHPLeft <= 0 || runSuccess == true) {
			std::cout << "\n\n\n";
			break;
		}
	}
}
