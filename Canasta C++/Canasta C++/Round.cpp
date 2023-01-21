#include "Round.h"
#include <filesystem>

/* *********************************************************************
Function Name: Round()
Purpose: Default constructor for Round class.
Parameters: None
Return Value: None
Assistance Received: None
********************************************************************* */
Round::Round() {

	nextPlayer = 0;
	roundNum = 0;

}

/* *********************************************************************
Function Name: ~Round()
Purpose: Default destructor for Round class.
Parameters: None
Return Value: None
Assistance Received: None
********************************************************************* */
Round::~Round() {

	stockAndDiscard.deleteDiscard();

}

/* *********************************************************************
Function Name: Round
Purpose:  Default constructor for Round class.
Parameters:
			 p1 -> Human object that represents the first Human player
			 p2 -> Human object that represents the second Human player
Return Value: None
Algorithm:
			1. Add the address of p1 and p2 to the players vector.
Assistance Received: None
********************************************************************* */
Round::Round(Human p1, Human p2) {

	players.push_back(&p1);
	players.push_back(&p2);
	nextPlayer = 0;
	roundNum = 0;

}

/* *********************************************************************
Function Name: Round
Purpose: Default constructor of Round class.
Parameters:
			 p1 -> Human object that represents the first Human player
			 p2 -> Computer object that represents the Computer player
Return Value: None
Algorithm:
			1. Add the address of p1 and p2 to the players vector .
Assistance Received: None
********************************************************************* */
Round::Round(Human p1, Computer p2) {

	players.push_back(&p1);
	players.push_back(&p2);
	nextPlayer = 0;
	roundNum = 0;

}

/* *********************************************************************
Function Name: Round
Purpose: Default constructor for Round class.
Parameters:
			players -> a vector of Player that represents the two players in the game
			roundNum -> int that represents the round number
Return Value: None
Assistance Received: None
********************************************************************* */
Round::Round(std::vector<Player*> players, int roundNum) {

	this->players = players;
	this->roundNum = roundNum;
	nextPlayer = 0;

}

/* *********************************************************************
Function Name: Round
Purpose: Default constructor for Round class.
Parameters:
			anotherRound -> Round object that represents each round played of Canasta
Return Value: None
Assistance Received: None
********************************************************************* */
Round::Round(const Round& anotherRound) {

	this->nextPlayer = anotherRound.nextPlayer;
	this->stockAndDiscard = anotherRound.stockAndDiscard;
	this->players = anotherRound.players;

}

/* *********************************************************************
Function Name: coinFlip()
Purpose: Does the coin flip at the beginning of the game.
Parameters: None
Return Value: int representing which player goes first
Algorithm:
			1. Initialize a variable with a random integer value between 1 and 2 using std::random_device and std::uniform_int_distribution.
			2. Display a message asking the second player to choose between heads or tails, 
			   and provide them with options to input 1 for heads or 2 for tails.
            3. Read the player's input and store it in a variable pick.
            4. If pick is equal to variable's result, display a message indicating that the first player will go first 
			   and that they correctly guessed the coin toss. Return 2.
			5. Otherwise, display a message indicating that the second player will go first and that they correctly guessed the coin toss. Return 1.
Assistance Received: None
********************************************************************* */
int Round::coinFlip() {

	auto time1 = std::chrono::system_clock::now().time_since_epoch().count();
	std::random_device device;
	std::uniform_int_distribution<std::mt19937::result_type> coin(1, 2);
	auto tossedCoin = coin(device);

	std::cout << "Player 2, choose between Heads or Tails." << std::endl;
	std::cout << "1. Heads" << std::endl;
	std::cout << "2. Tails" << std::endl;
	int pick = checkUserInput(1, 2);

	if (pick == tossedCoin) {

		std::cout << "Player 1 will go first. They correctly guessed " << ((tossedCoin == 1) ? "Heads" : "Tails") << std::endl;
		return 2;

	}

	else {

		std::cout << "Player 2 will go first. They correctly guessed " << ((tossedCoin == 1) ? "Heads" : "Tails") << std::endl;
		return 1;

	}

}

