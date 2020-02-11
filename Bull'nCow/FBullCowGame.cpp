#include "FBullCowGame.h"
#include <map>
#include <iostream>
#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); } //default construct

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {4,5},{5,7},{6,10} };
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

void FBullCowGame::SelectWordFromDificulty(FString DificultyLevel)
{
	TMap<FString, FString> WordFromDificulty{ {"1","bite"},{"2","spark"},{"3","earths"} };

	MyHiddenWord = WordFromDificulty[DificultyLevel];
}

void FBullCowGame::Reset()
{
	//const FString HIDDEN_WORD = "planet";
	//MyHiddenWord = "";
	
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const 
{ 
	
	if (!IsIsogram(Guess))// if hte guess isnt an isogram 
	{		
		return EGuessStatus::Not_Isogram;

	}
	else if (!IsLowerCase(Guess)) // if hte guess isnt all lowercase 
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (GetHiddenWordLength() != Guess.length()) // if hte guess length isnt correct 
	{
		return EGuessStatus::Wrong_Length;
	} else 
	{
		return EGuessStatus::OK;
	}

}

//recieves a VALID guess, incriments tries, and return tries
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); //assuming same length as guess
	// loop trough all letters in the hiddenword
	for (int32 MHWChar = 0; MHWChar < WordLength; ++MHWChar) 
	{
		//compare letters againts guess
		for (int32 GChar = 0; GChar < WordLength; ++GChar) {
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) { BullCowCount.Bulls++; }
				else {
					BullCowCount.Cows++;
				} 
			}
		}
	} 
	if (BullCowCount.Bulls == WordLength) { bGameIsWon = true; }
	else { bGameIsWon = false; }
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Guess) const {
	TMap<char, bool> LetterSeen;
	if (Guess.length() < 2) { return true; }
	
	for (auto Letter : Guess )
	{
		Letter = tolower(Letter);
		if(!LetterSeen[Letter]) {
			LetterSeen[Letter] = true;
		} else { 
			return false; 
		}
	}
	return true;
}

bool FBullCowGame::IsLowerCase(FString Guess) const
{
	for (auto Letter : Guess)
	{
		if (!islower(Letter)) 
		{ 
			return false; 
		}
	}
	return true;
}
