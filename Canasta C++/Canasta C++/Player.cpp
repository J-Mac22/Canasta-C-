#include "Player.h"

/* *********************************************************************
Function Name: Player()
Purpose: Default constructor for the Player class.
Parameters: None
Return Value: None
Assistance Received: None
********************************************************************* */
Player::Player() {

	score = 0;
	handOfPlayer;
	hasGoneOut = false;

}

/* *********************************************************************
Function Name: getScore()
Purpose: Selector for the score variable.
Parameters: None
Return Value: score -> int that represents the score of the player
Assistance Received: None
********************************************************************* */
int Player::getScore() {

	return score;

}

/* *********************************************************************
Function Name: getHandOfPlayer()
Purpose: Selector for the handOfPlayer variable.
Parameters: None
Return Value: handOfPlayer -> Hand object that represents the hand of the player
Assistance Received: None
********************************************************************* */
Hand Player::getHandOfPlayer() {

	return handOfPlayer;

}

/* *********************************************************************
Function Name: makeMeld
Purpose: Creates a meld for the player by utilizing three cards in the player's deck.
Parameters: 
			one -> Card object that represents the first card to make a meld
			two -> Card object that represents the second card to make a meld
			three -> Card object that represents the third card to make a meld

Return Value: handOfPlayer ->  Hand object that represents the hand of the player
Assistance Received: None
********************************************************************* */
bool Player::makeMeld(Card one, Card two, Card three) {

	return handOfPlayer.makeMeld(one, two, three);

}

/* *********************************************************************
Function Name: makeMeld
Purpose: Creates a meld by setting the three cards to their positions in the deck.
Parameters:
			possibleMeld -> a vector of Cards that represents the meld that will possible be created

Return Value: handOfPlayer ->  Hand object that represents the hand of the player
Algorithm:
			1. Check if the player's hand has three cards to make a meld.
			2. If the player's hand does not have all three cards, return false.
			3. If the player's hand does have all three cards, remove them from the hand and add them to the melds. Return true.
		
Assistance Received: None
********************************************************************* */
bool Player::makeMeld(std::vector<Card> possibleMeld) {

	Card meld1 = possibleMeld.at(0);
	Card meld2 = possibleMeld.at(1);
	Card meld3 = possibleMeld.at(2);

	return handOfPlayer.makeMeld(meld1, meld2, meld3);

}

/* *********************************************************************
Function Name: makeUniqueMeld
Purpose: Creates a special meld in the game.
Parameters:
			cardAdd -> Card object that represents the card to be added in the meld

Return Value: handOfPlayer ->  Hand object that represents the hand of the player
Assistance Received: None
********************************************************************* */
void Player::makeUniqueMeld(Card cardAdd) {

	handOfPlayer.makeMeld(cardAdd);

}

/* *********************************************************************
Function Name: addToHand
Purpose: Adds a card to the player's hand.
Parameters: 
			cardAdd -> Card object that represents the card to be added in the player's hand

Return Value: handOfPlayer ->  Hand object that represents the hand of the player
Assistance Received: None
********************************************************************* */
void Player::addToHand(Card cardAdd) {

	handOfPlayer.addToHand(cardAdd);

}

/* *********************************************************************
Function Name: addToHand
Purpose: Adds multiple cards to the player's hand.
Parameters:
			cardsAdd -> a vector of Cards that represents cards being added to the player's hand

Return Value: handOfPlayer ->  Hand object that represents the hand of the player
Assistance Received: None
********************************************************************* */
void Player::addToHand(std::vector<Card> cardsAdd) {

	handOfPlayer.addToHand(cardsAdd);

}

/* *********************************************************************
Function Name: scoreAdd
Purpose: Adds points to the player's score as the game goes on.
Parameters:
			addingScore -> int that represents the points to be added
Return Value: void
Assistance Received: None
********************************************************************* */
void Player::scoreAdd(int addingScore) {

	score += addingScore;

}

