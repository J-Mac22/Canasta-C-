#include "Hand.h"

/* *********************************************************************
Function Name: Hand()
Purpose: Default constructor for Hand class.
Parameters: None
Return Value: None
Assistance Received: None
********************************************************************* */
Hand::Hand() {

	handContainer.reserve(15);
	meldContainer.reserve(15);

	handContainer.resize(0);
	handContainer.resize(0);

}

/* *********************************************************************
Function Name: Hand
Purpose: Default constructor for Hand class.
Parameters:
			handDebug -> a vector of Cards representing debugging the player's hand
Return Value: None
Assistance Received: None
********************************************************************* */
Hand::Hand(std::vector<Card> handDebug) {

	handContainer = handDebug;

}


/* *********************************************************************
Function Name: makeMeld
Purpose: Creates a meld of three cards.
Parameters:
				one -> Card representing the first card to be melded 
				two -> Card representing the second card to be melded 
				three -> Card representing the third card to be melded 
Return Value: bool
Algorithm:
				1. Create a vector containing the three cards for melding.
				2. Check if any of the cards are special cards (i.e., jokers). 
				   If any of them are, print an error message and return false.
				3. Check if any of the cards are wild cards. 
				   If there are more than one wild card, print an error message and return false.
				4. If the first three conditions are not met, check if the ranks of all three cards are the same. 
				   If they are, check if a meld with that rank already exists. If it does, print an error message and return false. 
				   If it does not, add the meld to the container of melds and remove the three cards from the hand, then return true.
				5. If the ranks of the three cards are not the same, find the wild card if it exists. If there is no wild card or more than one wild card, print an error message and return false.
				6. If there is only one wild card, remove it from the vector.
				7. Check if the ranks of the two remaining cards are the same. 
				   If they are, check if a meld with that rank already exists. 
				   If it does, print an error message and return false. If it does not, add the meld to the container.
Assistance Received: None
********************************************************************* */
bool Hand::makeMeld(Card one, Card two, Card three) {

	std::vector<Card> possibleMeld = { one, two, three };

	//To make sure melds don't duplicate
	char cRank;

	if (one.isSpecial() || two.isSpecial() || three.isSpecial()) {

		std::cout << "Error: Unable to make a meld out of cards that are special" << "."  << std::endl;
		return false;

	}

	bool hasAWild = (one.isWild() || two.isWild() || three.isWild());


	if ((one.getFace() == two.getFace() && two.getFace() == three.getFace()) && !hasAWild) {

		cRank = one.getFace();

		if (notADuplicate(cRank)) {

			meldContainer.push_back(possibleMeld);

			for (int cardPosition = 0; cardPosition < 3; cardPosition++) {

				handRemoval(possibleMeld.at(cardPosition));

			}

			return true;

		}

		else {

			std::cout << "Error: Meld " << one.getFace() << "exists" << "." << std::endl;
			return false;

		}

	}

	else {

		int cardPosition = 0;
		Card wildCard;
		int countingWilds = 0;
		int wildCardPosition = 0;

		//Searching for a wild card in the possible meld.
		for (cardPosition = 0; cardPosition < 3; cardPosition++) {

			if (possibleMeld.at(cardPosition).isWild()) {

				wildCard = possibleMeld.at(cardPosition);
				wildCardPosition = cardPosition;
				countingWilds++;
				 
			}
		}


		if (countingWilds <= 1)

			possibleMeld.erase(possibleMeld.begin() + wildCardPosition);


		//Break only if wild card is unable to be removed.
		if (possibleMeld.size() == 3) {

			std::cout << "Error: Melds need to be of the same rank or have a wild card" << "." << std::endl;
			return false;

		}

		//A meld will be considered valid if the two remaining cards are contained in the same rank.
		else if (possibleMeld.at(0).getFace() == possibleMeld.at(1).getFace()) {

			if (notADuplicate(possibleMeld.at(0).getFace())) {

				wildCard.setTransfer(true);
				possibleMeld.push_back(wildCard);
				meldContainer.push_back(possibleMeld);

				for (int cardPosition = 0; cardPosition < 3; cardPosition++) {

					handRemoval(possibleMeld.at(cardPosition));

				}

				return true;

			}

			else {

				std::cout << "Error: Meld  " << one.getFace() << "exists" << "." << std::endl;
				return false;

			}

		}

		//However, return false since the meld is not considered to be valid.
		else {

			std::cout << "Error: Melds need to be of the same rank or have a wild card" << "." << std::endl;
			return false;

		}

	}

}

