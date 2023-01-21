#include "Human.h"
#include <iostream>

/* *********************************************************************
Function Name: play
Purpose: Has all the components needed for the Human to play Canasta.
Parameters:
			useDecks -> Deck object representing the two decks being utilized in the game
			opponentMelds -> a vector of a vector of Cards representing the melds of the opponent player

Return Value: bool for if the Human player can continue playing
Algorithm:
			1. Declare a bool variable that checks if a Humanplayer can go out depending on the phases of the game.
			2. Don't have Human player go out during the DRAW PHASE.
			3. Check if Human player can go out depending on how the opponent did during the MELD PHASE.
			4. Do the same method for step 3 for the DISCARD PHASE.
			5. Return false and have Human player continue playing otherwise.
Assistance Received: None
********************************************************************* */
bool Human::play(Deck& useDecks, std::vector<std::vector<Card>> opponentMeld) {

	bool instantBreak;

	instantBreak= goOut();
	if (instantBreak) return true;

	instantBreak = draw(useDecks);
	if (instantBreak) return true;

	meld(opponentMeld);
	instantBreak = goOut();
	if (instantBreak) return true;

	discard(useDecks, opponentMeld);
	instantBreak = goOut();

	if (instantBreak) return true;


	return false;

}

/* *********************************************************************
Function Name:  draw
Purpose:  Has components needed for the DRAW PHASE.
Parameters: 
				useDecks -> Deck object representing the two decks being used for drawing 
Return Value: bool
Algorithm:
			1. Print the discard pile and the hand of the player.
			2. Present the user with the option to draw from either the stock pile or the discard pile.
			3. Using a do-while loop, repeat the following steps until a draw is successfully made:
				a. Check the user's input and validate it to be either 1 or 2.
				b. If the user chooses to draw from the stock pile, 
				   check if the stock pile is not empty. If it is not, draw a card and 
				   add it to the player's hand. If it is, inform the user that the stock pile is 
				   empty and to try drawing from the discard pile instead.
				c. If the user chooses to draw from the discard pile, check if the discard pile is not frozen. 
				   If it is not, check if the top card of the discard pile can be melded or laid off 
				   with any card in the player's hand. If it can, draw the top card of the discard pile 
				   and add it to the player's hand. If it cannot, inform the user that no cards in the player's 
				   hand can meld or lay off with the top card of the discard pile. If the discard pile is frozen, 
				   inform the user that they cannot draw from the discard pile and to try drawing from the stock pile instead.
			4. Check if either both piles are empty or the discard pile is frozen 
			   and the stock pile is empty. If either of these conditions are true, 
			   inform the user that the round is over and return true. Otherwise, return false.
Assistance Received: None
********************************************************************* */
bool Human::draw(Deck &useDecks) {

	std::cout << "Discard Pile: " << std::endl;
	useDecks.outputDiscard();
	outputHandTemp();

	std::cout << "DRAW PHASE: Choose a deck to draw from. " << std::endl;
	std::cout << "1. Stock" << std::endl;
	std::cout << "2. Discard " << std::endl;

	bool didDrawFinish = false;
	Hand comparingHand = getHandOfPlayer();
	Card drawnCard;


	if (useDecks.emptyStock() && useDecks.getFrozenDiscard()) {

		std::cout << "Unable to draw, both the stock pile is empty and the discard pile is frozen. Round Over." << std::endl;
		return true;

	}


	do {

		int choice = checkUserInput(1, 2);

		if (choice == 1) {

			if (!useDecks.emptyStock()) {

				//Keeps on drawing a card until the card isn't a red three.
				do {
					drawnCard = useDecks.stockDraw();
					addToHand(drawnCard);
					destroyRedThrees();
				} while (drawnCard.isRedThrees() && !useDecks.emptyStock());

				didDrawFinish = true;

			}

			else {

				std::cout << "Stock pile is empty. Try drawing from the Discard pile instead." << std::endl;

			}

		}

		else {

			if (useDecks.getFrozenDiscard()) {

				std::cout << "Discard pile is frozen. Try drawing from the Stock pile instead." << std::endl;

			}

			else {

				Card topOfDiscard = useDecks.getDiscardTop();
				bool shouldDiscard = (comparingHand.canMeld(topOfDiscard) || comparingHand.canMeldWithMelds(topOfDiscard));

				if (shouldDiscard) {

					std::vector<Card> discardPickUp = useDecks.discardDraw();
					addToHand(discardPickUp);
					destroyRedThrees();
					didDrawFinish = true;

				}

				else {
					std::cout << "No cards in your hand can meld or lay off with top of discard pile. "
						<< topOfDiscard.getCardStr() << std::endl;
				}

			}

		}

	} while (!(useDecks.emptyPiles()) && !(didDrawFinish) ||
		(!useDecks.emptyStock() && !useDecks.getFrozenDiscard() && !(didDrawFinish)));

	if (didDrawFinish == true) {

		return false;

	}

	else {

		std::cout << "Either both piles are empty, or the discard pile is frozen and the stock pile is empty." << std::endl;
		std::cout << "Due to this, end of Round." << std::endl;
		return true;

	}

}

