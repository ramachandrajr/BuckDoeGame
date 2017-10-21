/**
 * console executable that makes use of BullCow class
 * this acts as view in MVC pattern, and is responsible for all 
 * user interaction. For game logic see the FBullCow class.
 */

#pragma execution_character_set( "utf-8" )
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include "FBuckDoeGame.h"




// make data types unreal friendly
using FText = std::string;
using int32 = int;



void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
void PrintAsciiArt(std::string);



FBuckDoeGame BCGame; // instantiate a new game, to use again and again




int main()
{
	bool Play{ true };

	do {
		PrintIntro();
		PlayGame();
		Play = AskToPlayAgain();
	}
	while (Play);	

	return 0;
}



void PlayGame()
{
	int32 MaxTries = BCGame.GetMaxTries();

	// reset game
	BCGame.Reset();	

	// loop while game is NOT won and there are still guesses remaining.
	while (BCGame.GetCurrentTry() <= MaxTries && !BCGame.IsGameWon()) {
		FText Guess = GetValidGuess();

		// submit valid guess to game
		FBuckDoeCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bucks = " << BullCowCount.Bulls;
		std::cout << ", Does = " << BullCowCount.Cows << std::endl;
	}

	// summarise game
	PrintGameSummary();

	return;
}



void PrintIntro()
{
	// clear screen at start of every game
	system("CLS");

	std::cout << "Welcome to Bucks and Does, a fun word game.\n";
	std::cout << std::endl;

	// print ASCII art from a file
	PrintAsciiArt("bucks.txt");

	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength()
		<< " letter isogram I'm thinking of?"
		<< std::endl;

	return;
}



FText GetValidGuess()
{
	// init at invalid
	EGuessStatus Status = EGuessStatus::INVALID;
	FText Guess{};

	// loop until user gives right guess.
	do {
		std::cout << "\n" << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << " tries. Enter you guess: ";
		getline(std::cin, Guess, '\n');

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::OK:
			//std::cerr << "Chachu all iz well!" << std::endl;	// debug
			break;
		case EGuessStatus::NOT_ISO:
			std::cerr << "Please enter a word without repeating letters!" << std::endl;
			break;
		case EGuessStatus::WRONG_LENGTH:
			std::cerr << "Please enter a " << BCGame.GetHiddenWordLength() << " length word!" << std::endl;
			break;
		case EGuessStatus::NOT_LOWERCASE:
			std::cerr << "Please enter your guess in lowercase alphabets!" << std::endl;
			break;
		default:
			std::cerr << "Damn we got something we can't handle!" << std::endl;
		}
	} while (Status != EGuessStatus::OK);


	return Guess;
}



bool AskToPlayAgain()
{
	FText Response{};

	std::cout << "Would you like to play again? (y|n) ";
	getline(std::cin, Response);
	std::cout << std::endl;

	return (Response[0] == 89 || Response[0] == 121);
}



/**
 * END OF GAME message
 */
void PrintGameSummary()
{
	if (BCGame.IsGameWon()) {
		PrintAsciiArt("fireworks.txt");
		std::cout << "\nCHEERS! YOU'VE WON!\n" << std::endl;
	}
	else {
		// TODO: add a few new lines and a shrug ascii art here				
		std::cout << "\nYou've lost!, better luck next time!\n" << std::endl;		
	}

	return;
}



/**
 * Prints ascii art from a file
 * @param	filename	ASCII art filename
 */
void PrintAsciiArt(std::string filename)
{
	std::fstream artFile = std::fstream(filename, std::ios::ios_base::in | std::ios::ios_base::binary);

	while (1)
	{
		std::string line{};
		// get a line.
		std::getline(artFile, line, '\n'); 

		// break on bad read or end of file
		if (artFile.eof() || artFile.bad()) { break; }

		std::cout << line << std::endl;
	}

	std::cout << "\n";

	return;
}