/* *********************************************************************
Function Name: makeMeld
Purpose: Makes a meld while utilizing red threes.
Parameters:
			redThree -> Card object representing the red threes in the deck of cards
Return Value: bool for if there is a red three or not
Algorithm:
			1. Check if the Card is a special card by checking if it is a red three (suit is 'H' or 'D').
			2. If the Card is a special card, create a vector of Cards containing only the special Card.
			3. Add the vector of Cards to the meld container.
			4. Remove the special Card from the Hand.
			5. Return true to indicate that a meld was successfully made.
			6. If the Card is not a special card, return false to indicate that a meld could not be made.
Assistance Received: None
********************************************************************* */
bool Hand::makeMeld(Card redThree) {

	if (redThree.isSpecial() && (redThree.getSuit() == 'H' || redThree.getSuit() == 'D')) {

		std::vector<Card> specialMeld;
		specialMeld.push_back(redThree);
		meldContainer.push_back(specialMeld);
		handRemoval(redThree);

		return true;

	}

	else {

		return false;

	}

}

/* *********************************************************************
Function Name: canMeld
Purpose: Shows that the head of the discard pile is meldable.
Parameters:
			headDiscard -> Card object representing the head of the discard pile
Return Value: bool
Algorithm:
			1. Initialize variables consistentCards and wildCards to 0. 
			   These variables will be used to track the number of cards in the player's hand that have 
			   the same rank as the head of the discard pile and the number 
			   of wild cards in the player's hand, respectively.
			2. Check if the head of the discard pile is a special card. 
			   If it is, then return true if the suit is either 'H' or 'D', and false otherwise.
			3. If the head of the discard pile is not a special card, check if it is a wild card. 
			   If it is, then iterate through the player's hand and for each card, 
			   count the number of cards in the player's hand that have the same rank. 
			   If there are at least 2 such cards, return true. Otherwise, return false.
			4. If the head of the discard pile is not a special card or a wild card, 
			   then iterate through the player's hand and count the number of cards in the player's 
			   hand that have the same rank as the head of the discard pile and the number of wild cards. 
			   If there is at least one card in the player's hand that has the same rank as 
			   the head of the discard pile and at least one wild card, or there are at least 
			   two cards in the player's hand that have the same rank as the head of the discard pile, return true. 
			   Otherwise, return false.
Assistance Received: None
********************************************************************* */
bool Hand::canMeld(Card headDiscard) {

	int consistentCards = 0;
	int wildCards = 0;

	if (headDiscard.getTransfer())
		return false;

	if (headDiscard.isSpecial()) {

		if (headDiscard.getSuit() == 'H' || headDiscard.getSuit() == 'D')
			return true;

		else
			return false;

	}

	else if (headDiscard.isWild()) {
		 
		for (int cardPosition = 0; cardPosition < handContainer.size(); cardPosition++) {

			for (int similarCardPosition = 0; similarCardPosition < handContainer.size(); similarCardPosition++) {

				if (handContainer.at(similarCardPosition).getFace() == handContainer.at(cardPosition).getFace())
					consistentCards++;

				if (consistentCards >= 2) {

					return true;

				}

			}

		}

		return false;
	}

	else {

		for (int card = 0; card < handContainer.size(); card++) {

			if (handContainer.at(card).isWild())
				wildCards = wildCards + 1;

			if (handContainer.at(card).getFace() == headDiscard.getFace())
				consistentCards++;

		}

		if ((consistentCards >= 1 && wildCards >= 1) || (consistentCards >= 2))
			return true;

		else
			return false;

	}

}