/* *********************************************************************
Function Name: discard
Purpose: Has the components needed for the DISCARD PHASE.
Parameters:
				useDecks -> Deck object representing the two decks being used for discarding
				opponentMelds -> a vector of vector of cards representing the melds of the opponent
Return Value: void
Algorithm:
			 1. Output the current hand of the player and the opponent's melds.
			 2. Check if the player has any cards in their hand. If not, skip the discarding turn and exit the function.
			 3. Prompt the player to select a card from their hand to discard by entering a number between 1 and the number of cards in their hand.
			 4. Retrieve the card the player selected from their hand and assign it to a variable.
			 5. Check if the card to discard is a wild card or special card. If it is, push the card to the top of the discard pile, 
			    remove it from the player's hand, and set the discard pile to "frozen".
			 6. If the card is not a wild card or special card, push the card to the top of the discard pile, 
			    remove it from the player's hand, and set the discard pile to "not frozen"
			 7. Finally, the function exits.
Assistance Received: None
********************************************************************* */
void Human::discard(Deck& useDecks, std::vector<std::vector<Card>> opponentMelds) {

	outputHandTemp();
	outputOpponentMeld(opponentMelds);

	Hand handOfPlayer = getHandOfPlayer();
	int handSize = handOfPlayer.getHandSize();

	if (handSize == 0) {

		std::cout << "There is nothing to discard, so you can skip your discarding turn." << std::endl;
		return;

	}


	std::cout << "DISCARD Phase: What card will you discard? Select a position from 1 to "<< handSize << std::endl;
	int choice = checkUserInput(0, handSize) - 1;
	Card cardToDiscard= handOfPlayer.getCardFromHand(choice);

	if (cardToDiscard.isWild() || cardToDiscard.isSpecial()) {

		useDecks.discardPushFront(cardToDiscard);
		handRemoval (cardToDiscard);
		useDecks.setFrozenDiscard(true);

	}

	else {

		useDecks.discardPushFront(cardToDiscard);
		handRemoval(cardToDiscard);
		useDecks.setFrozenDiscard(false);

	}

}

/* *********************************************************************
Function Name: meld
Purpose: All the components needed for the MELD PHASE.
Parameters:
			useDecks -> Deck object representing the two decks being used for discarding
			opponentMelds -> a vector of vector of cards representing the melds of the opponent
Return Value: void
Algorithm:
			1. Output the opponent's melds and the current hand of the player.
			2. Present the player with options to make a meld, add to a pre-existing meld, transfer wild cards,
			   or end the phase.
			3. Have player choose one of the options by inputtint a number between 1 and 4.
			4. If the player chooses option 1 (Make A Meld), prompt player to input a comma separated list
			   of cards. Confirm if these cards can be melded together, and if they can, remove the cards from the
			   player's hand and add them to the player's melds.
			5. If the player chooses option 2 (Add to Pre-Existing Meld), prompt the player to select a card from their hand,
			   and then select a meld to add that card to. If the card can be added to the meld, remove it from the player's hand
			   and add it to the meld.
			6. If the player chooses option 3 (Transfer Wildcards), prompt the player to select a wild card from their hand
			   and a meld from their melds. If the wildcard can be added to the meld, remove it from the player's hand and 
			   add it to the meld.
			7. If the player chooses option 4 (End Meld Phase), exit the loop and return.
			8. If the player completes a meld operation, output the player's updated hand.
			9. After all the operations, return.
Assistance Received: None
********************************************************************* */
void Human::meld(std::vector<std::vector<Card>> opponentMelds) {

	int option = 0;
	bool operationCompleted = false;
	bool stillMelding = true;
	int choice = 0;

	do {

		outputOpponentMeld(opponentMelds);
		outputHandTemp();

		std::cout << "MELD PHASE: Choose an option." << std::endl;
		std::cout << "1. Make a Meld" << std::endl;
		std::cout << "2. Add to Pre-Existing Meld " << std::endl;
		std::cout << "3. Transfer Wildcards" << std::endl;
		std::cout << "4. End Meld Phase" << std::endl;
		option = checkUserInput(1, 4);

		switch (option) {

		case 1: {

			outputHandTemp();
			operationCompleted = false;
			std::vector<Card> possibleMeld = confirmCommaInput();

			if (possibleMeld.size() == 0)
				break;

			else {

				operationCompleted = makeMeld(possibleMeld);
				outputHandTemp();

			}

			if (!operationCompleted)
				std::cout << "The meld failed. Please see above output^" << std::endl;

			break;

		}

		case 2: {

			do {

				outputHandTemp();
				operationCompleted = false;

				int cardPosition = 0;
				int meldPosition = 0;

				Card cardToLayOff;
				Hand handOfPlayer = getHandOfPlayer();

				if (handOfPlayer.getMeldSize() != 0) {

					std::cout << "ADD TO PRE-EXISTING MELD: Pick a card position from 1 to " << handOfPlayer.getHandSize()
						<< " to add to a pre-existing meld. Type 0 to cancel the operation" << std::endl;

					cardPosition = checkUserInput(0, handOfPlayer.getHandSize()) - 1;

					//For when user enters zero
					if (cardPosition == -1) break;

					cardToLayOff = handOfPlayer.getCardFromHand(cardPosition);

					std::cout << "Good, now pick a meld position from 1 to " << handOfPlayer.getMeldSize()
						<< " to add onto. Enter 0  to stop the operation." << std::endl;

					meldPosition = checkUserInput(0, handOfPlayer.getMeldSize()) - 1;

					//For when user enters zero
					if (meldPosition == -1) break;

					operationCompleted= cardLayoff(cardToLayOff, meldPosition);

					if (!operationCompleted) {

						std::cout << "The lay off operation failed. Please see above output^" << std::endl;
					}

				}

				else {

					std::cout << "Error: No melds to add onto." << std::endl;
					break;

				}

			} while (operationCompleted != true);

			outputHandTemp();
			break;
		}

		case 3: {
		
			outputHandTemp();
			operationCompleted = false;
			int wildPosition = 0;
			int wildCardPosition;
			int meldPosition = 0;
			Card cardToTransfer;
			Hand handOfPlayer = getHandOfPlayer();

			do {

				if (handOfPlayer.getMeldSize() != 0) {

					std::cout << "TRANSFER WILD CARDS: Pick a meld from 1 to " << handOfPlayer.getMeldSize()
						<< " to extract the wild card's position. Typr 0 to cancel the operation" << std::endl;

					wildPosition = checkUserInput(0, handOfPlayer.getMeldSize()) - 1;

					if (wildPosition == -1) break;

					std::vector<Card> wildMeld = handOfPlayer.getWildCards(wildPosition);

					if (wildMeld.size() == 0) {

						std::cout << "The meld you picked has no wild cards that can be transferred." << std::endl;
						break;

					}

					else {
						std::cout << "Good, now pick a card from the following list to transfer. Type 0 to cancel." << std::endl;
						 
						handOfPlayer.outputEveryWild(wildPosition);
						wildCardPosition = checkUserInput(0, wildMeld.size()) - 1;

						if (wildCardPosition == -1)
							break;
						 
						cardToTransfer = wildMeld.at(wildCardPosition);
					}

					std::cout << "Good, now pick a meld position from 1 to " << handOfPlayer.getMeldSize()
						<< " to add onto. Type 0 to cancel the operation." << std::endl;

					std::cout << "Also, enter -1";

					std::cout << " if you want to transfer the wild card back to the hand. You can only do this " <<
						"if you can create a meld with the cards in the hand." << std::endl;

					meldPosition = checkUserInput(-1, handOfPlayer.getMeldSize(), true) - 1;

					if (meldPosition == -1) break;

					if (meldPosition == wildPosition) {

						std::cout << "You don't have to transfer a wild card to the same meld." << std::endl;
						break;

					}

					operationCompleted = cardTransfer(cardToTransfer, wildPosition, meldPosition);

					if (!operationCompleted) {

						std::cout << "That didn't work. Please see the above output." << std::endl;

					}

				}

				else {

					std::cout << "Error: No melds to add onto." << std::endl;
					break;

				}

			} while (operationCompleted != true);

			break;
		}

		case 4:
			stillMelding = false;
			break;
		}

	} while (stillMelding);

}

