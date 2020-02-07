#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.cpp"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame(int32 CountTry,FText Word);
	bool AskToPlayAgain();

	int main() {
		bool bPlayAgain = false;
		do {
			FText Word= "snake";
			PrintIntro();
			PlayGame(5,  Word);
			bPlayAgain = AskToPlayAgain();

		} while (bPlayAgain);
		return 0;
	}


	void PrintIntro() {
		std::cout << "Bull'nCow game\n";
	std::cout << "SampleText_SampleText_SampleText_SampleText_SampleText_SampleText\n";
	std::cout << "SampleText_SampleText_SampleText_SampleText_SampleText_SampleText\n";
	std::cout << "SampleText_SampleText_SampleText_SampleText_SampleText_SampleText\n";
	std::cout << "SampleText_SampleText_SampleText_SampleText_SampleText_SampleText\n";
	std::cout << "Can you guess the (HERE NUMBER OF LETTER). This word is  isogram.\n";
}
void PlayGame(int32 Count, FText Word) {	
	int WordLength = Word.length();	
	std::cout << "You have " << Count <<" tries. Enter the guess: ";	
	FText Response = "";
	std::getline(std::cin, Response);
	if (Response.length() != WordLength) {
		std::cout << "Incorrect! Please enter " << WordLength << " letter word\n";
		PlayGame(Count, Word);
	}
	for (int i = 0; i < WordLength; ++i) {
		for (int k = WordLength; k != i; --k) {
			if (Response[i] == Response[k]) {
				std::cout << "This word should be isogram\n";
				PlayGame(Count, Word);
			}
		}
	}
	Count--;
	int32 Bull = 0;
	int32 Cow  = 0;
	for (int i = 0; i < WordLength; ++i) {
		if (Response[i] == Word[i]) ++Bull;
		for (int k = WordLength-1; k >= 0; --k) {
			if (Response[i] == Word[k] && i!=k) {
				Cow++;
				break;
			}
		}
	}
	std::cout << "Bulls: " << Bull;
	std::cout <<" Cows: "<< Cow << std::endl;
	if (Count != 0 && Bull != WordLength) PlayGame(Count, Word);
	std::cout << "Congratz! Correct!\n";
}
bool AskToPlayAgain() {
	std::cout << "Do you want to play again (y/n)\n";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}