/* *********************************************************************
Function Name: canMeldWithMelds
Purpose: Checks if the head of the discard pile can be melded with existing melds in the hand.
Parameters:
			headDiscard -> Card object representing head of the Discard pile
Return Value: bool
Algorithm:
			 1. Check if the head of the discard pile is a special card (Jokers and 2s). 
			    If it is, return true if the suit of 
				the discard head is either hearts or diamonds, and false otherwise.
			 2. Check if head of discard pile  is a wild card. If it is, iterate through each meld in the hand 
			    and check  if the meld is not a special card and has less than 3 wild cards. 
				If both conditions are true, return true.
			 3. If head of discard pile is a natural card, iterate through each meld in the hand and 
			    check if the rank of head of discard pile matches the rank of the first card in the meld. 
				If a match is found, the function returns true.
			 4. If none of the above conditions are met, return false.
Assistance Received: None
********************************************************************* */
bool Hand::canMeldWithMelds(Card headDiscard) {

	bool isMeldable = false;

	if (headDiscard.isSpecial()) {

		if (headDiscard.getSuit() == 'H' || headDiscard.getSuit() == 'D')
			return true;

		else
			return false;

	}

	else if (headDiscard.isWild()) {

		for (int meldPosition = 0; meldPosition < meldContainer.size(); meldPosition++) {

			if (!meldContainer.at(meldPosition).at(0).isSpecial() && getWildCards(meldPosition).size() < 3)

				return true;

		}

	}

	else if (headDiscard.isNatural()) {

		for (int meldPosition = 0; meldPosition < meldContainer.size(); meldPosition++)

			if (headDiscard.getFace() == meldContainer.at(meldPosition).at(0).getFace())
				return true;

	}

	return false;

}

/* *********************************************************************
Function Name: wildCardTransfer
Purpose: Allows a player to transfer a wild card from one meld to another.
Parameters:
			transfer -> Card object representing the wild card that is being transferred
			wildRoot -> int representing the origin of the wildcard
			meldSubject -> int represneting the position of the meld
Return Value: bool
Algorithm:  
			1. Check if the selected card is a wild card. If it is not, return false and print an error message.
			2. Check if the meld from which the wild card is being transferred 
			   has a size less than or equal to 3. If it does, return false and print an error message.
			3. Check if the wild card has already been transferred in the current turn. 
			4. Check if the wild card is in the meld from which it is being transferred. 
			5. Check if the meld to which the wild card is being transferred has a size of at least 3. 
			6. Remove the wild card from the meld it is being transferred from.
			7. Set the transfer status of the wild card to true.
			8. Add the wild card to the meld it is being transferred to.
			9. Return true to indicate that the wild card was successfully transferred.
Assistance Received: None
********************************************************************* */
bool Hand::wildCardTransfer(Card transfer, int wildRoot, int meldSubject) {

	std::vector<Card> wildVectorRoot = meldContainer.at(wildRoot);

	if (transfer.isWild()) {

		if (meldContainer.at(wildRoot).size() <= 3) {

			std::cout << "The selected meld is too small. Please transfer with a meld with a size greater than 3." << std::endl;
			return false;

		}

		if (transfer.getTransfer()== true) {

			std::cout << "The current card has only been transferred once. Please transfer wild cards once a turn." << std::endl;
			return false;

		}


		if (meldSubject == -2) {

			if (canMeld(transfer)) {

				auto itrWild = std::find(meldContainer.at(wildRoot).begin(), meldContainer.at(wildRoot).end(), transfer);
				meldContainer.at(wildRoot).erase(itrWild);
				handContainer.push_back(transfer);
				return true;

			}

			else {

				std::cout << "Cannot transfer wild card. Unable to create melds with this hand." << std::endl;
				return false;

			}

		}


		//Checks to see if a wild card is in a meld
		auto itrWild = std::find(meldContainer.at(wildRoot).begin(), meldContainer.at(wildRoot).end(), transfer);

		//Transfer wild card over only if it is found
		if (itrWild != meldContainer.at(wildRoot).end() && meldContainer.at(meldSubject).size() >= 3) {

			meldContainer.at(wildRoot).erase(itrWild);
			transfer.setTransfer(true);
			meldContainer.at(meldSubject).push_back(transfer);

			return true;

		}

		else
			std::cout << "Error: Can't transfer wildcard of meld that is size 3 or less, or wild card has not been found." << std::endl;
			return false;

	    }

	else {

		std::cout << "This selected card is not a wild card." << std::endl;
		return false;

	}

}