/* *********************************************************************
Function Name: mainRound
Purpose: Sets up the round by displaying all the information.
Parameters:
			hasFileLoad -> bool representing if a file has loaded or not
Return Value: bool
Algorithm:
		 1. Initialize variables for the two players (p1 and p2), a menu pick variable, and a round over flag.
		 2. If the round is not being loaded from a saved file:
			1. If the scores of p1 and p2 are equal, use the coinFlip function to determine the order of play.
			2. Otherwise, set the order of play based on the scores of p1 and p2.
			3. Perform the initial draw and sort the hands of the players.
		3. Print the round information.
		4. Do the following:
			1. Do the following: 
				 1. Display the pre-turn menu and get the player's choice.
				 2. If the choice is to save the game:
					 1. Prompt the player to choose whether to save and continue or save and quit.
					 2. Save the game using the saveRound function.
					 3. If the player chose to save and quit, return true.
				 3. If the choice is to continue, go to the next iteration of the loop.
				 4. If the choice is to quit the game, return true.
				 5. If the choice is to get strategy advice, call the playerStrategy function for the current player and pass it the stock and discard piles and the opponent's melds.
			2. Print the round information.
		    3. If the round is over, break out of the loop.
			4. If it is player 1's turn:
				1. Print the round information.
				2. Get the opponent's hand and melds.
				3. Set the round over flag to the result of calling the play function for player 1 and passing it the stock and discard piles and the opponent's melds.
				4. Clear any "transferred" cards in player 1's hand.
				5. Set the next player.
			5. Otherwise, do the same thing for the other player's turn.
		5. Tally the points, print the round information and return false. 
Assistance Received: None
********************************************************************* */
bool Round::mainRound(bool hasFileLoad) {

	auto p1 = players.at(0);
	auto p2 = players.at(1);
	int menuPick = 0; 
	bool roundOver = false;

	if (hasFileLoad == false) {

		if (p1->getScore() == p2->getScore()) {
			
			//Coin flip will decide who goes first
			setNextPlayer(coinFlip());

		}

		else {

			if (p1->getScore() > p2->getScore())
				nextPlayer = 1;

			else
				nextPlayer = 2;

		}

		initialDraw();
		playerHandSort();

	}

	printRoundInfo();

	do {

		do {

			menuPick = preTurnMenu();

			switch (menuPick) {

			case 1: {
				std::cout << "How would you like to save?" << std::endl;
				std::cout << "1. Save and Continue" << std::endl;
				std::cout << "2. Save and Quit" << std::endl;
				int savePick = checkUserInput(1, 2);
				playerHandSort();
				saveRound();

				if (savePick == 2)
					return true;

				break;

			}

			case 2:
				continue;
				break;

			case 3:
				return true;
				break;

			case 4: {
				auto playerToGiveHelpPosition= getNextPlayer() - 1;
				auto playerToGiveHelp = players.at(playerToGiveHelpPosition);
				auto opponentPlayer = (playerToGiveHelp == 0) ? players.at(1) : players.at(0);
				Hand opponentHand = opponentPlayer->getHandOfPlayer();
				std::vector<std::vector<Card>> opponentMeld = opponentHand.getMeld();

				playerToGiveHelp->playerStrategy(stockAndDiscard, opponentMeld);

				break;

			}

			}

			//If option is quit game or take a turn, break
		} while (menuPick != 3 && menuPick != 2);

		printRoundInfo();

		if (roundOver == true) break;


		if (nextPlayer == 1) {

			printRoundInfo();
			Hand opponentHand = p2->getHandOfPlayer();
			std::vector<std::vector<Card>> opponentMeld = opponentHand.getMeld();
			roundOver = p1->play(stockAndDiscard, opponentMeld);
			p1->deleteTransfer();
			nextPlayer++;
		}


		else {

			Hand opponentHand = p1->getHandOfPlayer();
			std::vector<std::vector<Card>> opponentMeld = opponentHand.getMeld();
			roundOver = p2->play(stockAndDiscard, opponentMeld);
			p2->deleteTransfer();
			nextPlayer--;

		}

		printRoundInfo();

	} while (roundOver == false && menuPick != 4);

	scoreTally();
	printRoundInfo();
	return false;

}

