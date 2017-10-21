#pragma once

#include <iostream> // TODO: comment after debugging
#include <fstream>
#include <string>
#include <map> 
#include <cmath>
#include <cstdlib> // srand, rand
#include <ctime> // time

#include <exception>
#include "Util.h"

#define TMap std::map


// __DEBUG__ to turn debugging on / off
extern int __DEBUG__;


// unreal type syntaxing
using int32 = int;
using FString = std::string;





enum class EGuessStatus
{
	OK, NOT_ISO, WRONG_LENGTH, NOT_LOWERCASE, INVALID
};



struct FBuckDoeCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};



class FBuckDoeGame
{
public:
	// constructor
	FBuckDoeGame();

	// getters
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	// statuses
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();
	// count bulls & cows, and increase try #.
	FBuckDoeCount SubmitValidGuess(FString);



// ^^ Please try and ignore this and focus on the interface above ^^
private:
	// see constructor for init.
	int32 MyCurrentTry;
	FString MyHiddenWord;
	FString *Isograms;
	int32 IsogramArrSize;
	bool bGameWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;

	void InitIsogramArray(); // TODO: convert return value to int32
	std::string GetRandomWord(); // use this function to get a random word







	// NOTE: do not work on ↓↓ this function ↓↓ until GetRandomWord function is fully functional
	std::string GetRandomWord(int32 length); // use this if user has passed in a length
};




/**
* Custom Exception Class
*/
class invalid_response :
	public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return "Error: Invalid response!";
	}
};

