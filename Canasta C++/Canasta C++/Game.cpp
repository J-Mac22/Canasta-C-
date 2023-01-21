#include "Game.h"


/* *********************************************************************
Function Name: Game
Purpose: Default constructor for the Game class.
Parameters: None
Return Value: None
Assistance Received: None
********************************************************************* */
Game::Game() {

	round = 0;

}

/* *********************************************************************
Function Name: ~Game
Purpose: Default destructor for the Game class.
Parameters: None
Return Value: None
Assistance Received: None
********************************************************************* */
Game::~Game() {

	if (players.size() > 0) {

		delete players.at(0);
		delete players.at(1);

	}

}

/* *********************************************************************
Function Name: Game
Purpose: Default constructor for the Game class.
Parameters:
			anotherGame -> a const of the Game class that represents another game of Canasta

Return Value: None
Algorithm:
			1. Set the private variables by using the anotherGame object.

Assistance Received: None
********************************************************************* */
Game::Game(const Game& anotherGame) {

	players = anotherGame.players;
	round = anotherGame.round;

}

/* *********************************************************************
Function Name: mainMenu()
Purpose: Prints the main menu of the game.
Parameters: None
Return Value: void
Algorithm:
			 1. Enter a do-while loop, which will continue to execute until the integer, "pick", is equal to 3.
			 2. Print the main menu options and prompt user to pick one by calling the "checkUserInput" function.
			 3. Enter a switch statement. Depending on the value of "pick, the function will perform a different action.
			 4. If "pick" is 1, go over to the "Select Type of Game" screen.
			 5. If "pick" is 2, attempt to load a saved game. It will return true if so.
				If the load was not successful, print error message to the user.

Assistance Received: None
********************************************************************* */
void Game::mainMenu() {

	std::string inputStr;
	int pick = 0;

	do {

		std::cout << "Welcome to Canasta! Please select an option: " << std::endl;
		std::cout << "1. New Game " << std::endl;
		std::cout << "2. Load Game " << std::endl;
		std::cout << "3. Exit" << std::endl;
		pick = checkUserInput(1, 3);

		switch (pick) {

		case 1:
			pickTypeOfPlayer();
			break;

		case 2: {

			Round roundLoading;
			bool loadComplete = roundLoading.loadGame();

			if (loadComplete) {

				players = roundLoading.getPlayers();
				mainGame(roundLoading);

			}

			else
				std::cout << "Can't load file." << std::endl;
			break;

		}

		case 3: {

			return;

		}

		default:
			std::cout << "Unknown option." << std::endl;

		}

	} while (pick != 3);

}

/* *********************************************************************
Function Name: pickTypeOfPlayer()
Purpose: A menu where the user can pick what type of game they would like to play.
Parameters: None
Return Value: void
Algorithm:
			1. Enter a do-while loop, which will continue to execute until the int variable, "pick", is equal to 3.
			2. Print a menu of options to the user and prompt user to pick one by calling "checkUserInput".
			3. If "pick" is 1, push back the two players of the Human class.
			4. If "pick" is 2, push back the Human player and the Computer player.
			5. If "pick" is 3, return and break.
			6. If the value of the switch expression is none of the above, print an error message to the user.

Assistance Received: None
********************************************************************* */
void Game::pickTypeOfPlayer() {

	std::string inputStr;
	int pick;

	//To avoid crashing after returning to main menu the first time
	do {

		std::cout << "Welcome to Canasta! Select a game type: " << std::endl;
		std::cout << "1. Player vs Player" << std::endl;
		std::cout << "2. Player vs Computer" << std::endl;
		std::cout << "3. Back to Main Menu" << std::endl;
		pick = checkUserInput(1, 3);

		switch (pick) {

		case 1: {

			players.push_back(new Human);
			players.push_back(new Human);
			mainGame();
			return;
			break;

		}

		case 2:

			players.push_back(new Computer);
			players.push_back(new Human);
			mainGame();
			return;
			break;

		case 3:

			return;
			break;

		default:

			std::cout << "Unknown option." << std::endl;
			break;

		}

	} while (pick != 3);

}