/* *********************************************************************
Function Name: playerStrategy
Purpose: Brings up the help menu and gives advice to the player about what they should do.
Parameters:
			 useDecks -> Deck object representing the two decks being used for whatever the player does
			 opponentMelds -> a vector of vector of Cards representing the melds of the opponent
Return Value: void
Algorithm:
			1. Print the help menu with help from a do while loop. The user will have to input a number
			   between 1 and 4 for this. 
			2. Create a switch statement that goes to the strategy the player picked. For example,
			   if the user pressed 2, the program will provide help regarding melding for their turn.
Assistance Received: None
********************************************************************* */
void Human::playerStrategy(Deck& useDecks, std::vector<std::vector<Card>> opponentMelds) {

	int pick = 0;

	do {

		std::cout << "What would you like help regarding?" << std::endl;
		std::cout << "1. Drawing" << std::endl;
		std::cout << "2. Melding" << std::endl;
		std::cout << "3. Discarding" << std::endl;
		std::cout << "4. Go out of menu" << std::endl;

		pick = checkUserInput(1, 4);

		switch (pick) {

		case 1:
			strategyDraw(useDecks);
			break;

		case 2:
			strategyMeld(useDecks, opponentMelds);
			break;

		case 3:
			strategyDiscard(useDecks, opponentMelds);
			break;

		case 4:
			return;

		}

	} while (pick != 4);

	return;

}


/* *********************************************************************
Function Name: getTypeOfPlayer()
Purpose: Selector for specifying the type of player is Human.
Parameters: None
Return Value: string representing that the type of player is "Human"
Assistance Received: None
********************************************************************* */
std::string Human::getTypeOfPlayer() {

	return "Human";

}
 

/* *********************************************************************
Function Name: outputTypeOfPlayer()
Purpose: Outputs the type of player which is "Human".
Parameters: None
Return Value: void
Assistance Received: None
********************************************************************* */
void Human::outputTypeOfPlayer() {

	std::cout << "Human";

}

/* *********************************************************************
Function Name: decideGoOut()
Purpose: Asks if the Human player would like to go out only if they have a Canasta and have melded all other cards.
Parameters: None
Return Value: bool for if the player wants to play a new round or not
Algorithm:
			1. If the Human player has a Canasta and has melded all other cards, ask if they would like to go out.
			2. Also, print a reminder to the Human saying that the action will end the round and they will
			   get a bonus 100 points for ending it. 
			3. Print yes and no options.
			4. If the user presses 1, have the game end.
			5. Otherwise, have another round play. 
Assistance Received: None
********************************************************************* */
bool Human::decideGoOut() {

	std::cout << "You can go out, you have a Canasta and have melded all other cards. Would you like to go out?" << std::endl;
	std::cout << "This action will end the round, and you'll get a bonus 100 points for ending it. " << std::endl;
	std::cout << "1. Yes" << std::endl;
	std::cout << "2. No" << std::endl;

	int pick = checkUserInput(1, 2);
	if (pick == 1) return true;
	else return false;

}

