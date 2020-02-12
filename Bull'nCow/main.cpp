/* This is the console executable that makes use of the BullCow class
This acts as the view in MVC pattern, and is responsible for user interaction.
For game logic see the FBullCowGame class
*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// for UE
using int32 = int;
using FText = std::string;
 
void PrintIntro();
void SelectDificulty();
void PlayGame();
bool AskToPlayAgain();
FText GetValidGuess();
void PrintGameSummary();

FBullCowGame BCGame; //instantiate a new game
 

int main() 
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		//SelectDificulty();
		PlayGame();
		PrintGameSummary();
		bPlayAgain = AskToPlayAgain();
		}
	while (bPlayAgain);
	return 0;
}


void SelectDificulty()
{
	FText Dificulty = "";

	std::cout << "Please enter level of difficulty from 1 to 3: ";
	std::getline(std::cin, Dificulty);
	BCGame.SelectWordFromDificulty(Dificulty);
	std::cout << std::endl;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries ) 
	{
		FText Guess = GetValidGuess(); 
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
}

FText GetValidGuess() //loop until the user give a valid guess 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << "  of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		 Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please use only lowercase letters.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter the word without repeating letters.\n  \n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;

	
}

void PrintIntro() 
{
	int32 HiddenWordLength = 0;
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	SelectDificulty();
		HiddenWordLength = BCGame.GetHiddenWordLength();
	std::cout << "Can you guess the " << HiddenWordLength;
	std::cout << " letter isogram I'm thinking of.\n\n";
	return;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Congratz, You won!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}
bool AskToPlayAgain() 
{
	std::cout << "Do you want to play again (y/n)\n";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}

  