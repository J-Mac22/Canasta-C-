#pragma once

class Card;
class Deck;
class Player;
class Human;
class Computer;
class Hand;

#include "Game.h"

class Round {

public:

	Round();
	~Round();
	Round(Human p1, Human p2);
	Round(Human p1, Computer p2);
	Round(std::vector<Player*> players, int roundNum);
	Round(const Round& anotherRound);

	int coinFlip();
	bool mainRound(bool hasFileLoad);
	void initialDraw();
	int preTurnMenu();
	void scoreTally();

	int getNextPlayer() const;
	std::vector<Player*> getPlayers();

	void setNextPlayer(int nextPlayer);
	void setStock(std::vector<Card> stockPile);
	void setDiscard(std::vector<Card> discardPile);
	void setRoundNum(int roundNum);

	bool loadGame();
	bool loadRoundNum(std::string roundStr);
	bool loadPlayer(std::string playerStr);
	bool loadPlayerScore(int player, std::string roundStr);
	bool loadStock(std::string stockStr);
	bool loadDiscard(std::string discardStr);
	bool loadNextPlayer(std::string nextPlayerStr);
	bool loadHand(int player, std::string handStr);
	bool loadMeld(int player, std::string preMeldStr);

	void playerHandSort();
	void printRoundInfo();
	bool strToCard(std::string cardStr);
	void saveRound();

private:

	int roundNum;
	int nextPlayer;
	Deck stockAndDiscard;
	std::vector<Player*> players;

};
