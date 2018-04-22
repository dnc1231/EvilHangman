#ifndef _EVIL_HANGMAN_GAME_H
#define _EVIL_HANGMAN_GAME_H

#include <set>
#include<string>

using namespace std;

class EvilHangmanGame {
private:
    set<string> currentWords;  // current word bank, i.e., active word list
    int currentWordsLength;    // word length chosen by user
    set<char> guesses;         // characters that the user has guessed
public:
    /* Constructs an EvilHangmanGame object. */
    EvilHangmanGame();

    /* This function creates the initial word families based on the word length and the input file. */
    void startGame(string dictionaryFile, int wordLength);

    /* makeGuess() takes the user's guess. If the character has been guessed before, a char is thrown.
       Otherwise, the guess is inserted into instance field guesses. Based on the guess, currentWords
       is updated. 
    */
    set<string> makeGuess(char guess);
};

#endif