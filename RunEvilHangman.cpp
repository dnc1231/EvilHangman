#include "EvilHangmanGame.h"
#include <iostream>
#include <sstream>
#include <set>
#include<string>
#include <vector>

using namespace std;

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

// Place your code description here (and remove this comment.)
vector<char> sort(vector<char> v);
int countDashes(string word);
bool notInSet(char guess, vector<char> lettersGuessed);

int main(int argc, char* argv[]) {

    int guessNum = 0;
    EvilHangmanGame newGame;
    char guess;
    int count = 0;
    string word;
    string word2;
    string curWord;
    vector<char> lettersGuessed;
    set<string> newWords;
    int dash;
    int dash2;


     string dictionaryFile = argv[1];
     int wordLength = atoi(argv[2]);
     int totalGuess = atoi(argv[3]);


    /*
    string dictionaryFile = "C:\\Users\\Daniel\\Documents\\Schoolwork\\EE 312\\p8\\smallDictionary.txt";
    int wordLength = 4;
    int totalGuess = 27;
*/
    if (totalGuess > 26 || totalGuess < 1){
        cout << "Please choose a guess limit between 1 and 26. Game Ending." << endl;
    }
    else {
        newGame.startGame(dictionaryFile, wordLength);
        while (guessNum < totalGuess && guessNum <= 26) {
            cout << "You have " << totalGuess - guessNum << " guesses left" << endl;
            cout << "Letters guessed: ";
            if (count != 0) {
                lettersGuessed = sort(lettersGuessed);
            }
            for (int i = 0; i < lettersGuessed.size(); i++) {
                cout << lettersGuessed[i] << " ";
            }
            cout << endl;
            cout << "Word: ";

            if (count == 0) {//constructs dashed word for the first time through
                for (int i = 0; i < wordLength; i++) {
                    word += "-";
                }
            } else {
                word.clear();//recreates dashed word
                for (int j = 0; j < wordLength; j++) {
                    word += '-';
                }
                for (int i = 0;
                     i < wordLength; i++) {//replaces dashes with letters guess if they are in the possible word
                    for (int k = 0; k < lettersGuessed.size(); k++) {
                        if (curWord[i] == lettersGuessed[k]) {
                            word[i] = lettersGuessed[k];
                            break;
                        } else {
                            word[i] = '-';
                        }
                    }
                }
            }
            dash = countDashes(word);
            cout << word;
            cout << endl << "Enter guess: ";
            cin >> guess;
            if (guess >= 'a' && guess <= 'z') {
                if (notInSet(guess, lettersGuessed)) {
                    lettersGuessed.push_back(guess);//stores the letters guessed to a local set
                    set<string> newWords = newGame.makeGuess(guess);//calls member function make guess
                    set<string>::iterator it = newWords.begin();
                    dash2 = 0;
                    curWord = *it;
                    word2.clear();
                    for (int j = 0; j < wordLength; j++) {
                        word2 += '-';
                    }
                    for (int i = 0; i < wordLength; i++) {
                        for (int k = 0; k < lettersGuessed.size(); k++) {
                            if (curWord[i] == lettersGuessed[k]) {
                                word2[i] = lettersGuessed[k];
                                break;
                            } else {
                                word2[i] = '-';
                            }
                        }
                    }
                    dash2 = countDashes(word2);
                    if (dash == dash2) {
                        cout << "Sorry there are no " << guess << "'s" << endl;
                        guessNum++;
                        if (guessNum == totalGuess) {
                            cout << "You lose!" << endl << "The word was: " << *it;
                            break;
                        } else {
                            cout << endl;
                        }
                    }
                    if (dash != dash2) {
                        cout << "Yes, there are " << dash - dash2 << " " << guess << "'s" << endl;
                        if (dash2 == 0) {
                            cout << "You win!" << endl << "The word was: " << word2 << endl << endl;
                            break;
                        }
                        if (guessNum == totalGuess) {
                            cout << "You lose!" << endl << "The word was: " << *it << endl;
                            break;
                        } else {
                            cout << endl;
                        }
                    }
                    count++;
                } else if (!notInSet(guess, lettersGuessed)) {
                    cout << "You have already guessed that letter. Please try again." << endl;
                }
            } else {
                cout << "That is not a valid input. Please try again." << endl << endl;
            }
        }
    }
}

vector<char> sort(vector<char> v){//sorts the vector of letters guessed to print out in order
    char temp;
    for (int i = 0; i < v.size(); i++){
        for (int j = i + 1; j < v.size(); j++){
            if (v[j] < v[i]){
                temp = v[i];
                v[i] = v[j];
                v[j] = temp;
            }
        }
    }
    return v;
}

int countDashes(string word){//counts how many dashes are still in a word
    int count = 0;
    for (int i = 0; i < word.size(); i++){
        if (word[i] == '-') count++;
    }
    return count;
}

bool notInSet(char guess, vector<char> lettersGuessed){
    bool flag = false;
    for (int i = 0; i < lettersGuessed.size(); i++){
        if (guess == lettersGuessed[i]){
            return flag;
        }
    }
    return true;
}