/* *********************************************************************
Function Name: outputOpponentMeld
Purpose: Outputs the Computer player's melds. 
Parameters:
			opponentMelds -> a vector of a vector of Cards representing the melds of the opponent player
Return Value: void
Algorithm:
			1. Iterate over each element in the opponentMeld vector, which represents a meld, using a for loop with the meld's position.
			2. Iterate over each element in the inner vector, which represents a card, using a for loop with a variable for the card's position.
			3. Within the inner for loop, use the at() method to access the card at the current card position of the inner vector, and call the getCardStr() method on that card 
			   to get the string representation of the card. Print the string representation of the card to the console.
Assistance Received: None
********************************************************************* */
void Human::outputOpponentMeld(std::vector<std::vector<Card>> opponentMeld) {

	std::cout << "Opponent's melds: " << std::endl;

	for (int meldPosition = 0; meldPosition < opponentMeld.size(); meldPosition++) {

		std::cout << "[ ";

		for (int cardPosition = 0; cardPosition < opponentMeld.at(meldPosition).size(); cardPosition++)

		std::cout << opponentMeld.at(meldPosition).at(cardPosition).getCardStr() << " ";
		std::cout << "] ";

	}

	std::cout << std::endl;
}


/* *********************************************************************
Function Name: confirmCommaInput()
Purpose: Prompts the Human player to input three card positions they want to meld, with the input
		 being comma separated and unique.
Parameters: None
Return Value: cardsToMeld -> a vector of Cards representing each card to be melded via comma separated lines
Algorithm:
			1. Call the getHandOfPlayer() method to get the player's hand, and create a variable to store the result.
			2. Initialize an integer variable for the card's range to the size of the hand of the player.
			3. Create a vector of Card objects to store the cards that the player wants to meld.
			4. Begin a do-while loop that continues until validInput is true.
			5. Print a message to the console prompting the user to input the positions of 
			   the cards they want to meld, separated by commas.
			6. Read the user's input using getline.
			7. If the input is "0", break out of the loop.
			8. Use the erase() method to remove any whitespace from the input string.
			9. Use a stringstream to split the input string at each comma, 
			   and store the resulting substrings in the outcome vector.
			10.Check if the size of the outcome vector is equal to 3. 
			   If not, print an error message to the console and go back to the beginning of the loop
			11.Use the unique() function to remove any duplicates from the outcome vector, 
			   and check if the size of the vector is still equal to 3. If not, 
			   print an error message to the console and go back to the beginning of the loop.
			12.Iterate over each element in the outcome vector using a for loop  
			13.Within the for loop, check if each element of the outcome vector can be 
			   converted to a number using the stoi() function. If not, 
			   print an error message to the console and go back to the beginning of the loop.
			14.If the element can be converted, check if it is between 1 and the card's range. 
			   If not, print an error message to the console and go back to the beginning of the loop.
			15.If the element is valid, use the getCardFromHand() method to get the card 
			   at that position in the player's hand, and add it to the cardsToMeld vector.
			16.After the for loop, check if the cardsToMeld vector has a size of 3.
			   If it does, set validInput to true, else clear the cardsToMeld vector.
			17.End the do-while loop.
Assistance Received: None
********************************************************************* */
std::vector<Card> Human::confirmCommaInput() {

	bool validInput = false;
	std::string input;
	Hand handOfPlayer = getHandOfPlayer();

	int cardRange = handOfPlayer.getHandSize();
	std::vector<Card> cardsToMeld;

	do {

		std::cout << "MAKE MELD: Please input the position of the cards you want to meld. Please input 3 comma seperated unique positions." << std::endl;
		std::cout << "Card position starts at 1 and ends at " << cardRange << std::endl;
		std::cout << "That or say 0 to cancel this phase." << std::endl;
		getline(std::cin, input);


		if (input == "0")
			break;

		std::vector<std::string> outcome;

		//Gets rid of whitespace from the whole string
		input.erase(std::remove_if(input.begin(), input.end(), ::isspace), input.end());
		std::stringstream  ss(input);
		std::string str;


		while (getline(ss, str, ',')) {

			outcome.push_back(str);

		}

		if (outcome.size() != 3) {

			std::cout << "You either have too many or too little positions. Please put only 3 positions" << std::endl;

		}

		outcome.erase(std::unique(outcome.begin(), outcome.end()), outcome.end());

		if (outcome.size() != 3) {

			std::cout << "No duplicates exist. Please enter special positions." << std::endl;

		}

		for (int inputPosition = 0; inputPosition < outcome.size(); inputPosition++) {

			std::string possibleCardPosition = outcome.at(inputPosition);

			//See if every position is alphanumeric
			if (!(std::all_of(possibleCardPosition.begin(), possibleCardPosition.end(), ::isdigit))) {

				std::cout << "Position is not numeric. Please enter a numeric position." << std::endl;

			}


			else {

				//Converting a string to an int 
				int comparePosition = stoi(possibleCardPosition);

				if (comparePosition >= 1 && comparePosition <= cardRange) {

					cardsToMeld.push_back(handOfPlayer.getCardFromHand(comparePosition - 1));

				}

				else {

					std::cout << "Position is not within range 1 to " << comparePosition << "!" << std::endl;
					break;

				}

			}

			ss.str("");

		}

		if (cardsToMeld.size() == 3)
			validInput = true;

		else
			cardsToMeld.clear();


	} while (validInput == false);

	return cardsToMeld;

}
 
