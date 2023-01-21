#include "Deck.h"

 
/* *********************************************************************
Function Name: Deck()
Purpose:  Default constructor for the Deck class.
Parameters: None
Return Value: None
Algorithm:
			 1. Call the makeStock function to create a new stock of cards.
			 2. Call the stockShuffle function to shuffle the stock of cards.
			 3. Declare a variable discardOne of type Card.
			 4. Enter a do-while loop. Inside the loop:
				1. Call the stockDraw function to draw a card from the stock and assign it to discardOne.
				2. Call the discardPushFront function to add the drawn card to the front of the discard pile.
				3. Check if discardOne is a red three or a wild card. If it is, continue the loop. If it is not, exit the loop.
			 5. End the do-while loop.

Assistance Received: None
********************************************************************* */
Deck::Deck() {

	makeStock();
	stockShuffle();
	Card discardOne;

	//Drawing another card only if the card is a red three
	do {

		discardOne = stockDraw();
		discardPushFront(discardOne);

	}

	while (discardOne.isRedThrees() || discardOne.isWild());

}

/* *********************************************************************
Function Name: makeStock()
Purpose: Creates the stock pile.
Parameters: None
Return Value: void
Algorithm:
			1. Initialize a loop that iterates i from 0 to 1.
			2. Inside the first loop, initialize a loop that iterates s from 0 to 3.
			3. Inside the second loop, initialize a loop that iterates f from 2 to 14.
			4. Inside the third loop, create a new Card object with suit s, face value f, and default string representation and point value.
			5. Add the newly created card to the end of the stock pile.
			6. End the loops.
			7. Add four Jokers to the end of the stock pile, each with default string representation "J1", "J2", "J3", and "J4" and point value 50.

Assistance Received: None
********************************************************************* */
void Deck::makeStock() {

	for (int i = 0; i < 2; i++)

		for (int s = 0; s < 4; s++) {

			for (int f = 2; f < 15; f++) {

				stockPile.push_back(Card(s, f));

			}

		}

	//Adding Jokers to the deck
	stockPile.push_back(Card('J', '1', "J1", 50));
	stockPile.push_back(Card('J', '2', "J2", 50));
	stockPile.push_back(Card('J', '3', "J3", 50));
	stockPile.push_back(Card('J', '1', "J4", 50));

}

/* *********************************************************************
Function Name: stockShuffle()
Purpose: Shuffles the cards in the stock pile.
Parameters: None
Return Value: void
Algorithm:
			1.Use the current time since epoch to seed shuffling.
			2.Use the shuffle function from the algorithm library to shuffle the elements in the stock pile vector 
			  using the shuffling random engine as the source of randomness.

Assistance Received: None
********************************************************************* */
void Deck::stockShuffle() {

	auto shuffling = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(stockPile.begin(), stockPile.end(), std::default_random_engine(shuffling));

}

/* *********************************************************************
Function Name: discard
Purpose: Discards a card in the deck.
Parameters:
			cardDiscard -> Card object that represents the card to be discarded

Return Value: void
Algorithm:
			1. If the discarded card is a black three, freeze the discard pile.
			2. Else, set the frozen discard pile to false.
			3. Add the discarded card to the top of the discard pile by calling the discardPushFront function.
 
Assistance Received: None
********************************************************************* */
void Deck::discard(Card cardDiscard) {

	if (cardDiscard.getCardStr() == "3S" || cardDiscard.getCardStr() == "3C") {

		frozenDiscard = true;

	}

	else if (frozenDiscard && cardDiscard.isNatural()) {

		frozenDiscard = false;

	}

	discardPushFront(cardDiscard);

}

/* *********************************************************************
Function Name: stockDraw()
Purpose: Draws a card from the stock pile.
Parameters: None
Return Value: drawnCard -> Card object that represents the card that has been drawn from the deck
Algorithm:
			1. Assign the value of the first element in the stockPile vector to drawnCard.
			2. Remove the first element from the stockPile vector.

Assistance Received: None
********************************************************************* */
Card Deck::stockDraw() {

	Card drawnCard;
	drawnCard = *(stockPile.begin());
	stockPile.erase(stockPile.begin());
	return drawnCard;
}

/* *********************************************************************
Function Name: discardDraw()
Purpose: Draws a card from the discard pile.
Parameters: None
Return Value: discardCopy -> vector of type Card that contains a copy of the discard pile
Algorithm:
			1. Create a copy of the discardPile vector and store it in a new variable.
			2. Clear the discardPile vector.
			3. Create a new Card object 

Assistance Received: None
********************************************************************* */
std::vector<Card> Deck::discardDraw() {

	std::vector<Card> discardCopy = discardPile;
	discardPile.clear();
	Card discardOne;

	return discardCopy;

}

/* *********************************************************************
Function Name: emptyStock()
Purpose: Reads if there are no more cards in the stock pile.
Parameters: None
Return Value: The size of the stockPile vector and have it be set to zero.
Assistance Received: None
********************************************************************* */
bool Deck::emptyStock() {

	return stockPile.size() == 0;

}

/* *********************************************************************
Function Name: emptyDiscard()
Purpose: Reads if there are no more cards in the discard pile.
Parameters: None
Return Value: The size of the discardPile vector and have it be set to zero.
Assistance Received: None
********************************************************************* */
bool Deck::emptyDiscard() {

	return discardPile.size() == 0;

}

