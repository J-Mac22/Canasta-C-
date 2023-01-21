#pragma once

#include "Player.h"

class Player;
 
class Computer : public Player {

public:

	Computer();
	bool play(Deck& useDecks, std::vector<std::vector<Card>> opponentMelds) override;
	bool draw(Deck &useDecks) override;
	void discard(Deck& useDecks, std::vector<std::vector<Card>> opponentMelds) override;
	void meld(std::vector<std::vector<Card>> opponentMelds) override;
	void playerStrategy(Deck& useDecks, std::vector<std::vector<Card>> opponentMelds) override;
	 
	virtual std::string getTypeOfPlayer() override;
	void outputTypeOfPlayer() override;
	bool decideGoOut() override;
	 
private:

	int meldBreakOff;

};
