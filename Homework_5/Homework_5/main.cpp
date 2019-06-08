/**
 *
 * Solution to homework task
 * Data Structures Course
 * Faculty of Mathematics and Informatics of Sofia University
 * Winter semester 2016/2017
 *
 * @author Stoicho Ganchev
 * @idnumber 45177
 * @task 5
 * @compiler VC
 *
 */
#include <iostream>
#include <fstream>
#include "binary_tree.h"
using namespace std;

int main()
{
	binaryTree<unsigned long long int>* initialTree;
	binaryTree<unsigned long long int>* resultTree;
	initialTree = new binaryTree<unsigned long long int>;
	int n = 0;
	cin >> n;

	ifstream file;
	do {
		char fname[32];
		cin.getline(fname, 32);
		file.open(fname, ios::binary);
	} while (!file.is_open());
	while (file.peek() != EOF) {
		unsigned long long int number;
		file.read((char*)&number, sizeof(number));
		initialTree->add(number);
	}
	file.close();

	for (int i = 1; i < n; i++) {
		resultTree = new binaryTree<unsigned long long int>;
		ifstream file;
		do {
			char fileName[32];
			cin.getline(fileName, 32);
			file.open(fileName, ios::binary);
		} while (!file.is_open());
		while (file.peek() != EOF) {
			unsigned long long int number;
			file.read((char*)&number, sizeof(number));
			if (initialTree->search(number)) {
				resultTree->add(number);
			}
		}
		file.close();
		delete initialTree;
		initialTree = resultTree;
	}

	ofstream ofile;
	ofile.open("result.bin", ios::binary);
	initialTree->save(ofile);
	ofile.close();
	delete initialTree;

	return 0;
}