/* *********************************************************************
Function Name: strategyDraw
Purpose: The drawing strategy for the Human player.
Parameters:
			useDecks -> Deck object representing the two decks to be used for drawing
Return Value: void
Algorithm:
			1. Check if a card is able to be melded or is able to be melded with melds and if the discard pile
			   is not frozen and if the player does not have a Canasta or if the player has a Canasta but needs to
			   make their hand smaller. If so, print a message to the console suggesting that the player should should
			   draw from the discard pile, draw a card from the discard pile, add the card to the player's hand, and
			   destroy any red threes in the player's hand.
			2. If the above condition is not met, check if the stock pile is not empty. If it's not, suggest
			   that the player should draw from the stock pile, draw a card from the stock pile, add it to player's hand
			   and destroy any red threes in the player's hand. 
			3. Repeat drawing cards until the drawn card is not a red three or the stock pile is empty. Have
			   another message output  about why the player should draw from the stock pile based on whether the
			   the discard pile is frozenor if the player can meld with the top of the dicard pile or if the
			   player should keep a small hand.
			4. If the stock pile is empty, print a message to the console saying 
			   that the stock pile is empty and the round will end.
Assistance Received: None
********************************************************************* */
void Human::strategyDraw(Deck& useDecks) {

	Hand handOfPlayer = getHandOfPlayer();
	Card discardTop = useDecks.getDiscardTop();
	bool ableToMeld = handOfPlayer.canMeld(discardTop);
	bool ableToMeldWithMelds = handOfPlayer.canMeldWithMelds(discardTop);
	bool handNotSmall = (((int)handOfPlayer.getHandSize() > 5));

	if (((ableToMeld || ableToMeldWithMelds) && ((!hasACanasta() || ((hasACanasta()) && (handNotSmall))))
		&& (!useDecks.getFrozenDiscard()))) {

		std::cout << "You should draw from the discard pile: can meld with hand or add onto melds"
			<< " and you don't have a Canasta, or you do have a Canasta but need to destroy your hand more." << std::endl;

		std::vector<Card> discardPickUp = useDecks.discardDraw();
		addToHand(discardPickUp);
		destroyRedThrees();
		return;

	}

	else if (!useDecks.emptyStock()) {
		std::cout << "You should draw from the stock pile, because: ";

		Card drawnCard;

		do {
			drawnCard = useDecks.stockDraw();
			addToHand(drawnCard);
			destroyRedThrees();

		} while (drawnCard.isRedThrees() && !useDecks.emptyStock());


		if (useDecks.getFrozenDiscard())
			std::cout << "the discard pile is frozen." << std::endl;

		else if (!ableToMeld)
			std::cout << "There are no cards in the your hand that can meld with the card " << discardTop.getCardStr() << std::endl;

		else {
			std::cout << "You should keep a small hand, especially for attempting to go out." << std::endl;
		}

		return;
	}

	else {

		std::cout << "The stock pile is empty, so you can't do much but let the round end." << std::endl;
		return;

	}
}