/* *********************************************************************
Function Name: hasACanasta()
Purpose: Checks to see if a player has a Canasta.
Parameters: None
Return Value: handOfPlayer ->  Hand object that represents the hand of the player
Assistance Received: None
********************************************************************* */
bool Player::hasACanasta() {

	return handOfPlayer.hasACanasta();

}

/* *********************************************************************
Function Name: emptyHand()
Purpose: Empties the hand of the player.
Parameters: None
Return Value: handOfPlayer ->  Hand object that represents the hand of the player
Assistance Received: None
********************************************************************* */
bool Player::emptyHand() {

	return handOfPlayer.emptyHand();

}

/* *********************************************************************
Function Name: destroyRedThrees
Purpose: Destroys all red threes in the player's hand.
Parameters: None
Return Value: handOfPlayer ->  Hand object that represents the hand of the player
Assistance Received: None
********************************************************************* */
void Player::destroyRedThrees() {

	handOfPlayer.destroyRedThrees();

}

/* *********************************************************************
Function Name: cardLayoff
Purpose: Looks for a card in the player's hand to be melded with another card's meld position.
Parameters:
			add -> Card object that represents the card to be added to a meld
			meldNum -> int that represents the meld number for the card to be added to

Return Value: handOfPlayer ->  Hand object that represents the hand of the player
Assistance Received: None
********************************************************************* */
bool Player::cardLayoff(Card add, int meldNum) {

	return handOfPlayer.cardLayOff(add, meldNum);

}

/* *********************************************************************
Function Name: cardTransfer
Purpose: Transfers a wild card from a player's hand.
Parameters:
			wildCard -> Card object that represents a wild card
			wildRoot -> int that represents the origin of the wild card
			meldNum -> int that represents the meld number for the wild card to transfer to

Return Value: handOfPlayer ->  Hand object that represents the hand of the player
Assistance Received: None
********************************************************************* */
bool Player::cardTransfer(Card wildCard, int wildRoot, int meldNum) {

	return handOfPlayer.wildCardTransfer(wildCard, wildRoot, meldNum);

}

/* *********************************************************************
Function Name: handRemoval
Purpose: Removes a card from the player's hand.
Parameters:
			cardDiscard -> Card object that represents the card being discarded from the player's hand

Return Value: handOfPlayer ->  Hand object that represents the hand of the player
Assistance Received: None
********************************************************************* */
bool Player::handRemoval(Card cardDiscard) {

	return handOfPlayer.handRemoval(cardDiscard);

}

/* *********************************************************************
Function Name: handSort()
Purpose: Sorts the player's hand.
Parameters: None
Return Value: handOfPlayer ->  Hand object that represents the hand of the player 
Assistance Received: None
********************************************************************* */
void Player::handSort() {

	handOfPlayer.sort();

}

/* *********************************************************************
Function Name: canGoOut()
Purpose: Checks if a player can go out or not.
Parameters: None
Return Value: bool that checks if a player can go out or not
Algorithm:
			1. Check if the player's hand is empty.
			2. Check if the player has a Canasta, which is a meld of at least 7 cards of the same rank.
			3. If both conditions are true, return true. Otherwise, return false.

Assistance Received: None
********************************************************************* */
bool Player::canGoOut() {

	if (handOfPlayer.emptyHand() == true && hasACanasta())
		return true;

	else
		return false;

 }

/* *********************************************************************
Function Name: outputHandTemp()
Purpose: Output the player's hand and melds information.
Parameters: None
Return Value: void
Algorithm:
			1. Print a message  indicating that the following information is about the player's hand and melds.
			2. Print a message indicating that the following information is about the player's hand only.
			3. Call the Player class's outputHand function to print the player's hand to the console.
			4. Print a message indicating that the following information is about the melds of the player.
			5. Call the Player class's outputMelds function to print the player's melds to the console.

Assistance Received: None
********************************************************************* */
void Player::outputHandTemp() {

	std::cout << std::endl;
	std::cout << "Hand and Melds Info: " << std::endl;
	std::cout << "Hand: "; getHandOfPlayer().outputHand();
	std::cout << "      ";

	for (int i = 0; i < getHandOfPlayer().getHandSize(); i++) {

		std::cout << (i + 1);

		if (i + 1 <= 9)
			std::cout << "  ";

		else if (i + 1 <= 99) 
			std::cout << " ";

	}

	std::cout << std::endl;
	std::cout << "Melds: "; getHandOfPlayer().outputMelds();
	std::cout << std::endl;

}
/* *********************************************************************
Function Name: getMeldScore
Purpose: Selector for the meldPosition variable.
Parameters:
			meldPosition -> int that represents the position of a meld
Return Value: 0
Assistance Received: None
********************************************************************* */
int Player::getMeldScore(int meldPosition) {

	return 0;

}

