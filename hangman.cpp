/*
    hangman.cpp
        
    Method implementations for the hangman class.
 
    Author: Reed Baker
    CSCI 262

*/

#include "hangman.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

// constructor
hangman::hangman() {
   ifstream dict("dictionary.txt");
   while (!dict.eof()) {
      vector<string> tempWord(1);
      dict >> tempWord.at(0);
      if(!lengthWords.emplace(tempWord.at(0).size(), tempWord).second) {
         lengthWords.at(tempWord.at(0).size()).push_back(tempWord.at(0));
      }
   }
   srand(time(0));
   rand();
}



// start_new_game()
//
// Setup a new game of hangman.
bool hangman::start_new_game(int num_length, int num_guesses) {
   remainingGuesses = num_guesses;
   if (lengthWords.find(num_length) != lengthWords.end()) {
      words = lengthWords.at(num_length);
      displayWord += string(num_length, '-');
      return true;
   }
   else {
      return false;
   }
}


// process_guess()
//
// Process a player's guess - should return true/false depending on whether
// or not the guess was in the hidden word.  If the guess is incorrect, the
// remaining guess count is decreased.
bool hangman::process_guess(char c) {
   map<string, vector<string>> wordFamilies; //stores the word families
   guessedChars += c;
   double bestFamily = -1;
   string strBestFamily;
   for (int i = 0; i < words.size(); i++) {
      string family = words.at(i);
      int numLetters = 0; //number of letters that will be in displayWord if this family is chosen (only needed for the improved algorithm)
      for (int ii = 0; ii < family.size(); ii++) {
         if (family.at(ii) != c) {
            family.at(ii) = '-';
         }
         else {
            numLetters++;
         }
      }
      numLetters += lettersCorrect;
      vector<string> familyWords(1);
      familyWords.at(0) = words.at(i);
      if (!wordFamilies.emplace(family, familyWords).second) {
         wordFamilies.at(family).push_back(familyWords.at(0));
      }

      //this algorithm attempts to take into account the remaining guesses and the number of letters that will be in displayWord
      // if a specific family is chosen, as well as the number of words in the family
      if (useImprovedAlgorithm) {
         if (family == string(family.size(), '-') && remainingGuesses == 1) { //will set the best family as the one that makes the guess incorrect, if the player only has 1 guess left
            strBestFamily = family;
            break;
         }
         if (bestFamily < wordFamilies.at(family).size() * pow((displayWord.length() - numLetters) / static_cast<double>(displayWord.length()), 10.0 / remainingGuesses) * 10000000) {
            bestFamily = wordFamilies.at(family).size() * pow((displayWord.length() - numLetters) / static_cast<double>(displayWord.length()), 10.0 / remainingGuesses) * 10000000;
            strBestFamily = family;
         }
      }
      else { //will only choose the family with the largest number of words
         if (bestFamily < wordFamilies.at(family).size()) {
            bestFamily = wordFamilies.at(family).size();
            strBestFamily = family;
         }
      }
   }
   words = wordFamilies.at(strBestFamily);
   bool correct = false;
   for (int i = 0; i < strBestFamily.size(); i++) {
      if (strBestFamily.at(i) == c) {
         displayWord.at(i) = c;
         lettersCorrect++;
         correct = true;
      }
   }
   if (correct) {
      return true;
   }
   remainingGuesses--;
   return false;
}


// get_display_word()
//
// Return a representation of the hidden word, with unguessed letters
// masked by '-' characters.
const string hangman::get_display_word() {
    return displayWord;
}


// get_guesses_remaining()
//
// Return the number of guesses remaining for the player.
const int hangman::get_guesses_remaining() {
    return remainingGuesses;
}


// get_guessed_chars()
//
// What letters has the player already guessed?  Return in alphabetic order.
const string hangman::get_guessed_chars() {
    return guessedChars;
}


// was_char_guessed()
//
// Return true if letter was already guessed.
const bool hangman::was_char_guessed(char c) {
   for (char x : guessedChars) {
      if (x == c) {
         return true;
      }
   }
    return false;
}


// is_won()
//
// Return true if the game has been won by the player.
const bool hangman::is_won() {
    for (char c : displayWord) {
       if (c == '-') {
          return false;
       }
    }
    return true;
}


// is_lost()
//
// Return true if the game has been lost.
const bool hangman::is_lost() {
    return remainingGuesses == 0;
}

const string hangman::hiddenWord() {
   return words.at(rand() % words.size());
}

const int hangman::wordsLength() {
   return words.size();
}