/* *********************************************************************
Function Name: strategyMeld
Purpose: The melding strategy for the Human player.
Parameters:
			useDecks -> Deck object representing the two decks to be used for drawing
			opponentMelds -> the melds of the opponent player
Return Value: void
Algorithm:
			1. Check if the critical card amount is greater than zero. If it is, output a message suggesting that
			   the player should play more carefully because one of their cards will give the opponent a Canasta.
			2. Check if the player has a Canasta and the hand size is less than six. If so, loop through each 
			   meld and check if the meld is less than seven or greater than seven. If it does, transfer the wild card
			   to the hand from the meld.
			3. Loop through each card for no duplicates, and check if the card is not wild or special. If so, 
			   add it to a vector of unique faces.
			4. Loop through each card for unique faces, and check if the card has a natural meld. If it does, add it to
			   a vector of natural melds. If not, check if the card can meld with wild card. If it can, add it to a vector
			   of cards meldable with wild cards.
			5. Check if the vector of natural cards has a size greater than or equal to three and meld the cards. If
			   not, check if the cards meldable with wild cards has a size greater than or equal to three and meld the cards.
			6. Check if the player has a canasta and the hand size is less than 6. If so, loop through each 
			   meld and check if the meld is less than 7 or greater than 7. If so, transfer the 
			   wild card to hand from the meld.
Assistance Received: None
********************************************************************* */
void Human::strategyMeld(Deck& useDecks, std::vector<std::vector<Card>> opponentMelds) {

	Hand handOfPlayer = getHandOfPlayer();
	std::vector<Card> handContainer = handOfPlayer.getHandContainer();
	std::vector<std::vector<Card>> meldContainer = handOfPlayer.getMeld();
	std::vector<Card> noDuplicates;
	std::vector<Card> uniqueFaces;
	std::vector<Card> naturalMeldVector;
	std::vector<Card> meldableWithWild;
	std::vector<Card> wildCardsInHand = handOfPlayer.getWildCardsFromHand();
	int handTransfer = -2;
	int critcalCardAmount = getCriticalCards(opponentMelds);

	if (critcalCardAmount > 0) {

		std::cout << "If discarded, one of your cards will give the enemy a Canasta, so the following help will be more careful." << std::endl;

	}

	//Removing duplicate cards
	bool actionDone = false;
	std::unique_copy(handContainer.begin(), handContainer.end(), std::back_inserter(noDuplicates));

	if ((hasACanasta() && handContainer.size() < 6)) {

		for (int meldPosition = 0; meldPosition < meldContainer.size(); meldPosition++) {

			if ((meldContainer.at(meldPosition).size() < 7 && meldContainer.at(meldPosition).size() > 3) || meldContainer.at(meldPosition).size() > 7) {

				std::vector<Card> wildTransferMeld = handOfPlayer.getWildCards(meldPosition);

				for (int wildPosition = 0; wildPosition < wildTransferMeld.size(); wildPosition++) {

					if (handOfPlayer.canMeld(wildTransferMeld.at(wildPosition))) {

						std::cout << "You should transfer the wild card " <<
						wildTransferMeld.at(wildPosition).getCardStr() << " to the hand from meld " << wildPosition << ": ";
						outputMeld(wildPosition);
						std::cout << "since you should be quick as to remove all the cards in your hand." << std::endl;
						actionDone = true;

					}

				}

			}

		}

	}

	handOfPlayer = getHandOfPlayer();
	wildCardsInHand = handOfPlayer.getWildCardsFromHand();

	//Ensure we represent each card of one face, which means no wild cards or special cards
	for (int cardPosition = 0; cardPosition < noDuplicates.size(); cardPosition++) {

		Card cardExtract = noDuplicates.at(cardPosition);

		if ((!cardExtract.isWild() && !cardExtract.isSpecial())) {

			bool isUnique = true;

			for (int uniqueCardPosition = 0; uniqueCardPosition < uniqueFaces.size(); uniqueCardPosition++) {

				if (cardExtract.getFace() == uniqueFaces.at(uniqueCardPosition).getFace())
					isUnique = false;

			}

			if (isUnique)
				uniqueFaces.push_back(handContainer.at(cardPosition));

		}

	}

	//Look at the hand for each unique face. Tally up the natural card total
	//with the same rank. If it is 3 or higher, it will meld. If more than 4, it will lay off the rest.
	for (int cardPosition = 0; cardPosition < uniqueFaces.size(); cardPosition++) {

		char faceToLook = uniqueFaces.at(cardPosition).getFace();
		handOfPlayer = getHandOfPlayer();
		handContainer = handOfPlayer.getHandContainer();
		meldContainer = handOfPlayer.getMeld();

		for (int handCPosition = 0; handCPosition< handContainer.size(); handCPosition++) {

			Card cardFromHand = handContainer.at(handCPosition);
			char faceExtract = cardFromHand.getFace();

			if (faceExtract == faceToLook && (!cardFromHand.isWild() && !cardFromHand.isSpecial())) {

				naturalMeldVector.push_back(cardFromHand);

			}

		}

		bool meldExistsAlready = false;

		if (naturalMeldVector.size() > 0) {

	    meldExistsAlready = existingMeld(naturalMeldVector.at(0));

		}

		else {

			meldExistsAlready = false;

		}

		 
		if (naturalMeldVector.size() >= 3 && !meldExistsAlready &&
			((int)handContainer.size() - critcalCardAmount > 0) &&
			!isACriticalCard(naturalMeldVector.at(0), opponentMelds)) {

			Card cardOne = naturalMeldVector.at(0);
			Card cardTwo= naturalMeldVector.at(1);
			Card cardThree = naturalMeldVector.at(2);
			handOfPlayer = getHandOfPlayer();

			 
			for (int layOffPosition = 3; layOffPosition < (int)naturalMeldVector.size() - critcalCardAmount; layOffPosition++) {

				actionDone = true;

			}

			std::cout << "Meld the following cards: ";
			outputVector(naturalMeldVector);
			std::cout << " since it is an natural meld, getting rid of natural cards is generally beneficial." << std::endl;

		}

		else if (naturalMeldVector.size() == 2 && !meldExistsAlready) {

			Card cardOne = naturalMeldVector.at(0);
			Card cardTwo = naturalMeldVector.at(1);

			meldableWithWild.push_back(cardOne);
			meldableWithWild.push_back(cardTwo);

		}

		else if (meldExistsAlready) {

			for (int meldPosition = 0; meldPosition< meldContainer.size(); meldPosition++) {

				if (naturalMeldVector.at(0).getFace() == meldContainer.at(meldPosition).at(0).getFace()) {

					int sizeOfLoop;

					if (isACriticalCard(naturalMeldVector.at(0), opponentMelds))
						sizeOfLoop = (int)naturalMeldVector.size();

					else
						sizeOfLoop = (int)naturalMeldVector.size() - critcalCardAmount;

					for (int layOffPosition = 0; layOffPosition < sizeOfLoop; layOffPosition++) {

						actionDone = true;

						std::cout << "Lay off the following card(s): ";
						outputVector(naturalMeldVector);
						std::cout << "They are all natural cards, and getting rid of natural cards is generally beneficial." << std::endl;
					}

				}

			}

		}

		naturalMeldVector.clear();

	}

	std::sort(meldableWithWild.begin(), meldableWithWild.end(),
		[](const Card& lhs, const Card& rhs) -> bool { return lhs > rhs; });


	int sizeEmulate = (int)wildCardsInHand.size();

	while (meldableWithWild.size() != 0 && sizeEmulate - critcalCardAmount > 0) {

		int cardPosition = 0;
		int cardTwoPosition = 1;
		int wildPosition = 0;

		Card firstNaturalCard= meldableWithWild.at(cardPosition);
		Card secondNaturalCard = meldableWithWild.at(cardTwoPosition);
		Card thirdWildCard = wildCardsInHand.at(wildPosition);
		std::cout << "Meld the following: ";
		outputVector(std::vector < Card >{firstNaturalCard, secondNaturalCard,thirdWildCard});
		std::cout << " as the two natural cards(ordered in highest order of points) can meld with a wild card. " << std::endl;

		sizeEmulate--;
		actionDone = true;

		//Delete the pair at the beginning of the vector
		meldableWithWild.erase(meldableWithWild.begin() + cardPosition);
		meldableWithWild.erase(meldableWithWild.begin() + cardPosition);
		handOfPlayer = getHandOfPlayer();
		wildCardsInHand = handOfPlayer.getWildCardsFromHand();

	}

	handOfPlayer = getHandOfPlayer();
	wildCardsInHand = handOfPlayer.getWildCardsFromHand();
	meldContainer = handOfPlayer.getMeld();
	meldSort(meldContainer);
	handOfPlayer= getHandOfPlayer();
	wildCardsInHand = handOfPlayer.getWildCardsFromHand();
	meldContainer = handOfPlayer.getMeld();
	meldSort(meldContainer);

	int wildCardInHandEmulate = (int)wildCardsInHand.size();

	for (int meldPosition = 0; meldPosition < meldContainer.size(); meldPosition++) {

		std::vector<Card> wildCardsFromMeld = handOfPlayer.getWildCardsWithoutTransferring(meldPosition);
		int wildCardEmulateSize = (int)wildCardsFromMeld.size();
		if (meldContainer.at(meldPosition).size() >= 3 && wildCardEmulateSize <= 3) {

			 
			while ((wildCardInHandEmulate - critcalCardAmount > 0) && (wildCardEmulateSize < 3)) {

				int absoluteMeldPosition = getMeldPosition(meldContainer.at(meldPosition));
				actionDone = true;
				 
				std::cout << "Lay off the card " << wildCardsInHand.at(0).getCardStr() << " because the meld chosen: ";
				outputVector(meldContainer.at(absoluteMeldPosition));
				std::cout << " has the highest size and less than 3 wild cards, so you ought to prioritize it." << std::endl;
				wildCardsInHand.erase(wildCardsInHand.begin());
				wildCardInHandEmulate--;
				wildCardEmulateSize++;
				wildCardsFromMeld = handOfPlayer.getWildCardsWithoutTransferring(meldPosition);

			}

		}

	}

	handOfPlayer = getHandOfPlayer();
	meldContainer = handOfPlayer.getMeld();

	for (int meldPosition = 0; meldPosition < meldContainer.size(); meldPosition++) {

		std::vector<Card> meld = meldContainer.at(meldPosition);
		int meldableToCanastaSum = meld.size() + 3 - (int)getVectorWildCards(meld).size();
		int minimumForCanasta = 7;
		handOfPlayer = getHandOfPlayer();
		meldContainer = handOfPlayer.getMeld();

		if (meldableToCanastaSum >= minimumForCanasta && meld.size() < 7 && !hasACanasta()) {

			int otherMeldsPosition = (meldPosition == meldContainer.size() - 1) ? 0 : meldPosition + 1;

			while (otherMeldsPosition != meldPosition) {

				handOfPlayer = getHandOfPlayer();
				meldContainer = handOfPlayer.getMeld();
				std::vector<Card> meldToWildExtract = meldContainer.at(otherMeldsPosition);

				if (meldToWildExtract.size() > 3) {

					std::vector<Card> wildToTransfer = handOfPlayer.getWildCards(otherMeldsPosition);

					while (wildToTransfer.size() != 0) {

						actionDone = true;
						std::cout << "Transfer the  card " << wildToTransfer.at(0).getCardStr() << "from meld: ";  outputMeld(otherMeldsPosition); std::cout << std::endl;
						std::cout << "As meld: "; outputMeld(meldPosition);
						std::cout << "can be made as a Canasta with just a few more wild cards." << std::endl;
						wildToTransfer.erase(wildToTransfer.begin());

					}

				}

				handOfPlayer= getHandOfPlayer();
				meldContainer = handOfPlayer.getMeld();

				if (otherMeldsPosition == meldContainer.size() - 1)
					otherMeldsPosition = 0;

				else
					otherMeldsPosition++;

			}

		}

	}

	if (!actionDone && critcalCardAmount == 0) {

		std::cout << "Nothing to meld, lay off, or transfer here. Do nothing." << std::endl;

	}

	else if (critcalCardAmount > 0 && !actionDone) {

		std::cout << "Do nothing, as otherwise the opponent gets a Canasta." << std::endl;

	}

	handSort();
}