/* *********************************************************************
Function Name: initialDraw()
Purpose: Does the initial drawing during the DRAW PHASE.
Parameters: None
Return Value: void
Algorithm:
			1. Initialize a variable initialDrawCounter to 15. This variable will be used to 
			   keep track of the number of cards that need to be drawn from the stock pile.
			2. Use a for loop to iterate over the players in the players vector.
			3. Inside the for loop, use another for loop to iterate initialDrawCounter times. 
			   This inner loop will be used to draw cards from the stock pile and give them to the current player.
		    4. Inside the inner loop, call the stockDraw() function on the stockAndDiscard object 
			   to draw a card from the stock pile.
			5. Convert the card object to a string and store it in a variable strDrawn.
			6. Check if strDrawn is equal to "3H" or "3D". 
			   If it is, then output a message saying that the player has drawn a red three on the initial draw 
			   and add the card to the player's unique meld using the makeUniqueMeld() function. 
			   Decrement the value of initialDrawCounter to account for the card that was drawn but not added to the player's hand.
			7. If strDrawn is not equal to "3H" or "3D", then add the card to the player's hand using the addToHand() function.
            8. After the inner loop has completed, move on to the next player.
            9. When the outer loop has completed, the initial draw is finished and all players should have 15 cards in their hands.
Assistance Received: None
********************************************************************* */
void Round::initialDraw() {

	//Drawing 15 cards from the stock pile
	int initialDrawCounter = 15;

	for (int cardCounter = 0; cardCounter < players.size(); cardCounter++) {

		for (int card = 0; card < initialDrawCounter; card++) {

			Card cardDrawn = stockAndDiscard.stockDraw();
			std::string strDrawn = cardDrawn.getCardStr();

			if (strDrawn == "3H" || strDrawn == "3D") {

				std::cout << "Player " << cardCounter + 1 << ", you got a red three on initial draw!" << std::endl;
				players.at(cardCounter)->makeUniqueMeld(cardDrawn);
				card--;

			}

			else {

				players.at(cardCounter)->addToHand(cardDrawn);

			}

		}

	}

}

/* *********************************************************************
Function Name: preTurnMenu()
Purpose: Displays a menu before each player takes their respective turn.
Parameters: None
Return Value: checkUserInput -> int that validates the choice made by the user
Algorithm:
			1. Declare an integer variable nextPlayer and initialize it with 
			   the value of the current player's position in the players vector.
			2. Declare a string variable nextTypeOfPlayer and initialize it with the value of 
			   the current player's type of player.
			3. If nextTypeOfPlayer is "Human":
				1. Print the menu options to the console.
				2. Return the user's input after checking that it is a valid menu option.
			4. Else if nextTypeOfPlayer is "Computer":
				1. Print the menu options to the console, excluding the "Ask for help" option.
			    2. Return the user's input after checking that it is a valid menu option.
			5. Else:
			   1. Print an error message to the console.
Assistance Received: None
********************************************************************* */
int Round::preTurnMenu() {

	int nextPlayer = getNextPlayer() - 1;
	std::string nextTypeOfPlayer = players.at(nextPlayer)->getTypeOfPlayer();

	if (nextTypeOfPlayer == "Human") {

		std::cout << "1. Save game" << std::endl;
		std::cout << "2. Take turn" << std::endl;
		std::cout << "3. Quit game" << std::endl;
		std::cout << "4. Ask for help" << std::endl;
		return checkUserInput(1, 4);

	}

	else if (nextTypeOfPlayer == "Computer") {

		std::cout << "1. Save game" << std::endl;
		std::cout << "2. Take turn" << std::endl;
		std::cout << "3. Quit game" << std::endl;
		return checkUserInput(1, 4);

	}

	else {

		std::cout << "Error: Unknown type of player." << std::endl;
		return -999;

	}

}

/* *********************************************************************
Function Name: scoreTally()
Purpose: Tallies the scores of both players.
Parameters: None
Return Value: void
Algorithm:
			1. Initialize two variables p1Score and p2Score to the respective scores 
			   of player 1 and player 2 obtained from their hands.
			2. If player 1 has decided to go out, add 100 to p1Score.
			3. If player 2 has decided to go out, add 100 to p2Score.
			4. Print out the scores of player 1 and player 2 with their respective player types.
		    5. Add the scores of player 1 and player 2 to their respective scores.
Assistance Received: None
********************************************************************* */
void Round::scoreTally() {

	int p1Score = players.at(0)->getHandOfPlayer().getTotalScore();
	int p2Score = players.at(1)->getHandOfPlayer().getTotalScore();

	if (players.at(0)->getGoOutChoice() == true) {

		p1Score += 100;

	}

	else if (players.at(1)->getGoOutChoice() == true) {

		p2Score += 100;

	}

	std::cout << "Player 1 (" << players.at(0)->getTypeOfPlayer() << ") " << " round score: " << p1Score << std::endl;
	std::cout << "Player 2 (" << players.at(1)->getTypeOfPlayer() << ") " << " round score: " << p2Score << std::endl;

	players.at(0)->scoreAdd(p1Score);
	players.at(1)->scoreAdd(p2Score);

}