/* *********************************************************************
Function Name: cardLayoff
Purpose: Adds a card to a pre-existing meld.
Parameters:
			add -> Card object that represents the cards being added to a pre-existing meld
			meldNum -> int that represents the meld's number
Return Value: bool
Algorithm:
			1. Check if the meld being added to consists of special cards (red threes).  
			2. See if the added card is a special card.  
			3. See if the added card is a wild card. If it is:
				a. Count the number of wild cards in the meld.
				b. If the number of wild cards is less than 3, set the transfer attribute of the card to true 
				   and add it to the meld. Remove the card from the hand and return true.
				c. If the number of wild cards is 3 or more, print an error message and return false.
			4. If the card being added is not a wild card, check if its face matches the 
			   face of the meld it is being added to. If it does, add it to the meld and 
			   remove it from the hand. Return true. If it does not match, print an error message and return false.
Assistance Received: None
********************************************************************* */
bool Hand::cardLayOff(Card add, int meldNum) {

	std::vector <Card> meldExisting = meldContainer.at(meldNum);

	if (meldExisting.at(0).isSpecial()) {

		std::cout << "Error: Can't add onto a meld of a red three." << std::endl;
		return false;

	}

	if (add.isSpecial()) {

		std::cout << "Error: Can't add special cards to meld." << std::endl;
		return false;

	}

	if (add.isWild()) {

		int wildCount = 0;

		//Counting how many wild card are there
		for (int cardPosition = 0; cardPosition < meldExisting.size(); cardPosition++)

			if (meldExisting.at(cardPosition).isWild())

				wildCount++;

		if (wildCount < 3) {

			add.setTransfer(true);
			meldContainer.at(meldNum).push_back(add);
			handRemoval(add);
			return true;

		}


		else {

			std::cout << "Error: Meld has too many wild cards." << std::endl;
			return false;

		}


	}

	//If not, check to see if it is going to the correct meld.
	else {

		if (add.getFace() == meldExisting.at(0).getFace()) {

			meldContainer.at(meldNum).push_back(add);
			handRemoval(add);
			return true;

		}

		else {

			std::cout << "Error: Faces don't match the meld." << std::endl;
			return false;

		}

	}

}

/* *********************************************************************
Function Name: handRemoval
Purpose: Removes a card from the hand container.
Parameters:
			cardDiscard -> Card object representing the card to be removed
Return Value: bool for if card is found in the container or not
Algorithm:
			1. Look for  a card in the hand container.
			2. If the card is found in the container, remove it and return true.
			3. Otherwise, return false.
Assistance Received: None
********************************************************************* */
bool Hand::handRemoval(Card cardDiscard) {

	itrCard itrDiscard = std::find(handContainer.begin(), handContainer.end(), cardDiscard);

	if (itrDiscard != handContainer.end()) {

		handContainer.erase(itrDiscard);
		return true;

	}

	else {

		return false;

	}

}

/* *********************************************************************
Function Name: isACanasta
Purpose: Checks if a particular meld has reached a size of 7 or more cards.
Parameters:
			meldNum -> int representing the meld's number
Return Value: bool for if a player has a Canasta or not
Algorithm:
			1. Check if the meld's size is greater than or equal to 7.
			2. If it is, return true.
			3. Otherwise, return false.
Assistance Received: None
********************************************************************* */
bool Hand::isACanasta(int meldNum) {

	if (meldContainer.at(meldNum).size() >= 7)
		return true;

	else
		return false;

}

/* *********************************************************************
Function Name: notADuplicate
Purpose: Takes in a rank and checks if it already exists in the meld container.
Parameters:
			rank -> char representing the rank of a card
Return Value: bool for if ranks are the same
Algorithm:
			1. Take in a rank and see if it exists already in the meld container. It will do this
			   by iterating through each meld in the container and getting the first element of each meld.
			2. Get the rank of the first element and compare it to the input tank.
			3. If they are the same, return false indicating that the rank is a duplicate.
			4. If the rank is not found in any of the melds, return true instead.
Assistance Received: None
********************************************************************* */
bool Hand::notADuplicate(char rank) {

	for (std::vector<Card> meld : meldContainer) {

		Card elementOne = meld.at(0);
		char elementOneRank = elementOne.getFace();

		if (rank == elementOneRank) {

			return false;

		}

	}

	return true;

}

/* *********************************************************************
Function Name: emptyHand()
Purpose: Checks if the hand is empty.
Parameters: None
Return Value: isHandEmpty -> bool representing if the hand has been emptied or not
Assistance Received: None
********************************************************************* */
bool Hand::emptyHand() {

	bool isHandEmpty = (handContainer.size() == 0) ? true : false;
	return isHandEmpty;

}

