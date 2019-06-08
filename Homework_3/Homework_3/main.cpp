/**
 *
 * Solution to homework task
 * Data Structures Course
 * Faculty of Mathematics and Informatics of Sofia University
 * Winter semester 2016/2017
 *
 * @author Stoicho Ganchev
 * @idnumber 45177
 * @task 3
 * @compiler VC
 *
 */
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include "Trie.h"
using namespace std;

//Words must not be longer than 1024 characters!
const int MAX_SIZE = 1024;

int main(int argc, char * argv[])
{
	Trie Dictionary;
	ifstream dictionary;
	dictionary.open(argv[1]);
	if (!dictionary.is_open()) {
		cerr << "Dictionary " << argv[1] << " could not be opened!" << endl;
	}
	else {
		while (dictionary.peek() != EOF) {
			char phrase[MAX_SIZE] = { '\0' };
			//The value is stored here and is converted with atoi
			char phraseValue[32] = { '\0' };
			dictionary.getline(phrase, MAX_SIZE);
			//Start from the end of the string, storing the value in another string and decrement the string until the first 'a'-'z' character is found
			for (int i = strlen(phrase) - 1; (phrase[i]<'a' || phrase[i] > 'z'); i--) {
				if (phrase[i - 1] >= 'a' && phrase[i - 1] <= 'z') {
					phrase[i] = '\0';
					break;
				}
				//Store the value in reversed string
				else if (phrase[i] >= '0' && phrase[i] <= '9') {
					for (int j = 0; ((phrase[i] >= '0' && phrase[i] <= '9') || phrase[i] == '-'); j++) {
						phraseValue[j] = phrase[i];
						i--;
					}
					//Reverse the value to its original form
					for (int first = 0, last = strlen(phraseValue) - 1; first < last; first++, last--) {
						char tmp = phraseValue[first];
						phraseValue[first] = phraseValue[last];
						phraseValue[last] = tmp;
					}
				}
				phrase[i] = '\0';
			}
			Dictionary.Add(phrase, atoi(phraseValue));
		}
	}
	dictionary.close();

	for (int i = 2; i < argc; i++) {
		int textScore = 0;
		int wordsInText = 0;
		ifstream text;
		text.open(argv[i]);
		if (!text.is_open()) {
			cerr << "Error opening text " << argv[i] << "!" << endl;
		}
		else {
			while (text.peek() != EOF) {
				char phrase[MAX_SIZE] = { '\0' };
				char nextLetter;
				//tmpValue will be used if longer phrase with this prefix exists in dictionary but is not found the same in the text
				int tmpValue;
				for (int i = 0; i < MAX_SIZE; i++) {
					//Stop writing the phrase if EOF is reached
					if (text.peek() != EOF) {
						text.get(nextLetter);
					}
					else {
						//Do not count words unless they are actually words(e.g. will not count ' ' as a word)
						if (phrase[0] >= 'a' && phrase[0] <= 'z') {
							wordsInText++;
						}
						break;
					}
					nextLetter = tolower(nextLetter);
					if (nextLetter >= 'a' && nextLetter <= 'z') {
						phrase[i] = nextLetter;
					}
					if (nextLetter <'a' || nextLetter > 'z') {
						phrase[i] = '\0';
						//Do not count words unless they are actually words(e.g. will not count ' ' as a word)
						if (phrase[0] >= 'a' && phrase[0] <= 'z') {
							wordsInText++;
						}
						break;
					}
				}
				tmpValue = Dictionary.findScore(phrase);
				//If the phrase consist of two or more words, enter in this loop
				while (Dictionary.hasLongerPhrase(phrase)) {
					phrase[strlen(phrase)] = ' ';
					text.get(nextLetter);
					nextLetter = tolower(nextLetter);
					//If there are two consecutive ' ', '\n', '\t' the phrase is not recognized
					if (nextLetter == ' ' || nextLetter == '\n' || nextLetter == '\t') {
						break;
					}else if (nextLetter >= 'a' && nextLetter <= 'z') {
						int pos = strlen(phrase);
						while (nextLetter >= 'a' && nextLetter <= 'z') {
							phrase[pos] = nextLetter;
							if (text.peek() != EOF) {
								text.get(nextLetter);
							}else {
								break;
								wordsInText++;
							}
							pos++;
						}
						phrase[strlen(phrase)] = '\0';
						wordsInText++;
					}
					//If the phrase exists set tmpValue to its value so as not to lose it if longer exist in dictionary, but not found
					if (Dictionary.findScore(phrase) != 0) {
						tmpValue = Dictionary.findScore(phrase);
					}
					//If the next word is not found, the position of the ifstream pointer is set to the beginning of the last checked word
					//and the words are decremented
					else {
						int lettersOfLastWord = 0;
						while (phrase[(strlen(phrase)) - lettersOfLastWord] != ' ') {
							lettersOfLastWord++;
						}
						text.seekg(-(lettersOfLastWord), ios::cur);
						wordsInText--;
					}
				}
				textScore += tmpValue;
			}
			text.close();
			cout << argv[i] << " " << (double)textScore / wordsInText << endl;
		}
	}

	return 0;
}
