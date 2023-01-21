#pragma once

#include <iostream>

#include <vector>
#include <string>

#include "Card.h"
#include "Deck.h"

//For extracting the cards one by one
typedef std::vector<Card>::const_iterator itrCard;

class Hand {

public:

	Hand();
	Hand(std::vector<Card> handDebug);

	bool makeMeld(Card one, Card two, Card three);
	bool makeMeld(Card redThree);

	bool canMeld(Card headDiscard);
	bool canMeldWithMelds(Card headDiscard);
	 
	bool wildCardTransfer(Card transfer, int wildRoot, int meldNum);
	bool cardLayOff(Card add, int meldNum);
	bool handRemoval(Card cardDiscard);
	bool isACanasta(int meldNum);
	bool notADuplicate(char rank);
	bool emptyHand();
	bool hasACanasta();
	int  createMeldPoints(int meldNum);
	void destroyRedThrees();

	void outputHand();
	void outputMelds();
	void outputEveryWild(int meld);

	void addToHand(Card cardAdd);
	void addToHand(std::vector<Card> cardAdd);
	 
	int  getHandSize();
	std::vector<Card> getHandContainer() const;
	std::vector<std::vector<Card>> getMeld();
	Card getMeldCard(int meldPosition, int cardPosition);
	int  getMeldSize();
	std::vector<Card> getWildCards(int meldPosition);
	std::vector<Card> getWildCardsWithoutTransferring(int meldPosition);
	std::vector<Card> getWildCardsFromHand();
	Card getCardFromHand(int position);
	int getTotalScore();
	int getMeldScore(int meldPosition) const;

	void setHand(std::vector<Card> &handContainer);
	void setMeld(std::vector<std::vector<Card>> &meldContainer);
	 
	void deleteTransfer();
	void deleteData();
	
	int nonSpecificMeldsSize() const;
	bool existingMeld(Card lookForCard);
	void sort();

private:
	std::vector<Card> handContainer;
	std::vector<std::vector<Card>> meldContainer;

};