/* *********************************************************************
Function Name: hasACanasta()
Purpose: Iterates through all the melds in the meld container and checks if any of them is a Canasta.
Parameters: None
Return Value: bool for if a Canasta has been found
Algorithm:
			1. Iterate through every meld in the meld container.
			2. Using the isACanasta function, check if any of the melds have a Canasta.
			3. If a Canasta has been found, return true.
			4. Otherwise, return false.
Assistance Received: None
********************************************************************* */
bool Hand::hasACanasta() {

	for (int meldPosition = 0; meldPosition < meldContainer.size(); meldPosition++) {

		if (isACanasta(meldPosition))
			return true;

	}

	return false;

}

/* *********************************************************************
Function Name: createMeldPoints
Purpose: Creates points for each meld made in the game.
Parameters:
				meldNum -> int representing the meld number
Return Value: meldPoints -> int representing the points made from each meld
Algorithm:
			1. Store the total points of the meld.
			2. Access the meld at the specified meld number in the meldContainer vector
			   and store it in another vector.
			3. Iterate through each card in the other vector.
			4. For each iteration, add the point value of the current card.
Assistance Received: None
********************************************************************* */
int Hand::createMeldPoints(int meldNum) {

	int meldPoints = 0;
	std::vector<Card> meldSubject = meldContainer.at(meldNum);

	for (itrCard card = meldSubject.begin(); card != meldSubject.end(); card++) {

		meldPoints += card->getPointVal();

	}

	return meldPoints;

}

/* *********************************************************************
Function Name: destroyRedThrees()
Purpose: Gets rid of red threes for melding.
Parameters: None
Return Value: void
Algorithm:
			1. Iterate through all the cards in the hand. 
			2. For each card, check whether the card is a red three.
			3. If the card is a red three, create a meld with that card by calling the makeMeld function.
			4. The makeMeld function will add the red three to the meld container and remove it from the hand container.
Assistance Received: None
********************************************************************* */
void Hand::destroyRedThrees() {

	for (int cardPosition = 0; cardPosition < handContainer.size(); cardPosition++) {

		std::string cardStr = handContainer.at(cardPosition).getCardStr();

		if (cardStr == "3H" || cardStr == "3D") {

			Card redThree = handContainer.at(cardPosition);
			makeMeld(redThree);

		}

	}

}

/* *********************************************************************
Function Name: outputHand()
Purpose: Prints the player's hand to the console.
Parameters: None
Return Value: void
Algorithm:
			1. Iterate through each card in the hand container
			2. For each card, print out the string representation of the card
			3. After all cards have been printed, print a new line character to ensure that the next output is on a new line.
Assistance Received: None
********************************************************************* */
void Hand::outputHand() {

	for (Card hCard : handContainer) {

		std::cout << hCard.getCardStr() << " ";

	}

	std::cout << std::endl;

}

/* *********************************************************************
Function Name: outputMelds()
Purpose: Prints the melds to the console.
Parameters: None
Return Value: void
Algorithm:
			1. Initialize a loop that iterates through each meld in the meld container.
			2. Inside the loop, print out "[ " to mark the beginning of the meld.
			3. Initialize another loop that iterates through each card in the current meld.
			4. Inside the second loop, retrieve the card at the current position.
			5. Print out the string representation of the cards.
			6. After the second loop completes, print out "] " to mark the end of the meld.
Assistance Received: None
********************************************************************* */
void Hand::outputMelds() {

	for (int meld = 0; meld < meldContainer.size(); meld++) {

		std::cout << "[ ";

		for (int card = 0; card < meldContainer.at(meld).size(); card++) {

			Card outputCard = meldContainer.at(meld).at(card);
			std::cout << outputCard.getCardStr() << " ";

		}

		std::cout << "] ";

	}

	std::cout << std::endl;

}

/* *********************************************************************
Function Name: outputEveryWild
Purpose: Prints all the wild cards to the console.
Parameters:
			meldPosition -> int representing the meld's position
Return Value: void 
Algorithm:
			1. Create a vector that stores the cards in the specified meld.
			2. Iterate through the vector and check if each card is a wild card and has not been transferred
			   to another meld yet.
			3. If both conditions are met, the count of wilds is incremented and the wild card is outputted
			   to the console.
Assistance Received: None
********************************************************************* */
void Hand::outputEveryWild(int meldPosition) {

	std::vector<Card> wildMeld = meldContainer.at(meldPosition);

	int countWilds = 0;

	for (int meldPosition = 0; meldPosition < wildMeld.size(); meldPosition++)

		if (wildMeld.at(meldPosition).isWild() && wildMeld.at(meldPosition).getTransfer() == false) {

			countWilds++;
			std::cout << countWilds << ". " << wildMeld.at(meldPosition).getCardStr() << std::endl;

		}

}

