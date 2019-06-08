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
#ifndef TRIE_H_INCLUDED
#define TRIE_H_INCLUDED

const int ALPHABET = 27;

struct node
{
	node();
	~node();
	node* letters[ALPHABET];
	bool isEndOfWord;
	int value;
};

node::node()
{
	for (int i = 0; i < ALPHABET; i++) {
		letters[i] = NULL;
	}
	isEndOfWord = false;
	value = 0;
}

node::~node()
{
	for (int i = 0; i < ALPHABET; i++) {
		if (letters[i] != NULL) {
			delete letters[i];
		}
	}
}

class Trie
{
public:
	Trie();
	~Trie();

	void Add(const char*, const int);
	int findScore(const char*) const;
	bool hasLongerPhrase(const char*) const;
private:
	node* root;
};

Trie::Trie()
{
	root = new node();
}

Trie::~Trie()
{
    delete root;
}

void Trie::Add(const char* word, const int value)
{
	node* pCurrent = root;
	for (int i = 0; word[i] != '\0'; i++) {
		if (word[i] == ' ') {
			if (pCurrent->letters[26] == NULL) {
				pCurrent->letters[26] = new node();
			}
			pCurrent = pCurrent->letters[26];
		}else {
			if (pCurrent->letters[word[i] - 'a'] == NULL) {
				pCurrent->letters[word[i] - 'a'] = new node();
			}
			pCurrent = pCurrent->letters[word[i] - 'a'];
		}
	}
	pCurrent->isEndOfWord = true;
	pCurrent->value = value;
}

int Trie::findScore(const char* word) const
{
	node* pCurrent = root;
	for (int i = 0; word[i] != '\0'; i++) {
		if ((pCurrent->letters[26] == NULL && word[i] == ' ') || pCurrent->letters[word[i] - 'a'] == NULL) {
			return 0;
		}else {
			if (word[i] == ' ') {
				pCurrent = pCurrent->letters[26];
			}else {
				pCurrent = pCurrent->letters[word[i] - 'a'];
			}
		}
	}
	if (pCurrent->isEndOfWord) {
		return pCurrent->value;
	}else {
		return 0;
	}
}

bool Trie::hasLongerPhrase(const char* word) const
{
	node* pCurrent = root;
	for (int i = 0; word[i] != '\0'; i++) {
		if ((pCurrent->letters[26] == NULL && word[i] == ' ') || pCurrent->letters[word[i] - 'a'] == NULL) {
			return false;
		}else {
			if (word[i] == ' ') {
				pCurrent = pCurrent->letters[26];
			}else {
				pCurrent = pCurrent->letters[word[i] - 'a'];
			}
		}
	}
	if (pCurrent->letters[26] != NULL) {
		return true;
	}else {
		return false;
	}
}

#endif // TRIE_H_INCLUDED