/* *********************************************************************
Function Name: mainGame()
Purpose: Asks the player if they would like to play another round and decide victor if user says no.
Parameters: None


Return Value: void
Algorithm:
			1. Enter a do-while loop until int variable "pick" is equal to 2 or bool value of HasExited is true.
			2. Ask user if they would like to play a new round.
			3. If hasExited is false,  prompt the user to choose whether they want to play a new round or not. 
			   If the user chooses to play a new round (i.e. pick is 1), the loop continues. If the user chooses not to play a new round (i.e. pick is 2), the loop breaks.
			4. After loop, decide winner of the game by calling the "chooseVictor" function.
			5. Delete the two Player objects and clear the "players" vector.

Assistance Received: None
********************************************************************* */
void Game::mainGame() {

	int pick = 0;
	int roundNum = 0;
	auto p1 = players.at(0);
	auto p2 = players.at(1);
	bool hasExited = false;

	do {

		roundNum++;
		Round gameRound(players, roundNum);
		hasExited = gameRound.mainRound(false);

		if (hasExited) break;

		std::cout << "Would you like to play a new round?" << std::endl;
		std::cout << "1. Yes" << std::endl;
		std::cout << "2: No" << std::endl;
		pick = checkUserInput(1, 2);

		p1->deleteHandAndMeld();
		p2->deleteHandAndMeld();

	} while (pick != 2 && hasExited == false);

	if (!hasExited)
		chooseVictor();

	delete players.at(0);
	delete players.at(1);
	players.clear();

}

/* *********************************************************************
Function Name: mainGame()
Purpose: Asks the player if they would like to play another round and decide victor if user says no.
Parameters: 
			roundLoaded->a Round object that loads a round of Canasta

Return Value: void
Algorithm:
			1. Enter a do-while loop until int variable "pick" is equal to 2 or bool value of HasExited is true.
			2. Inside the loop, return a bool indicating where the round was exited prematurely or not.
			3. Ask user if they would like to play a new round.
			4. If hasExited is false,  prompt the user to choose whether they want to play a new round or not.
			   If the user chooses to play a new round (i.e. pick is 1), the loop continues. If the user chooses not to play a new round (i.e. pick is 2), the loop breaks.
			5. After loop, decide winner of the game by calling the "chooseVictor" function.
			6. Delete the two Player objects and clear the "players" vector.

Assistance Received: None
********************************************************************* */
void Game::mainGame(Round &roundLoaded) {

	int pick = 0;
	int roundNum = 0;
	int loopCounter = 0;
	auto p1 = players.at(0);
	auto p2 = players.at(1);
	bool hasExited = false;

	do {

		if (loopCounter == 0)
			hasExited = roundLoaded.mainRound(true);

		else {

			Round gameRound(players, roundNum);
			hasExited = gameRound.mainRound(false);

		}

		if (hasExited) break;

		std::cout << "Would you like to play a new round?" << std::endl;
		std::cout << "1. Yes" << std::endl;
		std::cout << "2. No" << std::endl;
		pick = checkUserInput(1, 2);
		roundNum++;
		loopCounter++;
		p1->deleteHandAndMeld();
		p2->deleteHandAndMeld();

	} while (pick != 2 && hasExited == false);

	if (!hasExited)
		chooseVictor();

	delete players.at(0);
	delete players.at(1);
	players.clear();

}