/* *********************************************************************
Function Name: getVectorWildCards
Purpose: Gets the wild cards in order to do wild card transferring.
Parameters:
			cardVector -> a vector of cards
Return Value: wildCardsVector -> a vector of Cards that represents the wild cards of the player's hand
Algorithm:
			1. Initialize an empty vector to store the wild cards.
			2. Iterate through the elements of the input vector cardVector.
			3. For each element card in cardVector, check if it is a wild card and if its transfer attribute is set to false.
			4. If both conditions are true, add card to wildCardsVector.
			5. After the loop finishes, return wildCardsVector.

Assistance Received: None
********************************************************************* */
std::vector<Card> Player::getVectorWildCards(std::vector<Card> cardVector) {

	std::vector<Card> wildCardsVector;

	for (int cardPosition = 0; cardPosition < cardVector.size(); cardPosition++) {

		if (cardVector.at(cardPosition).isWild() && cardVector.at(cardPosition).getTransfer() == false) {

			wildCardsVector.push_back(cardVector.at(cardPosition));

		}

	}

	return wildCardsVector;

}

/* *********************************************************************
Function Name: setHand
Purpose: Mutator for the handContainer variable.
Parameters:
			handContainer -> a vector of Cards that represents a player's hand

Return Value: void
Assistance Received: None
********************************************************************* */
void Player::setHand(std::vector<Card> handContainer) {

	handOfPlayer.setHand(handContainer);

}

/* *********************************************************************
Function Name: setMeld
Purpose: Mutator for the meldContainer variable.
Parameters:
			meldContainer -> a vector of a vector of Cards that represents the melds of the hand

Return Value: handOfPlayer ->  Hand object that represents the hand of the player 
Assistance Received: None
********************************************************************* */
void Player::setMeld(std::vector<std::vector<Card>> meldContainer) {

	handOfPlayer.setMeld(meldContainer);

}

/* *********************************************************************
Function Name: setPlayerScore
Purpose: Mutator for the score variable.
Parameters:
			score -> int that represents the player's score
Return Value: void
Assistance Received: None
********************************************************************* */
void Player::setPlayerScore(int score) {

	this->score = score;

}

/* *********************************************************************
Function Name: existingMeld
Purpose: Looks to see if a meld exists in the player's hand.
Parameters:
			lookForCard -> Card object that represents looking for a card in the hand to make a meld
Return Value: handOfPlayer ->  Hand object that represents the hand of the player 
Assistance Received: None
********************************************************************* */
bool Player::existingMeld(Card lookForCard) {

	return handOfPlayer.existingMeld(lookForCard);

}

/* *********************************************************************
Function Name: getMeldPosition
Purpose: Will return the positions of the melds for the MELD PHASE of the game.
Parameters:
				meldVector -> a vector of Cards that represents a vector of melds
Return Value: 
				meldPosition -> int that represents which position coordinates with a med
				errPosition -> int that represents a default error position of -999
Algorithm:
			1. For each element in meldContainer, do the following:
				a. If the first element of meldVector is equal to the first element of the 
				   meldPosition element of meldContainer, return meldPosition.
			2. Return errPosition.

Assistance Received: None
********************************************************************* */
int Player::getMeldPosition(std::vector<Card> meldVector) {

	int elementOne = 0;
	int errPosition = -999;
	Hand handOfPlayer = getHandOfPlayer();
	std::vector<std::vector<Card>> meldContainer = handOfPlayer.getMeld();

	for (int meldPosition = 0; meldPosition < meldContainer.size(); meldPosition++) {

		if (meldVector.at(elementOne) == meldContainer.at(meldPosition).at(elementOne))

			return meldPosition;

	}

	return -errPosition;

}

