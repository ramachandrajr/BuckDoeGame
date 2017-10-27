#include "stdafx.h"
#include "FBuckDoeGame.h"



int __DEBUG__{ 0 }; // NOTE: **** set this to 0 if not debugging ****



// constructor
FBuckDoeGame::FBuckDoeGame() {
	InitIsogramArray(); // NOTE: needs to be inited once per console session, do not put in reset.
	Reset();
}



// getters
int32 FBuckDoeGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBuckDoeGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }



/**
 * Calculates max tries based on word length
 */
int32 FBuckDoeGame::GetMaxTries() const 
{
	int x = MyHiddenWord.length();
	// x^1.2 * log(x)
	int y = static_cast<int> (std::pow(x, 1.2) * std::log(x));
	return y;
}



bool FBuckDoeGame::IsGameWon() const { return bGameWon; }



void FBuckDoeGame::Reset()
{
	const FString HIDDEN_WORD = GetRandomWord();

	// INIT
	bGameWon = false;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;	

	if (__DEBUG__) std::cout << "\nWord = " << HIDDEN_WORD << "\n" << std::endl; // debug

	return;
}



// recieves a VALID guess, increments turn, and returns count.
FBuckDoeCount FBuckDoeGame::SubmitValidGuess(FString Guess)
{	
	FBuckDoeCount BuckDoeCount;	
	++MyCurrentTry;

	for (int32 i{ 0 }; i < GetHiddenWordLength(); ++i)
	{		
		if (Guess[i] == MyHiddenWord[i])
			++(BuckDoeCount.Bulls);
		else if (RJ::IndexOf(MyHiddenWord, Guess[i]) > -1)
			++(BuckDoeCount.Cows);
	}

	// end game if guessed 'em all right
	if (BuckDoeCount.Bulls == GetHiddenWordLength())
		bGameWon = true;		

	return BuckDoeCount;
}



bool FBuckDoeGame::IsIsogram(FString Guess) const
{
	// treat 0 and 1 letter words as isograms
	if (Guess.length() < 2) { return true; }

	TMap<char, bool> LetterSeen; // create new map

	for (char Letter : Guess) {
		// change capital alphabets to lowercase
		Letter = tolower(Letter);

		// if exists in hash map
		if (LetterSeen[Letter] == true) { return false; }
		// add to hash map
		else { LetterSeen[Letter] = true; }
	}


	return true;
}



bool FBuckDoeGame::IsLowercase(FString Guess) const
{
	for (auto letter : Guess) {		
		// check if it is lowercase
		if (! islower(letter)) { return false; }
	}

	return true;
}



/**
 * Reads in isograms from a file
 * NOTE: sets them manually if file not found
 */
void FBuckDoeGame::InitIsogramArray()
{	
    int numIsos{ 0 };
    std::string numIsosAsText{};
    std::fstream isosFile = std::fstream("isograms.txt", std::ios::ios_base::in);

    // if file not found
    if (!isosFile.is_open())
    {
        Isograms = { "aftershock", "brick", "stumped", "filmography" };
        IsogramArrSize = 4;
        return;
    }


    // ######## get number of isograms ########
    std::getline(isosFile, numIsosAsText, '\n'); // firstline == number of isos in file
    numIsos = atoi(numIsosAsText.c_str());
    this->Isograms.reserve(numIsos);
    

    // ######## read in isograms ########
    for (int i{ 0 }; i < numIsos; ++i)
    {
        std::string line{};
        std::getline(isosFile, line, '\n');
        if (isosFile.eof() || isosFile.bad()) { break; }
        this->Isograms.push_back(std::move(line));
    }
    

    this->IsogramArrSize = numIsos;

    return;
}



/**
 * Gets a random word from isograms array
 */
std::string FBuckDoeGame::GetRandomWord()
{
	int randomIndex{};

	// generate random integer between zero and IsogramArrSize
	std::srand(static_cast<unsigned int> (std::time(NULL)));
	randomIndex = rand() % IsogramArrSize;

	return Isograms[randomIndex];
}



EGuessStatus FBuckDoeGame::CheckGuessValidity(FString Guess) const
{	
	if (! IsIsogram(Guess))		// if the guess isn't an isogram, return an error
	{
		return EGuessStatus::NOT_ISO;
	}
	else if (! IsLowercase(Guess)) // if the guess isn't all lowercase
	{
		return EGuessStatus::NOT_LOWERCASE;
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::WRONG_LENGTH;
	}
	else			// otherwise
	{
		return EGuessStatus::OK;
	}
}