/* *********************************************************************
Function Name: getNextPlayer()
Purpose: Selector for the nextPlayer variable.
Parameters: None
Return Value: nextPlayer -> int representing the next player to go up
Assistance Received: None
********************************************************************* */
int Round::getNextPlayer() const {

	return nextPlayer;

}

/* *********************************************************************
Function Name: getPlayers()
Purpose: Selector for the players variable.
Parameters: None
Return Value: players -> a vector of Players representing the two players of the game
Assistance Received: None
********************************************************************* */
std::vector<Player*> Round::getPlayers() {

	return players;

}

/* *********************************************************************
Function Name: setNextPlayer
Purpose: Mutator for the nextPlayer variable. 
Parameters:
			nextPlayer -> int representing the next player to go up
Return Value: void
Assistance Received: None
********************************************************************* */
void Round::setNextPlayer(int nextPlayer) {

	this->nextPlayer = nextPlayer;

}

/* *********************************************************************
Function Name: setStock
Purpose: Mutator for the stockPile variable.
Parameters:
			stockPile -> a vector of Cards that represents the stock pile
Return Value: void
Assistance Received: None
********************************************************************* */
void Round::setStock(std::vector<Card> stockPile) {

	stockAndDiscard.setStock(stockPile);

}

/* *********************************************************************
Function Name: setDiscard
Purpose: Mutator for the discardPile variable
Parameters:
			discardPile -> a vector of Cards representing the discard pile
Return Value: void
Assistance Received: None
********************************************************************* */
void Round::setDiscard(std::vector<Card> discardPile) {

	stockAndDiscard.setDiscard(discardPile);

}

/* *********************************************************************
Function Name: setRoundNum
Purpose: Mutator for the roundNum variable.
Parameters:
			roundNum -> int that represents the round number
Return Value: void
Assistance Received: None
********************************************************************* */
void Round::setRoundNum(int roundNum) {

	this->roundNum = roundNum;

}

/* *********************************************************************
Function Name: loadGame()
Purpose: Loads a game of Canasta.
Parameters: None
Return Value: loadComplete -> bool representing a game of Canasta has fully loaded
Algorithm:
			1. Prompt the user to input the name of the file they want to load and store the input in a string.
			2. Check if the input is "0". If it is, return false.
			3. Check if the file with the specified name exists. If it doesn't, output an error message and return false.
			4. Read each line of the file and store them in a vector of strings.
			5. Check if the size of the vector of strings is 12. If it is not, output an error message and return false.
			6. Iterate through the vector of strings and perform the appropriate action for each element based on its position in the vector.
			7. Close the file and print the round information.

Assistance Received: None
********************************************************************* */
bool Round::loadGame() {

	std::cout << "Input the file you want to load. Type 0 to exit." << std::endl;

	std::string enterFileName;

	if (enterFileName == "0") {

		return false;

	}

	getline(std::cin, enterFileName);

	std::ifstream fileToLoad(enterFileName);
	std::string stringExtract;
	std::vector<std::string> parseLines;

	bool loadComplete = true;

	if (std::filesystem::exists(enterFileName)) {

		while (getline(fileToLoad, stringExtract)) {

			std::istringstream ss(stringExtract);

			if (stringExtract.find(':') != std::string::npos) {

				//Removing extra spaces inside the string
				stringExtract.erase(std::unique(stringExtract.begin(), stringExtract.end(),
					[](char a, char b) { return isspace(a) && isspace(b); }), stringExtract.end());

				 
				stringExtract.erase(stringExtract.begin(), std::find_if(stringExtract.begin(), stringExtract.end(), [](unsigned char ch) {
					return !isspace(ch); //Remember this
				}));

				parseLines.push_back(stringExtract);

			}

		}

	}

	else {

		std::cout << "Specified file does not exist" << std::endl;
		return false;

	}

	if (parseLines.size() != 12) {

		std::cout << "The load file has either too little or too much information." << std::endl;
		return false;

	}

	else {

		for (int linePosition = 0; linePosition < parseLines.size(); linePosition++) {

			std::string lineParse = parseLines.at(linePosition);

			switch (linePosition) {

			case 0:
				loadComplete = loadRoundNum(lineParse);
				break;

			case 1:
				loadComplete = loadPlayer(lineParse);
				break;

			case 2:
				loadComplete = loadPlayerScore(0, lineParse);
				break;

			case 3:
				loadComplete = loadHand(0, lineParse);
				break;

			case 4:
				loadComplete = loadMeld(0, lineParse);
				break;

			case 5:
				loadComplete = loadPlayer(lineParse);
				break;

			case 6:
				loadComplete = loadPlayerScore(1, lineParse);
				break;

			case 7:
				loadComplete = loadHand(1, lineParse);
				break;

			case 8:
				loadComplete = loadMeld(1, lineParse);
				break;

			case 9:
				loadComplete = loadStock(lineParse);
				break;

			case 10:
				loadComplete = loadDiscard(lineParse);
				break;

			case 11:
				loadComplete = loadNextPlayer(lineParse);
				break;

			}

		}

	}

	fileToLoad.close();
	printRoundInfo();
	return loadComplete;

}

