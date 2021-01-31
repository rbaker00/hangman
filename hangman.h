#ifndef _HANGMAN_H
#define _HANGMAN_H

/*
    hangman.h
        
    Class definition for the hangman class.
    Class allows one to play hangman, but with a twist. Instead of the computer choosing a word, it continually chooses the best
    "word family" based on the character guessed by the player. For example, if I guessed 'a', some families could be "-----",
    "-a---", "-a-a--", etc. By default, the best family is the one that has the most amount of words in it.

    Author: Reed Baker
    CSCI 262

*/

#include <string>
#include <vector>
#include <map>

using namespace std;

/******************************************************************************
   class hangman

   Maintains game state for a game of hangman.

******************************************************************************/

class hangman {
public:
    //opens dictionary.txt, reads in words and puts them into lengthWords appropriately, and sets a seed for rand() based on the time
    hangman();


    // Start a new game where player gets num_guesses unsuccessful tries. Returns whether or not if there were any words of the specified length in the dictionary
	 bool start_new_game(const int num_length, const int num_guesses);

    // player guesses letter c; return whether or not char is in word
    bool process_guess(char c);

    // display current state of word - guessed characters or '-'
    const string get_display_word();

    // How many guesses remain?
	 const int get_guesses_remaining();

    // What characters have already been guessed (for display)?
    const string get_guessed_chars();

    // Has this character already been guessed?
    const bool was_char_guessed(char c);

    // Has the game been won/lost?  (Else, it continues.)
    const bool is_won();
    const bool is_lost();

    //if the player lost, picks a random word to show to the player from the vector words
    const string hiddenWord();

    //bool for whether or not to show how many words are in the vector words
    bool showRemainingWords = false;

    //returns how many elements are in the vector words
    const int wordsLength();




private:
    const bool useImprovedAlgorithm = false; //bool for whether or not to use the "improved" algorithm. Default value is never changed, up to the class user to set
    map<int, vector<string>> lengthWords; //Maps each word in the dictionary. THe key is the length of a word, and the value is a vector containing all words of that length.
    vector<string> words; //pointer to a vector to store the remaining words
    string displayWord; //string that holds what to display to the player, e.g. "-e--o"
    int lettersCorrect; //stores how many letters in the word have been guessed. If the displayWord is "-e--o", lettersCorrect would be 2
    string guessedChars; //holds the characters guessed by the player
    int remainingGuesses; //stores how many incorrect guesses the player has left
};

#endif