/* *********************************************************************
Function Name: addToHand
Purpose: Adds a card to the player's hand.
Parameters:
			cardAdd -> Card object representing the card to be added to the player's hand
Return Value: void
Assistance Received: None
********************************************************************* */
void Hand::addToHand(Card cardAdd) {

	handContainer.push_back(cardAdd);

}

/* *********************************************************************
Function Name: addToHand
Purpose: Adds a card to the player's hand.
Parameters:
			cardAdd -> a vector of Cards representing the card to be added to a player's hand
Return Value: void
Algorithm:
			1. Declare an empty vector of cards called handContainer which will represent the hand.
			2. Create a vector of cards called cardAdd which will represent the cards to be added to the hand.
			3. Iterate through cardAdd using a for loop, starting at the first element and ending at the last element.
			4. For each iteration of the loop, add the current card in cardAdd to the end of handContainer using the push_back method.
			5. After the loop has completed, all the cards have been added to the hand.
Assistance Received: None
********************************************************************* */
void Hand::addToHand(std::vector<Card> cardAdd) {

	for (int cardPosition = 0; cardPosition < cardAdd.size(); cardPosition++) {

		handContainer.push_back(cardAdd.at(cardPosition));

	}

}

/* *********************************************************************
Function Name: getHandSize()
Purpose: Selector for the handContainer variable.
Parameters: None
Return Value: handContainer -> a vector of Cards representing the container of the hand
Assistance Received: None
********************************************************************* */
int Hand::getHandSize() {

	return handContainer.size();

}

/* *********************************************************************
Function Name: getHandContainer()
Purpose: Selector for the handContainer variable.
Parameters: None
Return Value:  handContainer -> a vector of Cards representing the container of the hand
Assistance Received: None
********************************************************************* */
std::vector <Card> Hand::getHandContainer() const {

	return handContainer;

}

/* *********************************************************************
Function Name: getMeld()
Purpose: Selector for the meldContainer veriable.
Parameters: None
Return Value:  meldContainer -> a vector of Cards representing the container of the meld
Assistance Received: None
********************************************************************* */
std::vector<std::vector<Card>> Hand::getMeld() {

	return meldContainer;

}

/* *********************************************************************
Function Name: getMeldCard
Purpose: Selector for the meldContainer variable.
Parameters:
			meldPosition -> int representing the meld's position
			cardPosition -> int representing the card's position
Return Value:  meldContainer -> a vector of Cards representing the container of the meld
Assistance Received: None
********************************************************************* */
Card Hand::getMeldCard(int meldPosition, int cardPosition) {

	return meldContainer.at(meldPosition).at(cardPosition);

}

/* *********************************************************************
Function Name: getMeldSize()
Purpose: Selector for the meldContainer variable.
Parameters: None
Return Value:  meldContainer -> a vector of Cards representing the container of the meld 
Assistance Received: None
********************************************************************* */
int Hand::getMeldSize() {

	return meldContainer.size();

}

/* *********************************************************************
Function Name: getWildCards
Purpose: Selector for the wild cards.
Parameters:
			meldPosition -> int representing the position of the meld
Return Value: wildMeld -> a vecotr of Cards representing wild cards to be melded
Algorithm:
			1. Declare an empty vector to store wild cards.
			2. Iterate through each card in the meld.
			3. For each card in the meld, check if it is a wild card and has not been transferred.
			4. If the card meets these conditions, add it to the vector.
Assistance Received: None
********************************************************************* */
std::vector<Card> Hand::getWildCards(int meldPosition) {

	std::vector<Card> meldExtract = meldContainer.at(meldPosition);
	std::vector<Card> wildMeld;

	for (int meldPosition = 0; meldPosition < meldExtract.size(); meldPosition++)
		if (meldExtract.at(meldPosition).isWild() && !(meldExtract.at(meldPosition).getTransfer()))
			wildMeld.push_back(meldExtract.at(meldPosition));

	return wildMeld;
		 
}

