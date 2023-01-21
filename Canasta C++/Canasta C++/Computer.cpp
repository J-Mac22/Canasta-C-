#include <iostream>
#include "Computer.h"

/* *********************************************************************
Function Name: Computer
Purpose: Default constructor for the Computer class.
Parameters: None
Return Value: None
Assistance Received: None
********************************************************************* */
Computer::Computer() {

	meldBreakOff = 5;

}

/* *********************************************************************
Function Name: play
Purpose: Has all the components needed for the Computer to play Canasta.
Parameters:  
			useDecks -> Deck object representing the two decks being utilized in the game
			opponentMelds -> a vector of a vector of Cards representing the melds of the opponent player

Return Value: bool for if the Computer player can continue playing
Algorithm: 
			1. Declare a bool variable that checks if a Computer player can go out depending on the phases of the game.
			2. Don't have Computer player go out during the DRAW PHASE.
			3. Check if Computer player can go out depending on how the opponent did during the MELD PHASE.
			4. Do the same method for step 3 for the DISCARD PHASE.
			5. Return false and have Computer player continue playing otherwise.
Assistance Received: None
********************************************************************* */
bool Computer::play(Deck& useDecks, std::vector<std::vector<Card>> opponentMelds) {

	bool instantBreak;
	instantBreak = goOut();
	if (instantBreak) return true;

	instantBreak = draw(useDecks);
	if (instantBreak) return true;

	meld(opponentMelds);
	instantBreak = goOut();
	if (instantBreak) return true;

	discard(useDecks, opponentMelds);
	instantBreak = goOut();
	if (instantBreak) return true;

	return false;

}

/* *********************************************************************
Function Name: draw
Purpose: The drawing strategy for the Computer player.
Parameters: 
			useDecks -> Deck object representing the two decks being utilized in the game
Return Value: bool
Algorithm:	
			1. If the Computer sees that the first card of the discard pile can meld:
				1. As well as the discard pile isn't frozen:
					1. Also if the Computer has a hand size greater than five:
						1. Draw from the discard pile.
			2. If none of the above are true and the stock pile is empty:
				1. Draw from the stock pile instead.
			3. Otherwise, it will give up, saying it can not draw from either pile, hence the end of the game.
Assistance Received: None
********************************************************************* */
bool Computer::draw(Deck &useDecks) {

	Hand handOfPlayer = getHandOfPlayer();
	Card discardTop = useDecks.getDiscardTop();
	bool meldable = handOfPlayer.canMeld(discardTop);
	bool meldableWithMelds = handOfPlayer.canMeldWithMelds(discardTop);
	bool notSmallHand = (((int)handOfPlayer.getHandSize() > 5));

	if (((meldable || meldableWithMelds) && ((!hasACanasta() || ((hasACanasta()) && (notSmallHand))))
		&& (!useDecks.getFrozenDiscard()))) {
		std::cout << "Computer: drawing discard pile: can meld with hand or add onto melds, hand isn't that small." << std::endl;
		std::vector<Card> discardPickUp = useDecks.discardDraw();
		addToHand(discardPickUp);
		destroyRedThrees();
		return false;
	}

	else if (!useDecks.emptyStock()) {
		std::cout << "Computer: drawing from stock, because: ";

		Card cardDrawn;
		do {
			cardDrawn = useDecks.stockDraw();
			addToHand(cardDrawn);
			destroyRedThrees();
		} while (cardDrawn.isRedThrees() && !useDecks.emptyStock());


		if (useDecks.getFrozenDiscard())
			std::cout << "the discard pile is frozen." << std::endl;
		else if (!meldable)
			std::cout << "there are no cards in the Computer's hand that can meld with the card " << discardTop.getCardStr() << std::endl;
		else {
			std::cout << "The bot wants to keep a small hand." << std::endl;
		}
		return false;
	}

	else {
		std::cout << "The stock pile is empty and the Computer can't draw from the discard pile. It gave up!" << std::endl;
		return true;
	}

}