/* *********************************************************************
Function Name: loadRoundNum
Purpose: Loads the round number into the game.
Parameters:
			roundStr -> string representing a round of the game
Return Value: bool
Algorithm:
			1. Obtain the round number string by extracting the substring after the space character in the input roundStr string.
			2. Check if the round number string is empty. If it is, output an error message and return false.
			3. Check if all characters in the round number string are digits using the std::all_of function and the ::isdigit function from the <cctype> library. 
			   If all characters are not digits, output an error message and return false.
			4. Convert the round number string to an integer using  std::stoi.
			5. Call the setRoundNum function and pass it the converted round number integer.
			6. Return true.
Assistance Received: None
********************************************************************* */
bool Round::loadRoundNum(std::string roundStr) {

	std::string roundNumber = roundStr.substr(roundStr.find(" ") + 1);

	if (roundNumber.size() == 0) {

		std::cout << "Error: Missing round number." << std::endl;
		return false;

	}

	if (std::all_of(roundNumber.begin(), roundNumber.end(), ::isdigit)) {

		int convertedRoundNum = std::stoi(roundNumber);
		setRoundNum(convertedRoundNum);
		return true;

	}

	else {

		std::cout << "Error: Round number is not numeric." << std::endl;
		return false;

	}

}

/* *********************************************************************
Function Name: loadPlayer
Purpose: Loads the players into the game.
Parameters:
			playerStr -> string representing the players of the game
Return Value: bool
Algorithm:
			1. Check if the input string is "Human:". If it is, create a new Human object 
			   and add it to the players vector. Return true to indicate that the loading was successful.
			2. Check if the input string is "Computer:". If it is, create a new Computer object 
			   and add it to the players vector. Return true to indicate that the loading was successful.
			3. If the input string is neither "Human:" nor "Computer:", 
			   output an error message and return false to indicate that the loading was unsuccessful.
Assistance Received: None
********************************************************************* */
bool Round::loadPlayer(std::string playerStr) {

	if (playerStr == "Human:") {

		players.push_back(new Human);
		return true;

	}

	else if (playerStr == "Computer:") {

		players.push_back(new Computer);
		return true;

	}

	else {

		std::cout << "Error: Unknown type of player." << std::endl;
		return false;

	}

}

/* *********************************************************************
Function Name: loadPlayerScore
Purpose: Loads the scores of the players.
Parameters:
			player -> int that represents a player in the game
			roundStr -> string that represents a round of the game
Return Value: bool
Algorithm:
			1. Initialize an empty string called playerScore that will be used to store the player's score.
			2. Use the find method of the roundStr string to search for the first occurrence of a space character, 
			   and assign the result to a variable called spaceIndex.
			3. Use the substr method of roundStr to create a new string called playerScore 
			   that starts at the index following the space character and 
			   includes all characters up to the end of the string.
			4. Check if the size of playerScore is 0. If it is, output an error message and return false.
			5. Check if all characters in playerScore are digits using the 
			   all_of function from the algorithm library. If any of the characters are not digits, 
			   output an error message and return false.
			6. Convert the playerScore string to an integer using the stoi function 
			   and store the result in a variable called convertedPlayerScore.
			7. Use the setPlayerScore method to set the player's score to convertedPlayerScore.
			8. Return true.
Assistance Received: None
********************************************************************* */
bool Round::loadPlayerScore(int player, std::string roundStr) {

	std::string playerScore = roundStr.substr(roundStr.find(" ") + 1);

	if (playerScore.size() == 0) {

		std::cout << "Error: Missing player score." << std::endl;
		return false;

	}

	if (std::all_of(playerScore.begin(), playerScore.end(), ::isdigit)) {

		int convertedPlayerScore = std::stoi(playerScore);
		players.at(player)->setPlayerScore(convertedPlayerScore);
		return true;

	}

	else {

		std::cout << "Error: Player score is not numeric." << std::endl;
		return false;

	}

}

