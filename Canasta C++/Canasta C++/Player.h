#pragma once

#include "Hand.h"
#include "Deck.h"

class Player {

public:

	Player();

	int getScore();
	Hand getHandOfPlayer();

	bool makeMeld(Card one, Card two, Card three);
	bool makeMeld(std::vector<Card> possibleMeld);
	void makeUniqueMeld(Card cardAdd);

	void addToHand(Card cardAdd);
	void addToHand(std::vector<Card> cardsAdd);
	void scoreAdd(int addingScore);

	bool hasACanasta();
	bool emptyHand();
	void destroyRedThrees();

	bool cardLayoff(Card add, int meldNum);
	bool cardTransfer(Card wildCard, int wildRoot, int meldNum);
	bool handRemoval(Card cardDiscard);
	void handSort();
	bool canGoOut();
	void outputHandTemp();

	int getMeldScore(int meldPosition);
	std::vector<Card> getVectorWildCards(std::vector<Card> cardVector);

	void setHand(std::vector<Card> handContainer);
	void setMeld(std::vector<std::vector<Card>> meldContainer);
	void setPlayerScore(int score);

	bool existingMeld(Card lookForCard);
	int  getMeldPosition(std::vector<Card> meldVector);
	void meldSort(std::vector<std::vector<Card>> &sortingMelds);

	void outputVector(std::vector<Card> vectorToOutput);
	void outputMeld(int meldPosition);

	void deleteHand();
	void deleteTransfer();
	void deleteHandAndMeld();


	virtual bool play(Deck& useDecks, std::vector<std::vector<Card>> opponentMelds) = 0;
	virtual bool draw(Deck &useDecks) = 0;
	virtual void discard(Deck& useDecks, std::vector<std::vector<Card>> opponentMelds) = 0;
	virtual void meld(std::vector<std::vector<Card>> opponentMelds) = 0;
	virtual void playerStrategy(Deck& useDecks, std::vector<std::vector<Card>> opponentMelds) = 0;

	int getCriticalCards(std::vector<std::vector<Card>> opponentMelds);
	bool isACriticalCard(Card possibleCriticalCard, std::vector<std::vector<Card>> opponentMelds);

	virtual std::string getTypeOfPlayer() = 0;
	virtual void outputTypeOfPlayer() = 0;

	bool getGoOutChoice() const;
	void setGoOutChoice(bool goOutChoice);
	virtual bool decideGoOut() = 0;
	bool goOut();


private:

	Hand handOfPlayer;
	int score;
	bool hasGoneOut;

};

int checkUserInput(int lower, int upper);
int checkUserInput(int lower, int upper, bool uniqueOption);