/* *********************************************************************
Function Name: discard
Purpose: The discard strategy for the Computer player.
Parameters:
			useDecks -> Deck object representing the two decks being utilized in the game
			opponentMelds -> a vector of a vector of Cards representing the melds of the opponent player
Return Value: void
Algorithm:
			1. Create a vector of every card that is not in the melds of the opponent. Otherwise, it will try
			   to discard from that vector.
			2. Create a list of every card that isn't a wild card, based on a sorted hand from least to greatest points.
			   Otherwise, it will try to discard cards that aren't wild cards.
			3. Check if the top of the discard pile is in the opponent's melds. If it is, 
			   check if it has a three of spades or clubs and discard that. Otherwise,
			   it will try to discard a card at the lowest point value in the hand.
			4. If there is nothing to discard, skip the discard turn.
Assistance Received: None
********************************************************************* */
void Computer::discard(Deck& useDecks, std::vector<std::vector<Card>> opponentMelds) {

	std::vector<Card> preferDiscard;
	std::vector<Card> notInMeldButWild;
	std::vector<Card> noWildDiscard;
	Hand handOfPlayer = getHandOfPlayer();

	//Making comparisons easier to do 
	handOfPlayer.sort();
	std::vector<Card> handContainer = handOfPlayer.getHandContainer();
	Card preferCard;
	int cardOnePosition = 0;

	auto itrThreeSpades= std::find(handContainer.begin(), handContainer.end(), Card("3S"));
	auto itrThreeClubs = std::find(handContainer.begin(), handContainer.end(), Card("3C"));

	for (int cardPosition = 0; cardPosition < handContainer.size(); cardPosition++) {

		Card cardToLook = handContainer.at(cardPosition);
		bool considerAdding = true;
		for (int meldPosition = 0; meldPosition < opponentMelds.size(); meldPosition++) {

			//Looking for the first card
			if (cardToLook.getFace() == opponentMelds.at(meldPosition).at(0).getFace()) {

				considerAdding = false;

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

	Card discardTop = useDecks.getDiscardTop();
	bool didThreeDiscard = false;

	for (int meldPosition = 0; meldPosition < opponentMelds.size(); meldPosition++) {
		if (discardTop.getFace() == opponentMelds.at(meldPosition).at(cardOnePosition).getFace()) {

			if (itrThreeSpades != handContainer.end()) {

				preferCard = *itrThreeSpades;
				useDecks.discardPushFront(*itrThreeSpades);
				handRemoval(*itrThreeSpades);

				std::cout << "The Computer chose to throw away 3S since it sees the top of the discard, "
					<< discardTop.getCardStr() << " is in opponent meld: "; outputMeld(meldPosition);
				std::cout << std::endl;

				didThreeDiscard = true;
				break;

			}


			else if (itrThreeClubs != handContainer.end()) {

				preferCard = *itrThreeClubs;
				useDecks.discardPushFront(*itrThreeClubs);
				handRemoval(*itrThreeClubs);

				std::cout << "The Computer chose to throw away 3C since it sees the top of the discard, "
					<< discardTop.getCardStr() << " is in opponent meld: "; outputMeld(meldPosition);
				std::cout << std::endl;

				didThreeDiscard = true;
				break;

			}

		}

	}

	if (preferDiscard.size() != 0 && !didThreeDiscard) {

		preferCard = preferDiscard.at(0);

		std::cout << "The Computer chose to throw away " << preferCard.getCardStr() << " since the lowest value  " <<
			"in the Computer's hand, with " << preferCard.getPointVal() << " points, and is not in the opponent's melds." << std::endl;

	}

	else if (notInMeldButWild.size() != 0 && !didThreeDiscard) {

		preferCard = notInMeldButWild.at(0);

		std::cout << "The Computer chose to throw away " << preferCard.getCardStr() << " since the lowest value  " <<
			"in the Computer's hand, with " << preferCard.getPointVal() << " points, and was not in opponent's meld." << std::endl;

	}

	else if (noWildDiscard.size() != 0 && !didThreeDiscard) {

		preferCard = noWildDiscard.at(0);

		std::cout << "The Computer chose to throw away " << preferCard.getCardStr() << " since the lowest value  " <<
			"in the Computer's hand, with " << preferCard.getPointVal() << " points, and it's not a wild card." << std::endl;

	}

	else if (handContainer.size() != 0 && !didThreeDiscard) {

		preferCard = handContainer.at(0);
		std::cout << "The Computer had no choice, so it threw away it's lowest value card, which was: " << preferCard.getCardStr() << std::endl;

	}

	else if (!didThreeDiscard) {

		std::cout << "The Computer has nothing to discard, so it stood by." << std::endl;
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

/* *********************************************************************
Function Name: meld
Purpose: The meld strategy for the Computer player.
Parameters:
			opponentMelds -> a vector of a vector of Cards representing the melds of the opponent player
Return Value: void
Algorithm:
			1. Have the Computer consider first if any of the cards in its hand can be made as a 
			   Canasta when discarded to the enemy.
			2. If it sees this, it will play more modestly, holding onto cards in its hand by restricting the total
			   number of cards laid off per meld by the size of the critical cards.
			3. Have the Computer make a copy of unique faces in the hand. 
			4. Have Computer see how many cards are there that make up that unique face (only if they are natural).
			5. If the face is already in a pre-existing meld, have Computer search and find the meld and add onto it.
				1. If not, if the cards are greater than three, it will make a meld.
				2. If there are two natural cards, save them for later, as they can be probably melded with a wild card.
				3. If there is just one, see if it can be laid off.
			6. Have the cards that have a possibility to be melded with wild cards be sorted in ascending order.
				1. Each pair will be melded with a vector of wild cards, while both are not empty.
				2. When choosing to meld with wild cards, have it choose the meld with the highest score. 
			7. Have the Computer sort a temporary vector of vectors of the meld container, by size, and decide
			   by the order of the size which melds are best to lay off wild cards.
			8. If the Computer checks that a meld can be created as a Canasta, through transferring wild cards,
			   have it do that from extracting wild cards from other melds greater than three, but less than seven.
			9. If the Computer did none of the strategies above, have it claim it did nothing.
			10.Also, have Computer say that this choice was because to seeing a critical card (a card that if
			   discarded will give a Canasta to the opponent) in it's hand.
Assistance Received: None
********************************************************************* */
void Computer::meld(std::vector<std::vector<Card>> opponentMelds) {

	Hand handOfPlayer = getHandOfPlayer();
	std::vector<Card> handContainer = handOfPlayer.getHandContainer();
	std::vector<std::vector<Card>> meldContainer = handOfPlayer.getMeld();
	std::vector<Card> noDuplicates;
	std::vector<Card> uniqueFaces;
	std::vector<Card> naturalVectorMeld;
	std::vector<Card> meldableWithWild;
	std::vector<Card> wildCardsInHand = handOfPlayer.getWildCardsFromHand();
	int handTransfer = -2;
	int criticalCardAmount = getCriticalCards(opponentMelds);

	if (criticalCardAmount > 0) {

		std::cout << "The Computer notices one of its' cards if discarded will allow opponent to make a Canasta, so it's playing more modestly." << std::endl;

	}

	//Removing duplicates
	bool actionDone = false;
	std::unique_copy(handContainer.begin(), handContainer.end(), std::back_inserter(noDuplicates));

	if ((hasACanasta() && handContainer.size() < 6)) {

		for (int meldPosition = 0; meldPosition < meldContainer.size(); meldPosition++) {

			if ((meldContainer.at(meldPosition).size() < 7 && meldContainer.at(meldPosition).size() > 3)
				|| meldContainer.at(meldPosition).size() > 7) {

				std::vector<Card> transferWildMeld = handOfPlayer.getWildCards(meldPosition);

				for (int wildPosition= 0; wildPosition < transferWildMeld.size(); wildPosition++) {

					if (handOfPlayer.canMeld(transferWildMeld.at(wildPosition))) {

						std::cout << "The Computer decided to transfer the wild card " << transferWildMeld.at(wildPosition).getCardStr() << " to the hand from meld " << wildPosition << ": ";
						outputMeld(wildPosition);
						std::cout << "since it is interested to throw away the cards out of it's hand to go out." << std::endl;
						cardTransfer(transferWildMeld.at(wildPosition), meldPosition, -2);
						actionDone = true;

					}

				}

			}

		}

	}

	handOfPlayer = getHandOfPlayer();
	wildCardsInHand = handOfPlayer.getWildCardsFromHand();

	//Ensure we represent each card of one face, which means no wild cards or special cards.
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

	//Look at the hand for unique faces. Tally the total of natural card s 
	//with the same rank. If it is 3 or higher, it will meld. If it is more than 4, it will lay off.
	for (int cardPosition = 0; cardPosition < uniqueFaces.size(); cardPosition++) {

		char faceToLook = uniqueFaces.at(cardPosition).getFace();
		handOfPlayer = getHandOfPlayer();
		handContainer = handOfPlayer.getHandContainer();
		meldContainer = handOfPlayer.getMeld();

		for (int handCPosition = 0; handCPosition < handContainer.size(); handCPosition++) {

			Card cardFromHand = handContainer.at(handCPosition);
			char faceExtract = cardFromHand.getFace();
			if (faceExtract == faceToLook && (!cardFromHand.isWild() && !cardFromHand.isSpecial())) {

				naturalVectorMeld.push_back(cardFromHand);

			}

		}

		bool meldExistsAlready = false;

		if (naturalVectorMeld.size() > 0) {

			meldExistsAlready = existingMeld(naturalVectorMeld.at(0));

		}

		else {

			meldExistsAlready = false;

		}

		if (naturalVectorMeld.size() >= 3 && !meldExistsAlready &&
			((int)handContainer.size() - criticalCardAmount > 0) &&
			!isACriticalCard(naturalVectorMeld.at(0), opponentMelds)) {

			Card cardOne = naturalVectorMeld.at(0);
			Card cardTwo = naturalVectorMeld.at(1);
			Card cardThree = naturalVectorMeld.at(2);
			makeMeld(cardOne, cardTwo, cardThree);
			handOfPlayer = getHandOfPlayer();

			for (int layOffPosition = 3; layOffPosition < (int)naturalVectorMeld.size() - criticalCardAmount; layOffPosition++) {

				cardLayoff(naturalVectorMeld.at(layOffPosition), handOfPlayer.getMeldSize() - 1);
				actionDone = true;

			}

			std::cout << "The Computer decided to meld the following cards: ";
			outputVector(naturalVectorMeld);
			std::cout << " as they were an all natural meld, and throwing away natural cards is generally beneficial." << std::endl;

		}

		else if (naturalVectorMeld.size() == 2 && !meldExistsAlready) {

			Card cardOne = naturalVectorMeld.at(0);
			Card cardTwo = naturalVectorMeld.at(1);

			meldableWithWild.push_back(cardOne);
			meldableWithWild.push_back(cardTwo);

		}

		else if (meldExistsAlready) {

			for (int meldPosition = 0; meldPosition < meldContainer.size(); meldPosition++) {

				if (naturalVectorMeld.at(0).getFace() == meldContainer.at(meldPosition).at(0).getFace()) {

					int sizeOfLoop;

					if (isACriticalCard(naturalVectorMeld.at(0), opponentMelds))
						sizeOfLoop = naturalVectorMeld.size();

					else
						sizeOfLoop = (int)naturalVectorMeld.size() - criticalCardAmount;


					for (int layOffPosition = 0; layOffPosition < sizeOfLoop; layOffPosition++) {

						actionDone = true;
						cardLayoff(naturalVectorMeld.at(layOffPosition), meldPosition);

						std::cout << "The Computer decided to lay off the following card(s): ";
						outputVector(naturalVectorMeld);
						std::cout << " as they were all natural cards, and throwing away natural cards is always beneficial." << std::endl;

					}

				}

			}

		}

		naturalVectorMeld.clear();

	}

	std::sort(meldableWithWild.begin(), meldableWithWild.end(),
		[](const Card& lhs, const Card& rhs) -> bool { return lhs > rhs; });

	while (meldableWithWild.size() != 0 && (int)wildCardsInHand.size() - criticalCardAmount > 0) {

		int cardPosition = 0;
		int cardTwoPosition= 1;
		int wildPosition = 0;

		Card firstNaturalCard = meldableWithWild.at(cardPosition);
		Card secondNaturalCard = meldableWithWild.at(cardTwoPosition);
		Card thirdWildCard = wildCardsInHand.at(wildPosition);

		std::cout << "The Computer decided to meld: ";
		outputVector(std::vector < Card >{firstNaturalCard, secondNaturalCard, thirdWildCard});
		std::cout << " as the two natural cards can meld with a wild card. " << std::endl;

		makeMeld(firstNaturalCard, secondNaturalCard, thirdWildCard);
		actionDone = true;

		//At beginning of vector, delete all pairs
		meldableWithWild.erase(meldableWithWild.begin() + cardPosition);
		meldableWithWild.erase(meldableWithWild.begin() + cardPosition);

		handOfPlayer = getHandOfPlayer();
		wildCardsInHand = handOfPlayer.getWildCardsFromHand();

	}

	handOfPlayer = getHandOfPlayer();
	wildCardsInHand = handOfPlayer.getWildCardsFromHand();
	meldContainer = handOfPlayer.getMeld();
	meldSort(meldContainer);

	for (int meldPosition = 0; meldPosition < meldContainer.size(); meldPosition++) {

		handOfPlayer = getHandOfPlayer();
		wildCardsInHand= handOfPlayer.getWildCardsFromHand();
		meldContainer = handOfPlayer.getMeld();
		meldSort(meldContainer);
		std::vector<Card> wildCardsFromMeld = handOfPlayer.getWildCardsWithoutTransferring(meldPosition);

		if (meldContainer.at(meldPosition).size() >= 3 && wildCardsInHand.size() <= 3) {


			while ((((int)wildCardsInHand.size() - criticalCardAmount) > 0) && wildCardsFromMeld.size() < 3) {

				int absolutePositionMeld = getMeldPosition(meldContainer.at(meldPosition));
				actionDone = true;

				std::cout << "The Computer chose to lay off the card " << wildCardsInHand.at(0).getCardStr() << " because the meld chose, ";
				outputVector(meldContainer.at(absolutePositionMeld));
				std::cout << " had the highest size and less than 3 wild cards, so it prioritized it." << std::endl;
				cardLayoff(wildCardsInHand.at(0), absolutePositionMeld);

				handOfPlayer = getHandOfPlayer();
				wildCardsInHand = handOfPlayer.getWildCardsFromHand();
				wildCardsFromMeld = handOfPlayer.getWildCardsWithoutTransferring(meldPosition);

			}

		}

	}

	handOfPlayer = getHandOfPlayer();
	meldContainer = handOfPlayer.getMeld();

	for (int meldPosition = 0; meldPosition < meldContainer.size(); meldPosition++) {

		std::vector<Card> meld = meldContainer.at(meldPosition);
		int meldableCanastaSum = meld.size() + 3 - getVectorWildCards(meld).size();
		int minimumCanasta = 7;
		handOfPlayer = getHandOfPlayer();
		meldContainer = handOfPlayer.getMeld();

		if (meldableCanastaSum >= minimumCanasta && meld.size() < 7 && !hasACanasta()) {

			int multipleMeldsPosition = (meldPosition == meldContainer.size() - 1) ? 0 : meldPosition + 1;

			while (multipleMeldsPosition != meldPosition) {

				handOfPlayer = getHandOfPlayer();
				meldContainer = handOfPlayer.getMeld();
				std::vector<Card> extractWildMelds = meldContainer.at(multipleMeldsPosition);

				if (extractWildMelds.size() > 3) {

					std::vector<Card> transferWild = handOfPlayer.getWildCards(multipleMeldsPosition);

					while (transferWild.size() != 0) {

						actionDone= true;

						std::cout << "Computer decided to transfer card " <<transferWild.at(0).getCardStr() << " from meld: ";  outputMeld(multipleMeldsPosition);
						std::cout << "As meld: "; outputMeld(meldPosition);
						std::cout << " can be made as a Canasta with just a few more wildcards." << std::endl;
						cardTransfer(transferWild.at(0), multipleMeldsPosition, meldPosition);

						transferWild.erase(transferWild.begin());

					}

				}

				handOfPlayer = getHandOfPlayer();
				meldContainer= handOfPlayer.getMeld();

				if (multipleMeldsPosition == meldContainer.size() - 1)
					multipleMeldsPosition = 0;

				else
					multipleMeldsPosition++;
			}
		}
	}


	if (!actionDone && criticalCardAmount == 0) {

		std::cout << "The Compter chose to do nothing, since it can't do anything involving melding." << std::endl;

	}

	else if (criticalCardAmount > 0 && !actionDone) {

		std::cout << "The Computer chose to do nothing, since it would do that than give a Canasta to the opponent." << std::endl;

	}

	handSort();

}

/* *********************************************************************
Function Name: playerStrategy
Purpose: Defines the strategy for the Computer player.
Parameters:
			useDecks -> Deck object representing the two decks being utilized in the game
			opponentMelds -> a vector of a vector of Cards representing the melds of the opponent player
Return Value: None
Assistance Received: None
********************************************************************* */
void Computer::playerStrategy(Deck& useDecks, std::vector<std::vector<Card>> opponentMelds) {

	std::cout << "The Computer has it's own strategy, so it won't need help." << std::endl;

}

/* *********************************************************************
Function Name: getTypeOfPlayer()
Purpose: Selector for the Computer player.
Parameters: None
Return Value: string representing the player is a Computer
Assistance Received: None
********************************************************************* */
std::string Computer::getTypeOfPlayer() {

	return "Computer";

}
 
/* *********************************************************************
Function Name: outputTypeOfPlayer()
Purpose: Outputs that type of player is Computer.
Parameters: None
Return Value: void
Assistance Received: None
********************************************************************* */
void Computer::outputTypeOfPlayer() {

	std::cout << "Computer";

}

/* *********************************************************************
Function Name: decideGoOut()
Purpose: Has the Computer choose to go out since it loves 100 bonus points.
Parameters: None
Return Value: bool for if the Computer decides to go out
Assistance Received: None
********************************************************************* */
bool Computer::decideGoOut() {

	std::cout << "The Computer decided to go out since it loves 100 bonus points." << std::endl;
	return true;

}