/* *********************************************************************
Function Name: getWildCardsWithoutTransferring
Purpose: Selector for the wild cards without transferring get in the way.
Parameters:
			 meldPosition -> int representing the position of the meld
Return Value: wildMeld -> a vector of Cards representing the wildcards that have been melded
Algorithm:
			1. Extract the meld from the meld container by using the meld's position.
			2. Iterate through the meld and check if each card is a wild card.
			3. If it is, add the wild card to an empty vector.
Assistance Received: None
********************************************************************* */
std::vector<Card> Hand::getWildCardsWithoutTransferring(int meldPosition) {

	std::vector<Card> meldExtract = meldContainer.at(meldPosition);
	std::vector<Card> wildMeld;

	for (int meldPosition = 0; meldPosition < meldExtract.size(); meldPosition++)
		if (meldExtract.at(meldPosition).isWild())
			wildMeld.push_back(meldExtract.at(meldPosition));

	return wildMeld;

}

/* *********************************************************************
Function Name: getWildCardsFromHand
Purpose: Selector for obtaining wild cards from a given hand.
Parameters: None
Return Value: wildVector -> a vector of wild cards
Algorithm:
			1. Iterate through each element in the hand container.
			2. For each element, check if it is a wild card and if it is not transferrable.
			3. If both conditions are true, add the element to an empty vector.
Assistance Received: None
********************************************************************* */
std::vector<Card> Hand::getWildCardsFromHand() {

	std::vector<Card> wildVector;

	for (int cardPosition = 0; cardPosition < handContainer.size(); cardPosition++) {

		if (handContainer.at(cardPosition).isWild() && handContainer.at(cardPosition).getTransfer() == false)

			wildVector.push_back(handContainer.at(cardPosition));

	}

	return wildVector;

}

/* *********************************************************************
Function Name: getCardFromHand
Purpose: Selector for getting a card from a player's hand.
Parameters:
			position -> int representing the position of the hand
Return Value: handContainer -> a vector of Cards representing the container of the Hand
Assistance Received: None
********************************************************************* */
Card Hand::getCardFromHand(int position) {

	return handContainer.at(position);

}

/* *********************************************************************
Function Name: getTotalScore()
Purpose: Selector for the overall player scores of the game.
Parameters: None
Return Value: totalScore -> int representing the total score for both players
Algorithm:
			1. Store the total point value of the cards in the hand that not yet been melded.
			2. Store the total point value of the cards in the meld.
			3. Iterate through all the cards in the hand and add their point values.
			4. Iterate through all the melds in the hand.
				1. For each meld, iterate through all the cards in the meld.
			5. If any of these cards are wild, the meld is not a natural meld.
			6. Add the point value of each card in the meld.
			7. Check if each meld is a natural meld or not.
				1. If a meld is a natural meld and it contains at least 7 cards, add 500 points.
				2. If a meld is not a natural meld but it contains at least 7 cards, add 300 points.
			8. Calculate the total score via subtraction.
Assistance Received: None
********************************************************************* */
int Hand::getTotalScore() {

	int subtractHandScore = 0;
	int addMeldScore = 0;
	bool naturalMeld = true;

	for (int cardPosition = 0; cardPosition < handContainer.size(); cardPosition++)
		subtractHandScore += handContainer.at(cardPosition).getPointVal();

	for (int meldPosition = 0; meldPosition < meldContainer.size(); meldPosition++) {

		for (int meldCardPosition = 0; meldCardPosition < meldContainer.at(meldPosition).size(); meldCardPosition++) {

			if (meldContainer.at(meldPosition).at(meldCardPosition).isWild())
				naturalMeld = false;
			    addMeldScore += meldContainer.at(meldPosition).at(meldCardPosition).getPointVal();

		}

		if (naturalMeld == true && meldContainer.at(meldPosition).size() >= 7)
			addMeldScore += 500;

		else if (naturalMeld == false && meldContainer.at(meldPosition).size() >= 7)
			addMeldScore += 300;

	}

	int totalScore = addMeldScore - subtractHandScore;
	return totalScore;

}