/* *********************************************************************
Function Name: chooseVictor()
Purpose: Decides who has won Canasta.
Parameters: None
Return Value: void
Algorithm:
			 1. Get scores of the players by calling their respective "getScore" functions.
			 2. Compare the scores to determine the winner and loser of the game.
			 3. If "p1" has a higher score, print out that "p1" is the winner and "p2" as the loser.
			 4. If "p2" has a higher score, print out that "p2" is the winner and "p1" is the loser.

Assistance Received: None
********************************************************************* */
void Game::chooseVictor() {

	auto p1 = players.at(0);
	auto p2 = players.at(1);
	int p1Score = p1->getScore();
	int p2Score = p2->getScore();

	if (p1Score > p2Score) {

		std::cout << "Winner: Player 1 (" << p1->getTypeOfPlayer() << ") with score of " << p1Score << std::endl;
		std::cout << "Loser: Player 2 (" << p2->getTypeOfPlayer() << ") with score of " << p2Score << std::endl;

	}

	else {

		std::cout << "Winner: Player 2 (" << p2->getTypeOfPlayer() << ") with score of " << p2Score << std::endl;
		std::cout << "Loser: Player 1 (" << p1->getTypeOfPlayer() << ") with score of " << p1Score << std::endl;

	}

}

/* *********************************************************************
Function Name: checkUserInput
Purpose: Will validate the inputs made by the user when needed.
Parameters:
			lower -> int that represents the lower bound
			upper -> int that represents the upper bound


Return Value: int that checks if the options are within the range
Algorithm:
			1. Enter a do-while loop that will continue until the bool, "valid", becomes true.
			2. Take user input and store it in "input".
			3. Check if all characters in 'input' are digits using both "all_of" and "isdigit".
			4. If all characters are digits, convert 'input' to an int and store in 'optionConvert'.
			5. Check if 'optionConvert' is within the range specified by lower bound and upper bound.
			6. If it is, set 'valid' to true.
			7. If not, print an error message and continue the loop.

Assistance Received: None
********************************************************************* */
int checkUserInput(int lower, int upper) {

	std::string input;
	bool valid = false;
	int optionConvert = 0;

	do {

		std::cin >> input;
		std::cin.clear();
		std::cin.ignore(10000000, '\n');

		if (std::all_of(input.begin(), input.end(), ::isdigit)) {

			optionConvert = std::stoi(input);

			if (optionConvert >= lower && optionConvert <= upper) {

				valid = true;

			}

			else {

				std::cout << "Error: Not a valid option." << std::endl;

			}

		}

		else {

			std::cout << "Error: String not numeric." << std::endl;

		}

	} while (valid != true);

	return optionConvert;

}

/* *********************************************************************
Function Name: checkUserInput
Purpose: Will validate the inputs made by the user when needed.
Parameters:
			lower -> int that represents the lower bound
			upper -> int that represents the upper bound
			uniqueOption -> bool that checks if the user selected option is unique or not

Return Value: int that checks if the options are within the range
Algorithm:
			1. Enter a do-while loop that will continue until the bool, "valid", becomes true.
			2. Take user input and store it in "input".
			3. Check if all characters in 'input' are digits using both "all_of" and "isdigit".
			4. If all characters are digits, convert 'input' to an int and store in 'optionConvert'.
			5. Check if 'optionConvert' is within the range specified by lower bound and upper bound.
			6. If it is, set 'valid' to true.
			7. If not, print an error message and continue the loop.

Assistance Received: None
********************************************************************* */
int checkUserInput(int lower, int upper, bool uniqueOption) {

	std::string input;
	bool valid = false;
	int optionConvert = 0;

	do {

		std::cin >> input;
		std::cin.clear();
		std::cin.ignore(10000000, '\n');

		if (input == "-1")
			return -1;


		if (std::all_of(input.begin(), input.end(), ::isdigit)) {

			optionConvert = std::stoi(input);

			if (optionConvert >= lower && optionConvert <= upper) {

				valid = true;

			}

			else {

				std::cout << "Error: Not a valid option" << std::endl;

			}

		}

		else {

			std::cout << "Error: String not numeric." << std::endl;

		}

	} while (valid != true);

	return optionConvert;

}