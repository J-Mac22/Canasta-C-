#pragma once

#include <iostream>

#include <string>
#include <vector>
#include <random>
#include <chrono>

#include "Card.h"

class Deck {

public:

	Deck();

	void makeStock();
	void stockShuffle();
	void discard(Card discardCard);

	Card stockDraw();
	std::vector<Card> discardDraw();

	bool emptyStock();
	bool emptyDiscard();
	bool emptyPiles();

	Card getDiscardTop();
	bool getFrozenDiscard();
	int  getDiscardSize() const;

	void setStock(std::vector<Card> stockPile);
	void setDiscard(std::vector<Card> discardPile);
	void setFrozenDiscard(bool isFreezing);

	void outputStock();
	void outputStockTop();
	void outputDiscard();
	void outputDiscardTop();

	void discardPushFront(Card cardPush);
	void deleteDiscard();

private:

	std::vector<Card> stockPile;
	std::vector<Card> discardPile;
	bool frozenDiscard = false;

};