/* *********************************************************************
Function Name: strategyDiscard
Purpose: The discarding strategy for the Human player.
Parameters:
			useDecks -> Deck object representing the two decks used for discarding
			opponentMelds -> a vector of vector of Cards representing the melds of the opponent
Return Value: void 
Algorithm:
			1. Initialize some variables for storing cards and the player's hand.
			2. Sort the player's hand.
			3. Check for cards that are not in the opponent's melds.
			4. If a card is not in the melds of the opponent but is a wild card, add it to 
			   vector for that.
			5. If a card is not a wild card, add it to a vector for no wild cards in discard.
			6. Check if the top card of the discard pile is in the opponent's melds.
			7. If the top card is in the opponent's melds and the player has a 3 of spades or 3 of clubs, discard
			   the 3 card and break the loop.
			8. If the vector for regular discarding, the vector for cards not in meld or wild, and the vector for no wild
			   cards in discard is not empty and a 3 card was not discarded, discard
			   the first card in the respective vector.
			9. If none of the above conditions are met and a 3 card was not discarded, discard the top card of the player's hand.
		   10. Remove the discarded card from the player's hand.
Assistance Received: None
********************************************************************* */
void Human::strategyDiscard(Deck& useDecks, std::vector<std::vector<Card>> opponentMelds) {

	std::vector<Card> preferDiscard;
	std::vector<Card> notInMeldButWild;
	std::vector<Card> noWildDiscard;
	Hand handOfPlayer = getHandOfPlayer();
	handOfPlayer.sort();
	std::vector<Card> handContainer = handOfPlayer.getHandContainer();
	Card preferCard;
	int cardOnePosition = 0;
	auto itreThreeSpades = std::find(handContainer.begin(), handContainer.end(), Card("3S"));
	auto itrThreeClubs = std::find(handContainer.begin(), handContainer.end(), Card("3C"));

	for (int cardPosition = 0; cardPosition < handContainer.size(); cardPosition++) {

		Card cardToLook = handContainer.at(cardPosition);
		bool considerAdding = true;

		for (int meldPosition= 0; meldPosition < opponentMelds.size(); meldPosition++) {
			 
			//Checking for first card
			if (cardToLook.getFace() == opponentMelds.at(meldPosition).at(0).getFace()) {

				considerAdding= false;

			}

		}

		if (considerAdding == true) {

			if (!cardToLook.isWild() && !cardToLook.isSpecial())
				preferDiscard.push_back(cardToLook);

			else {

				notInMeldButWild.push_back(cardToLook);

			}

		}

		if (!cardToLook.isWild()) {

			noWildDiscard.push_back(cardToLook);

		}

	}

	Card discardTop = useDecks.getDiscardTop(); //remember this
	bool didThreeDiscard = false;

	for (int meldPosition = 0; meldPosition < opponentMelds.size(); meldPosition++) {

		if (discardTop.getFace() == opponentMelds.at(meldPosition).at(cardOnePosition).getFace()) {

			if (itreThreeSpades != handContainer.end()) {

				preferCard = *itreThreeSpades;
				useDecks.discardPushFront(*itreThreeSpades);
				handRemoval(*itreThreeSpades);

				std::cout << "You should choose to get rid of 3S since the top of the discard, "
					<< discardTop.getCardStr() << " is in the opponent meld: "; outputMeld(meldPosition);
				std::cout << std::endl;

				didThreeDiscard = true;
				break;

			}

			else if (itrThreeClubs != handContainer.end()) {

				preferCard = *itrThreeClubs;
				useDecks.discardPushFront(*itrThreeClubs);
				handRemoval(*itrThreeClubs);

				std::cout << "You should choose to get rid of 3C since the top of the discard, "
					<< discardTop.getCardStr() << " is in the opponent meld: "; outputMeld(meldPosition);
				std::cout << std::endl;

				didThreeDiscard = true;
				break;

			}

		}

	}

	if (preferDiscard.size() != 0 && !didThreeDiscard) {

		preferCard = preferDiscard.at(0);

		std::cout << "I suggest to throw away: " << preferCard.getCardStr() << " since it's the lowest value  " <<
			"in your hand, with " << preferCard.getPointVal() << " points, and is not in opponent's melds." << std::endl;

	}

	else if (notInMeldButWild.size() != 0 && !didThreeDiscard) {

		preferCard = notInMeldButWild.at(0);
		std::cout << "I suggest to throw away: " << preferCard.getCardStr() << " since it's the lowest value  " <<
			"in your hand, with " << preferCard.getPointVal() << " points, and wasn't in opponent meld." << std::endl;

	}

	else if (noWildDiscard.size() != 0 && !didThreeDiscard) {

		preferCard= noWildDiscard.at(0);

		std::cout << "I suggest to throw away: " << preferCard.getCardStr() << " since it's the lowest value  " <<
			"in your hand, with " << preferCard.getPointVal() << " points, and wasn't a wild card." << std::endl;


	}
	 
	else if (handContainer.size() != 0 && !didThreeDiscard) {

		preferCard = handContainer.at(0);
		std::cout << "You don't really have a choice, so throw away your lowest value card, which is " << preferCard.getCardStr() << std::endl;

	}
	else if (!didThreeDiscard) {

		std::cout << "You can't discard anything, I can't advise what to discard here. " << std::endl;
		return;

	}

	if (preferCard.isWild() || preferCard.isSpecial()) {

		useDecks.setFrozenDiscard(true);

	}

	else {

		useDecks.setFrozenDiscard(false);

	}

	useDecks.discardPushFront(preferCard);
	handRemoval(preferCard);

}