/* *********************************************************************
Function Name: loadStock
Purpose: Loads the stock pile into the game.
Parameters:
			stockStr -> string representing the stock pile
Return Value: bool
Algorithm:
			1. Initialize an empty vector of Card objects called stockConvert.
			2. Create an input string stream extractStock and initialize it with the value of stockStr.
			3. Create a loop that continues until the end of the input string stream is reached. Inside the loop:
				1. Initialize a string variable cardStr to an empty string.
				2. Extract a string from extractStock and store it in cardStr.
				3. If cardStr is an empty string, break out of the loop.
				4. If strToCard returns true when called with cardStr as the argument:
					1. Push a new Card object with cardStr as the argument into stockConvert.
				5. Otherwise, return false.
			4. Set the current round object to stockConvert.
			5. Return true.
Assistance Received: None
********************************************************************* */
bool Round::loadStock(std::string stockStr) {

	std::string stock = stockStr.substr(stockStr.find(" ") + 1);
	std::vector<Card> stockConvert;
	std::istringstream extractStock(stock);

	do {

		std::string cardStr;
		extractStock >> cardStr;

		if (cardStr == "")
			break;

		if (strToCard(cardStr)) {

			stockConvert.push_back(Card(cardStr));

		}

		else {

			return false;

		}

	} while (extractStock);

	setStock(stockConvert);
	return true;

}

/* *********************************************************************
Function Name: loadDiscard
Purpose: Loads the discard pile into the game.
Parameters:
			discardStr -> string representing the discard pile
Return Value: bool
Algorithm:
			1. Start a loop that will continue until the end of the input string stream is reached.
			2. Within the loop, initialize an empty string called "cardStr".
			3. Use the input string stream operator (>>) to extract the 
			   next card string from "extractDiscard" and assign it to "cardStr".
			4. If "cardStr" is an empty string, break out of the loop.
			5. Call the helper function "strToCard" with "cardStr" as the input. 
			   If "strToCard" returns false, return false immediately.
			6. If "strToCard" returns true, add a new card object to the 
			   "discardConvert" vector using the constructor "Card(cardStr)".
			7. Repeat the loop starting from step 1.
			8. After the loop ends, call the function "setDiscard" with "discardConvert" as the input.
			9. Return true to indicate success.
Assistance Received: None
********************************************************************* */
bool Round::loadDiscard(std::string discardStr) {

	std::string discard = discardStr.substr(discardStr.find(" ") + 1);
	discard = discardStr.substr(discardStr.find(":") + 1);
	std::vector<Card> discardConvert;
	std::istringstream extractDiscard(discard);

	do {

		std::string cardStr;
		extractDiscard >> cardStr;

		if (cardStr == "")
			break;

		if (strToCard(cardStr)) {

			discardConvert.push_back(Card(cardStr));

		}

		else {

			return false;

		}

	} while (extractDiscard);

	setDiscard(discardConvert);
	return true;

}

/* *********************************************************************
Function Name: loadNextPlayer
Purpose: Loads the next player into the game.
Parameters:
			nextPlayerStr ->  string that represents the next player of the game
Return Value: bool
Algorithm:
			1. If "nextPlayerStr" is equal to "Player: Human", call the function 
			   "setNextPlayer" with the value 2 and return true.
			2. If "nextPlayerStr" is equal to "Player: Computer", call the 
			   function "setNextPlayer" with the value 1 and return true.
			3. If "nextPlayerStr" is not equal to either "Player: Human" or "Player: Computer",
			   print an error message and return false.
Assistance Received: None
********************************************************************* */
bool Round::loadNextPlayer(std::string nextPlayerStr) {

	nextPlayerStr = nextPlayerStr.substr(nextPlayerStr.find(" ") + 1);

	if (nextPlayerStr == "Player: Human") {

		setNextPlayer(2);
		return true;

	}

	else if (nextPlayerStr == "Player: Computer") {

		setNextPlayer(1);
		return true;

	}

	else {

		std::cout << "Error: Next player is not Human or Computer." << std::endl;
		return false;

	}

}