/* *********************************************************************
Function Name: getMeldScore
Purpose: Selector for scores obtained through melding.
Parameters:
			meldPosition -> int representing the position of the meld
Return Value: score -> int representing the score 
Algorithm:
			1. Iterate through each card in the meld.
			2. Add the point value of each card.
Assistance Received: None
********************************************************************* */
int Hand::getMeldScore(int meldPosition) const {

	int score = 0;

	for (int cardPosition = 0; cardPosition < meldContainer.at(meldPosition).size(); cardPosition++) {

		score += meldContainer.at(meldPosition).at(cardPosition).getPointVal();

	}

	return score;

}

/* *********************************************************************
Function Name: setHand
Purpose: Mutator for the handContainer variable.
Parameters:
			handContainer -> a vector of Cards representing the container of the hand
Return Value: void
Assistance Received: None
********************************************************************* */
void Hand::setHand(std::vector<Card> &handContainer) {

	this->handContainer = handContainer;

}

/* *********************************************************************
Function Name: setMeld
Purpose: Mutator for the meldContainer variable.
Parameters:
			meldContainer -> a vector of Cards representing the container of the meld
Return Value: void
Assistance Received: None
********************************************************************* */
void Hand::setMeld(std::vector<std::vector<Card>> &meldContainer) {

	this->meldContainer = meldContainer;

}

/* *********************************************************************
Function Name: deleteTransfer()
Purpose: Sets the transfer of cards in the meld container to false.
Parameters: None
Return Value: void
Algorithm:
			1. Iterate through every meld in the meld container.
			2. For each meld, it iterates through every card in that meld.
			3. For each card, set the transfer to false. (Can be done by using setTransfer())
			4. After this function has been called, all cards in the meld container will have its transfer set to false.
Assistance Received: None
********************************************************************* */
void Hand::deleteTransfer() {

	for (int meldPosition = 0; meldPosition < meldContainer.size(); meldPosition++) {

		std::vector<Card> changeMeld = meldContainer.at(meldPosition);

		for (int card = 0; card < changeMeld.size(); card++)

			meldContainer.at(meldPosition).at(card).setTransfer(false);


	}

}

/* *********************************************************************
Function Name: deleteData()
Purpose: Clears the hand container and the meld container.
Parameters: None
Return Value: void
Assistance Received: None
********************************************************************* */
void Hand::deleteData() {

	handContainer.clear();
	meldContainer.clear();

}

/* *********************************************************************
Function Name: nonSpecificMeldsSize
Purpose: Counts the number of melds that are not special cards.
Parameters: None
Return Value: nonSpecificMeldCounter -> int representing how many melds are not special cards
Algorithm:
			1. Iterate through the meldContainer vector, starting at the first meld and going to the last meld.
			2. For each meld, check if the first card in the meld is not a special card (i.e. not a red three). 
			   If it is not, increment nonSpecificMeldCounter by 1.
			3. After all melds have been checked, return nonSpecificMeldCounter.
Assistance Received: None
********************************************************************* */
int Hand::nonSpecificMeldsSize() const {

	int nonSpecificMeldCounter = 0;

	for (int meldPosition = 0; meldPosition < meldContainer.size(); meldPosition++) {

		if (!meldContainer.at(meldPosition).at(0).isSpecial())

			nonSpecificMeldCounter++;

	}

	return nonSpecificMeldCounter;

}

/* *********************************************************************
Function Name: existingMeld
Purpose: Checks if a card with the same rank exists in any of the melds in the meld container.
Parameters:
			lookForCard -> Card object representing a card with the same rank to be searched
Return Value: bool for if there is a card existing with the same rank or not
Algorithm:
			1. Iterate through each meld in the meld container.
			2. Iterate through each card in the meld. For each card, do the following:
				1. If the rank of the card being looked for is the same as the rank of the current card,
				   return true and break out of the inner loop.
			3. Otherwise, return false.
Assistance Received: None
********************************************************************* */
bool Hand::existingMeld(Card lookForCard) {

	for (int meldPosition = 0; meldPosition < meldContainer.size(); meldPosition++) {

		for (int cardPosition = 0; cardPosition < meldContainer.at(meldPosition).size(); cardPosition++) {

			if (lookForCard.getFace() == meldContainer.at(meldPosition).at(cardPosition).getFace())

				return true;

		}

	}

	return false;

}

/* *********************************************************************
Function Name: sort()
Purpose: Sorting function for the handContainer variable.
Parameters: None
Return Value: void
Assistance Received: None
********************************************************************* */
void Hand::sort() {

	std::sort(handContainer.begin(), handContainer.end());

}