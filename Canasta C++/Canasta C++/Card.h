#pragma once

#include <vector>
#include <string>

class Card {

public:

	Card();
	~Card();
	Card(int suit, int face);
	Card(char face, char suit, std::string strRep, int pointVal);
	Card(std::string strRep);
	Card(const Card& anotherCard);
	Card operator=(const Card& anotherCard);
	Card(Card&& anotherCard) noexcept;
	Card operator=(Card&& anotherCard) noexcept;
	 
	char getSuit() const;
	char getFace() const;
	std::string getCardStr() const;
	int getPointVal() const;
	bool getTransfer() const;
	int getNumVal() const;

	void setTransfer(bool hasBeenTransferred);

	bool isWild() const;
	bool isSpecial() const;
	bool isNatural() const;
	bool isRedThrees() const;
	bool isJoker() const;

	void translateSymbols(int face, int val);
	void createPointVal(char face, char val);

private:

	char suit;
	char face;
	std::string strRep;
	int pointVal;
	bool hasBeenTransferred;

};

//For composition of binary numbers 
bool operator==(const Card c1, const Card c2);
bool operator<(const Card c1, const Card c2);
bool operator>(const Card c1, const Card c2);