/* *********************************************************************
Function Name: loadHand
Purpose: Loads the player's hand into the game
Parameters:
			player -> int representing a player in the game
			handStr -> string that represents the player's hand
Return Value: bool
Algorithm:
			1. Initialize a vector handConvert to store the cards in the hand.
			2. Initialize an input string stream extractHand to read from the string hand.
			3. While there are more characters in extractHand, do the following:
				1. Read a string cardStr from extractHand.
				2. If cardStr is an empty string, break out of the loop.
				3. If strToCard returns true for cardStr, add a new card with the value of cardStr to handConvert.
				4. Otherwise, return false.
			4. Set the player's hand to handConvert using the setHand method.
			5. Return true.

Assistance Received: None
********************************************************************* */
bool Round::loadHand(int player, std::string handStr) {

	std::string hand = handStr.substr(handStr.find(" ") + 1);
	std::vector<Card> handConvert;
	std::istringstream extractHand(hand);

	do {

		std::string cardStr;
		extractHand >> cardStr;

		if (cardStr == "")
			break;

		if (strToCard(cardStr)) {

			handConvert.push_back(Card(cardStr));

		}

		else {

			return false;

		}


	} while (extractHand);

	players.at(player)->setHand(handConvert);
	return true;

}

/* *********************************************************************
Function Name: loadMeld
Purpose: Loads each player's melds into the game.
Parameters:
			player -> int representing a player in the game
			preMeldStr -> string representing the cards that are to be melded
Return Value: bool
Algorithm:
			1. Initialize an empty vector called meldConvert to store the cards in a meld and 
			   an empty vector of vectors called meldConvertContainer to store all the melds.
			2. Initialize a string meldStr to store the current meld being processed 
			   and a string cardStr to store the current card being processed.
			3. Using an input string stream, extract each meld from the preMeldStr string 
			   and store it in meldStr until the end of the string is reached.
			4. For each meldStr, remove the brackets and store the modified string 
			   in a new input string stream extractCard.
			5. Using extractCard, extract each card from the meld string and 
			   store it in cardStr until the end of the meld string is reached.
			6. If cardStr is a valid card, add it to meldConvert. If it is not a valid card, return false.
			7. When the end of the meld string is reached, add meldConvert to meldConvertContainer and clear meldConvert.
			8. Repeat steps 3 to 7 until all melds have been processed.
			9. Set the player's melds to meldConvertContainer.
			10. Return true.
Assistance Received: None
********************************************************************* */
bool Round::loadMeld(int player, std::string preMeldStr) {

	std::string melds = preMeldStr.substr(preMeldStr.find(" ") + 1);
	std::vector<Card> meldConvert;
	std::vector<std::vector<Card>> meldConvertContainer;
	std::istringstream extractMeld(melds);
	std::string cardStr;
	std::string meldStr;

	while (getline(extractMeld, meldStr, ']')) {

		if (meldStr == "" || meldStr == " ")
			break;

		meldStr.erase(std::remove(meldStr.begin(), meldStr.end(), '['), meldStr.end());
		meldStr.erase(std::remove(meldStr.begin(), meldStr.end(), ']'), meldStr.end());
		std::istringstream extractCard(meldStr);

		while (extractCard >> cardStr) {

			if (cardStr == "")
				break;

			if (strToCard(cardStr)) {

				meldConvert.push_back(Card(cardStr));

			}

			else {

				return false;

			}

		}

		meldConvertContainer.push_back(meldConvert);
		meldConvert.clear();
		extractCard.clear();
		extractMeld.clear();

	}

	players.at(player)->setMeld(meldConvertContainer);
	return true;

}

/* *********************************************************************
Function Name: playerHandSort()
Purpose: Sorts the hands of the players.
Parameters: None
Return Value: void
Algorithm:
			1. Iterate through each player in the list of players for the round.
			2. For each player, call the handSort method on the player's hand.
			3. End the loop when all players have had their hands sorted.
Assistance Received: None
********************************************************************* */
void Round::playerHandSort() {

	for (int playerPosition = 0; playerPosition < players.size(); playerPosition++)

		players.at(playerPosition)->handSort();

}