/* *********************************************************************
Function Name: meldSort
Purpose: Sorts the melds from the player's hand.
Parameters:
			sortingMelds -> a vector of a vector of Cards that represents the melds to be sorted

Return Value: bool for if one side of the vector is greater than the other
Algorithm:
			1. Use the sort function to sort the elements of the sortingMelds vector in 
			   non-descending order based on the size of each element, which is a vector of Card objects.
			2. Use a lambda function as the third argument of the sort function to 
			   specify the comparison function. The lambda function should take in two vectors of Card objects and 
			   return a boolean value indicating whether the size of the first vector is greater than the size of the second vector.
			3. The sort function will use the lambda function to compare the size of each pair of vectors in the sortingMelds vector
			   and rearrange the elements in non-descending order based on the size.
			4. The meldSort function should then return, as the sorting of sortingMelds has been completed.

Assistance Received: None
********************************************************************* */
void Player::meldSort(std::vector<std::vector<Card>> &sortingMelds) {

	int cardOnePosition = 0;

	std::sort(sortingMelds.begin(), sortingMelds.end(), [cardOnePosition]
	(const std::vector<Card>& leftHandSide, const std::vector<Card>& rightHandSide) {

		return leftHandSide.size() > rightHandSide.size();

});

}

/* *********************************************************************
Function Name: outputVector
Purpose: Outputs brackets for each meld to go in.
Parameters:
			vectorToOutput -> a vector of Cards that represents a vector to have its' cards outputted
Return Value: void
Algorithm:
			1. Append the opening square bracket and a space to output.
			2. Iterate through each Card in vectorToOutput. For each Card:
				1. Append the Card's string representation and a space to output.
			3. Append the closing square bracket and a space to output.
			4. Convert ss to a string and output it to the console.
		
Assistance Received: None
********************************************************************* */
void Player::outputVector(std::vector<Card> vectorToOutput) {

	std::cout << "[ ";

	for (Card card : vectorToOutput) {

		std::cout << card.getCardStr() << " ";

	}

	std::cout << "] " << std::endl;

}

/* *********************************************************************
Function Name: outputMeld
Purpose: Outputs the player's melds.
Parameters:
			meldPosition -> int that represents the meld's position
Return Value: void
Algorithm:
			1. Retrieve the player's hand using getHandOfPlayer().
			2. Retrieve the meld container from the hand using getMeld().
			3. Access the meld at the specified position in the meld container using at().
			4. Pass the meld as an argument to the outputVector() function to output the meld.

Assistance Received: None
********************************************************************* */
void Player::outputMeld(int meldPosition) {

	Hand handOfPlayer = getHandOfPlayer();
	std::vector<std::vector<Card>> meldContainer = handOfPlayer.getMeld();
	outputVector(meldContainer.at(meldPosition));

}

/* *********************************************************************
Function Name: deleteHand()
Purpose: Deletes all the data in the player's hand.
Parameters: None
Return Value: void
Assistance Received: None
********************************************************************* */
void Player::deleteHand() {

	handOfPlayer.deleteData();

}

/* *********************************************************************
Function Name: deleteTransfer()
Purpose: Deletes any card used during the "Transfer Wildcards" part of the MELD PHASE.
Parameters: None
Return Value: void
Assistance Received: None
********************************************************************* */
void Player::deleteTransfer() {

	handOfPlayer.deleteTransfer();

}

/* *********************************************************************
Function Name: deleteHandAndMeld()
Purpose: Deletes both the player's hand and their melds.
Parameters: None
Return Value: void
Assistance Received: None
********************************************************************* */
void Player::deleteHandAndMeld() {

	handOfPlayer.deleteData();

}

