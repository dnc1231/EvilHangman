#include "EvilHangmanGame.h"
#include <fstream>
#include <iostream>
#include <set>
#include <map>
#include <string>
#include <vector>

using namespace std;

// EvilHangmanGame.cpp (or RunEvilHangman.cpp) -- EE 312 Project 9

/* Student information for project:
 *
 * On my honor, Daniel Canterino, this programming project is my own work
 * and I have not provided this code to any other student.
 *
 * Name: Daniel Canterino
 * email address: dnc1231@verizon.net
 * UTEID: djc3323
 * Section 5 digit ID: 16115
 * Number of slip days used on this assignment: 2
 */

// Evil hangman creates a hangman game where the user plays against a cheating computer. The computer has a dictionary
//and does not choose its word until it needs to, thus making it very difficult for the user to win

string makeLowerCase(string word);
void findPositions(string word, char guess, vector<int> & v);
bool comparePositions(string word, vector<int> v, char guess);
bool compareSizes(set<string> words1, set<string> words2, vector<int> positions, vector<int> actualPositions);

EvilHangmanGame::EvilHangmanGame() {


}

/* This function creates the initial word families based on the word length and the input file. */
void EvilHangmanGame::startGame(string dictionaryFile, int wordLength) {
    ifstream file;
    file.open(dictionaryFile);
    string word;
    currentWordsLength = wordLength;
    while(getline(file,word)){
        if (word.length() == currentWordsLength){
            word = makeLowerCase(word);
            currentWords.insert(word);
        }
    }
    file.close();
    if (currentWords.empty()){
        cout << "The dictionary does not contain any words of the specified length. Please choose a different dictionary." << endl;
        //need to end code
    }
}


/* makeGuess() takes the user's guess. If the character has been guessed before, a char is thrown.
   Otherwise, the guess is inserted into instance field guesses. Based on the guess, currentWords
   is updated.
*/
set<string> EvilHangmanGame::makeGuess(char guess) {
    try {
        if (guesses.find(guess) != guesses.end()) {
            throw guess;
        }
        if (guesses.find(guess) == guesses.end()) {//checks if letter has already been guessed or not
            guesses.insert(guess);
            vector<int> positions;
            set<string> current;
            set<string> actualWords;
            set<string> noGuess;
            vector<int> actualPositions;

            for (set<string>::iterator it = currentWords.begin(); it != currentWords.end(); it++) {
                string word = *it;
                current.clear();//resets the current set of strings for each iteration
                positions.clear();//resets the current positions
                if (word.find(guess) != string::npos) {
                    findPositions(word, guess, positions);
                    for (set<string>::iterator it2 = currentWords.begin(); it2 != currentWords.end(); it2++) {
                        string word2 = *it2;
                        if (comparePositions(word2, positions, guess)) {
                            current.insert(word2);
                        }
                    }
                } else if (word.find(guess) == string::npos) {
                    noGuess.insert(word);
                }
                if (compareSizes(current, actualWords, positions, actualPositions)) {
                    actualWords = current;
                    actualPositions = positions;
                }
            }
            positions.clear();
            if (compareSizes(noGuess, actualWords, positions, actualPositions)) {
                actualWords = noGuess;
                actualPositions.clear();//gets rid of any positions if biggest family was no position
            }
            this->currentWords = actualWords;
            return actualWords;
        }
    }
    __catch(char guess){
        cout << "You have already guessed that letter. Please try again" << endl;
        cin >> guess;
        makeGuess(guess);
    }
}

string makeLowerCase(string word){
    string lower; char offset = 32;//to convert from upper to lower
    for(int i = 0; i < word.length(); i++){
        if (word[i] < 'a'){
            char a = word[i] + offset;//makes a new char offset to ensure it's lowercase
            lower.push_back(a);
        }
        else if (word[i] >= 'a'){
            lower.push_back(word[i]);
        }
    }
    return lower;
}

void findPositions(string word, char guess, vector<int> & v){
    for (int i = 0; i < word.size(); i++){
        if (word[i] == guess){
            v.push_back(i);
        }
    }
}

bool comparePositions(string word, vector<int> v, char guess){
    int numGuessIn = 0;
    for (int j = 0; j < word.size(); j++){
        if (word[j] == guess){
            numGuessIn++;
        }
    }
    if (numGuessIn != v.size()) return false;
    else {
        for (int i = 0; i < v.size(); i++) {
            if (guess != word[v[i]]) return false;
        }
        return true;
    }
}

//returns true if the first set of words passed to it belongs to the larger family of words/hierarchy
bool compareSizes(set<string> words1, set<string> words2, vector<int> positions, vector<int> actualPositions) {
    if (words1.size() > words2.size() || (positions == actualPositions)) {
        return true;
    }
    else if (words1.size() < words2.size()) {
        return false;
    }
    else if (positions.empty()) return true;
    else if (positions.size() < actualPositions.size()) return true;
    else if (positions.size() > actualPositions.size()) return false;
    else {
        for (int i = positions.back(); i >= 0; i--) {
            if (positions[i] > actualPositions[i]){
                return true;
            }
        }
        return false;
    }
}
