/**
 *
 * Solution to homework task
 * Data Structures Course
 * Faculty of Mathematics and Informatics of Sofia University
 * Winter semester 2016/2017
 *
 * @author Stoicho Ganchev
 * @idnumber 45177
 * @task 4
 * @compiler VC
 *
 */
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "Binary_Tree.h"
using namespace std;

int main(int argc, char* argv[])
{
	binaryTree<int, string> binary_tree;

	ifstream file;
	file.open(argv[1], ios::binary);
	while (file.peek() != EOF) {
		int key = 0;
		int data_length;
		file.read((char*)&key, sizeof(key));
		file.read((char*)&data_length, sizeof(data_length));
		char* data = new char[data_length];
		file.read((char*)&data, sizeof(data_length));
		data[data_length] = '\0';
		string dataStr = "";
		if (data != NULL) {
			dataStr.assign(data);
		}
		binary_tree.add(key, dataStr);
		delete[]data;
	}

	return 0;
}