/* *********************************************************************
Function Name: printRoundInfo()
Purpose: Prints the information of the Round onto the console.
Parameters: None
Return Value: void
Algorithm:
			1. Create a variable p1 to store the first player in the players vector.
			2. Create a variable p2 to store the second player in the players vector.
			3. Create a variable p1Hand to store the hand of the first player.
			4. Create a variable p2Hand to store the hand of the second player.
			5. Print the round number.
			6. Print the type of player for p1.
			7. Print "Score: " and the score of p1.
			8. Print "Hand: " and the hand of p1.
			9. Print "Melds: " and the melds of p1.
			10.Print the type of player for p2.
			11.Print "Score: " and the score of p2.
			12.Print "Hand: " and the hand of p2.
			13.Print "Melds: " and the melds of p2.
			14.Print "Stock: " and the stock.
			15.Print "Discard Pile: " and the discard pile.
			16.Print "Next Player: " and the next player.
Assistance Received: None
********************************************************************* */
void Round::printRoundInfo() {

	auto p1 = players.at(0);
	auto p2 = players.at(1);
	auto p1Hand = p1->getHandOfPlayer();
	auto p2Hand = p2->getHandOfPlayer();
	std::cout << "Round: " << roundNum << "\n" << std::endl;

	p1->outputTypeOfPlayer();
	std::cout << ":" << std::endl;
	std::cout << "   Score: "  << p1->getScore() << std::endl;
	std::cout << "   Hand: ";
	p1Hand.outputHand();
	std::cout << "   Melds: ";
	p1Hand.outputMelds();
	std::cout << "\n" << std::endl;

	p2->outputTypeOfPlayer();
	std::cout << ":" << std::endl;
	std::cout << "   Score: " << p2->getScore() << std::endl;
	std::cout << "   Hand: ";
	p2Hand.outputHand();
	std::cout << "   Melds: ";
	p2Hand.outputMelds();
	std::cout << "\n" << std::endl;
	std::cout << "Stock: ";
	stockAndDiscard.outputStock();
	std::cout << "Discard Pile: ";
	stockAndDiscard.outputDiscard();

	std::cout << std::endl;
	std::cout << "Next Player: ";
	(nextPlayer == 1) ? p1->outputTypeOfPlayer() : p2->outputTypeOfPlayer();
	std::cout << std::endl;

	std::cout << std::endl;

}

/* *********************************************************************
Function Name: strToCard
Purpose: Converts strings to the cards in the game.
Parameters: 
			cardStr -> string representing a card in the game
Return Value: bool
Algorithm:
			1. Check if the size of cardStr is equal to 2. If it is not, print an error message and return false.
			2. Assign the first character in cardStr to a variable rank and the second character to a variable suit.
			3. Declare two strings rankList and suitsList containing all the possible ranks and suits, 
			   respectively, in a playing card.
			4. Check if rank can be found in rankList and suit can be found in suitsList. 
			   If either one cannot be found, print an error message and return false.
			5. If both rank and suit can be found in their respective lists, return true.
Assistance Received: None
********************************************************************* */
bool Round::strToCard(std::string cardStr) {

	if (cardStr.size() != 2) {

		std::cout << "Value selected is not valid card." << std::endl;
		return false;

	}

	else {

		char rank = cardStr.at(0);
		char suits = cardStr.at(1);
		std::string rankList = "123456789XAJQK";
		std::string suitsList = "HDCS12345678";

		if (rankList.find(rank) != std::string::npos && suitsList.find(suits) != std::string::npos)
			return true;

		else {

			std::cout << "String characters don't contain a valid rank and suit." << std::endl;
			return false;

		}

	}

}

/* *********************************************************************
Function Name: saveRound()
Purpose: Saves a file for the player.
Parameters: None
Return Value: void
Algorithm:
			1. Declare a variable fileName of type std::string.
			2. Prompt the user to enter the name they want to save the file as, and store the input in fileName.
			3. If the user enters "q", return from the function.
			4. Create an std::ofstream object named out and open the file with the name fileName.
			5. Save the current buffer in a variable coutBuf.
			6. Set the buffer to the buffer of out.
			7. Call the printRoundInfo function to output the round information to the file.
			8. Reset the buffer of std::cout to the original buffer saved in coutBuf.
			9. Close the file stream out.
Assistance Received: None
********************************************************************* */
void Round::saveRound() {

	std::string fileName;
	std::cout << "What would you like to save your file as? Type q to cancel." << std::endl;

	if (fileName == "q")
		return;

	getline(std::cin, fileName);
	std::ofstream out(fileName);
	std::streambuf* coutBuf = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());
	printRoundInfo();
	std::cout.rdbuf(coutBuf);

}