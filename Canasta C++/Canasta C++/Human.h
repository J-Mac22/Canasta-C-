#pragma once

#include "Player.h"

#include <sstream>

class Player;
class Human;
 
class Human : public Player {

public:

	bool play(Deck& useDecks, std::vector<std::vector<Card>> opponentMeld) override;
	bool draw(Deck &useDecks) override;
	void discard(Deck& useDecks, std::vector<std::vector<Card>> opponentMelds) override;
	void meld(std::vector<std::vector<Card>> opponentMelds) override;
	void playerStrategy(Deck& useDecks, std::vector<std::vector<Card>> opponentMelds) override;
	 
	virtual std::string getTypeOfPlayer() override;
	void outputTypeOfPlayer() override;
	bool decideGoOut() override;
	void outputOpponentMeld(std::vector<std::vector<Card>> opponentMeld);
	std::vector<Card> confirmCommaInput();

	void strategyDraw(Deck& useDecks);
	void strategyMeld(Deck& useDecks, std::vector<std::vector<Card>> opponentMelds);
	void strategyDiscard(Deck& useDecks, std::vector<std::vector<Card>> opponentMelds);

	 
};