/* *********************************************************************
Function Name: getCriticalCard
Purpose: Takes in a vector of opponent's melds and returns the number of "critical cards" in the player's hand.
Parameters:
			opponentMelds -> a vector of a vector of Cards that represents the opposing player's melds
Return Value: criticalAmount -> int that represents the amount of "critical cards"
Algorithm:
			1. Get the hand of the player.
			2. For each card in "handContainer":
				1. For each meld in "opponentMelds":
					1. If the face value of the card is equal to the face value of the 
					   first card in the meld and the size of the meld is 6, increment "criticalAmount" by 1.

Assistance Received: None
********************************************************************* */
int Player::getCriticalCards(std::vector<std::vector<Card>> opponentMelds) {

	Hand handOfPlayer = getHandOfPlayer();
	int criticalAmount = 0;
	std::vector<Card> handContainer = handOfPlayer.getHandContainer();

	for (int cardPosition = 0; cardPosition < handContainer.size(); cardPosition++) {

		for (int meldPosition = 0; meldPosition < opponentMelds.size(); meldPosition++) {

			if (handContainer.at(cardPosition).getFace() ==
				opponentMelds.at(meldPosition).at(0).getFace()
				&& opponentMelds.at(meldPosition).size() == 6) {

				criticalAmount++;

			}

		}

	}

	return criticalAmount;

}

/* *********************************************************************
Function Name: isACriticalCard
Purpose: Checks if a given card is a "critical card" by checking if the face value of the card 
		 is the same as the face value of the first card in any of the melds belonging to the opponent.
Parameters:
			possibleCriticalCard -> Card object that represents a "critical card"
			opponentMelds -> a vector of a vector of Cards that represents the opposing player's melds

Return Value: bool for if the card's face value matched the first card's face value in any of the opponent's melds
Algorithm:
			1. Loop through each meld.
			2. For each meld, check if the face value of the card is equal
			   to the face value of the first card in the meld.
			3. If the face values are equal, set "isCritical" to true and break out of the loop.

Assistance Received: None
********************************************************************* */
bool Player::isACriticalCard(Card possibleCriticalCard, std::vector<std::vector<Card>> opponentMelds) {

	for (int meldPosition = 0; meldPosition < opponentMelds.size(); meldPosition++) {

		if (possibleCriticalCard.getFace() == opponentMelds.at(meldPosition).at(0).getFace())

			return true;

	}

	return false;

}

/* *********************************************************************
Function Name: getGoOutChoice()
Purpose: Selector for having player go out.
Parameters: None
Return Value: hasGoneOut -> bool that represents if a player has gone out or not
Assistance Received: None
********************************************************************* */
bool Player::getGoOutChoice() const {

	return hasGoneOut;

}

/* *********************************************************************
Function Name: setGoOutChoice
Purpose: Mutator for the goOutChoice variable.
Parameters:
			goOutChoice -> bool that represents the decision made by the player to go out
Return Value: void
Assistance Received: None
********************************************************************* */
void Player::setGoOutChoice(bool goOutChoice) {

	hasGoneOut = goOutChoice;

}

/* *********************************************************************
Function Name: goOut()
Purpose: Has a player go out of the round/game.
Parameters: None
Return Value: didDecideToGoOut -> bool that represents if the player decided to go out
Algorithm:
		1. Check if the player is able to go out by calling"canGoOut". If the player is not able to go out, return false.
		2. Ask the player if they want to go out by calling "decideGoOut". If the player does not want to go out, return false.
		3. Set the player's go out choice to true by calling "setGoOutChoice".
		4. Return true to indicate that the player has decided to go out.

Assistance Received: None
********************************************************************* */
bool Player::goOut() {

	bool ableToGoOut = canGoOut();
	bool didDecideToGoOut = false;

	if (ableToGoOut) {

		didDecideToGoOut = decideGoOut();

		if (didDecideToGoOut) {

			setGoOutChoice(true);

		}

	}

	return didDecideToGoOut;

}