#pragma once
#include <string>
using FString = std::string;
using int32 = int;
//all values = zero
struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
	
};

enum class  EResetStatus 
{

};

class FBullCowGame 
{
public:
	FBullCowGame() ;

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; 

	void SelectWordFromDificulty(FString);
	void Reset(); 
	FBullCowCount SubmitValidGuess(FString);


private:
	int32 MyCurrentTry ;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;


	
};
	