/* *********************************************************************
Function Name: emptyPiles()
Purpose: Reads if there are no more cards in either pile.
Parameters: None
Return Value: The empty piles represented by their respective "empty" functions.
Assistance Received: None
********************************************************************* */
bool Deck::emptyPiles() {

	return (emptyStock() && emptyDiscard());

}

/* *********************************************************************
Function Name: getDiscardTop()
Purpose: Selector that gets the first card in the discard pile.
Parameters: None
Return Value: Either the top card on the discard pile or an instance of Card class with default values.
Assistance Received: None
********************************************************************* */
Card Deck::getDiscardTop() {

	if (discardPile.size() != 0)
		return *discardPile.begin();

	else
		return Card();

}

/* *********************************************************************
Function Name: getFrozenDiscard()
Purpose: Selector that checks if the discard pile is frozen or not.
Parameters: None
Return Value:  bool that indicates whether the top card of the discard pile 
			   has caused the discard pile to become frozen
 
Assistance Received: None
********************************************************************* */
bool Deck::getFrozenDiscard() {

	if (discardPile.size() != 0) {

		return frozenDiscard || getDiscardTop().isSpecial();

	}

	else

		return frozenDiscard;

}

/* *********************************************************************
Function Name: getDiscardSize()
Purpose: Selector for the discardPile variable.
Parameters: None
Return Value: discardPile -> vector of Cards that represents the discard pile
Assistance Received: None
********************************************************************* */
int Deck::getDiscardSize() const {

	return discardPile.size();

}

/* *********************************************************************
Function Name: setStock
Purpose: Mutator for the stockPile variable.
Parameters:
			stockPile -> vector of Cards that represents the stock pile

Return Value: void
Assistance Received: None
********************************************************************* */
void Deck::setStock(std::vector<Card> stockPile) {

	this->stockPile = stockPile;

}

/* *********************************************************************
Function Name: setDiscard
Purpose: Mutator for the discardPile variable.
Parameters:
			discardPile -> vector of Cards that represents the discard pile

Return Value: void
Assistance Received: None
********************************************************************* */
void Deck::setDiscard(std::vector<Card> discardPile) {

	this->discardPile = discardPile;

}

/* *********************************************************************
Function Name: setFrozenDiscard
Purpose: Mutator for the isFreezing variable.
Parameters:
			isFreezing -> bool that represents if the discard pile has froze or not

Return Value: void
Assistance Received: None
********************************************************************* */
void Deck::setFrozenDiscard(bool isFreezing) {

	frozenDiscard = isFreezing;

}

/* *********************************************************************
Function Name: outputStock()
Purpose: Outputs the stock pile.
Parameters: None
Return Value: void
Algorithm:
				1. Create a loop that iterates over every Card object in the stockPile vector.
				2. Within the loop, output the string representation of the current Card object by calling its getCardStr() function.
				3. After the loop completes, output a newline character to the console.

Assistance Received: None
********************************************************************* */
void Deck::outputStock() {

	for (Card card : stockPile)
		std::cout << card.getCardStr() << " ";
	std::cout << std::endl;

}

/* *********************************************************************
Function Name: outputStockTop()
Purpose: Outputs the top of the stock pile.
Parameters: None
Return Value: void
Algorithm:
			1. Check if the size of the stockPile vector is greater than 0.
			2. If the size of the stockPile vector is greater than 0, 
			   output the string representation of the top card in the stockPile vector (which is the first element of the vector).
            3. If the size of the stockPile vector is not greater than 0, do nothing.

Assistance Received: None
********************************************************************* */
void Deck::outputStockTop() {

	if (stockPile.size() > 0)
		std::cout << stockPile.at(0).getCardStr() << std::endl;

}

/* *********************************************************************
Function Name: outputDiscard()
Purpose: Outputs the discard pile.
Parameters: None
Return Value: void
Algorithm:
			1. Iterate through each Card object in discardPile.
			2. For each Card object, print its string representation to the console.
			3. After all Card objects have been printed, print a newline character to the console.

Assistance Received: None
********************************************************************* */
void Deck::outputDiscard() {

	for (Card card : discardPile)
		std::cout << card.getCardStr() << " ";
	std::cout << std::endl;

}

/* *********************************************************************
Function Name: outputDiscardTop()
Purpose: Outputs the top card in the discard pile.
Parameters: None
Return Value: void
Algorithm:
			1. Check if the discard pile is empty by calling the function emptyDiscard(). If it is empty, print a blank line.
			2. Print the string representation of the top card in the discard pile. 
			   This can be obtained by calling the function getCardStr() on the first element of the discardPile vector.

Assistance Received: None
********************************************************************* */
void Deck::outputDiscardTop() {

	if (emptyDiscard() == false)
		std::cout << discardPile.at(0).getCardStr() << std::endl;

	else {

		std::cout << std::endl;

	}

}

/* *********************************************************************
Function Name: discardPushFront
Purpose: Pushes the first element of the discard pile to the front.
Parameters:
			cardPush -> Card object that represents the card being pushed to the front of the discard pile

Return Value: void
Assistance Received: None
********************************************************************* */
void Deck::discardPushFront(Card cardPush) {

	discardPile.insert(discardPile.begin(), cardPush);

}

/* *********************************************************************
Function Name: deleteDiscard()
Purpose: Clears out the cards in the discard pile.
Parameters: None
Return Value: void
Assistance Received: None
********************************************************************* */
void Deck::deleteDiscard() {

	discardPile.clear();

}