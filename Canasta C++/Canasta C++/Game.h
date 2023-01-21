#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <algorithm>
#include <filesystem>

class Card;
class Deck;
class Hand;
class Player;
class Human;
class Computer;
class Round;

#include "Player.h"
#include "Hand.h"
#include "Human.h"
#include "Computer.h"
#include "Round.h"

class Game {

public:

	Game();
	~Game();
	Game(const Game& anotherGame);

	void mainMenu();
	void pickTypeOfPlayer();

	void mainGame();
	void mainGame(Round &roundLoaded);

	void chooseVictor();

private:

	std::vector<Player*> players;
	int round;

};

int checkUserInput(int lower, int upper);
int checkUserInput(int lower, int upper, bool uniqueOption);