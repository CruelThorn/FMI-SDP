/**
 *
 * Solution to homework task
 * Data Structures Course
 * Faculty of Mathematics and Informatics of Sofia University
 * Winter semester 2016/2017
 *
 * @author Stoicho Ganchev
 * @idnumber 45177
 * @task Project
 * @compiler VC
 *
 */
#include <iostream>
#include <fstream>
#include <windows.h>
#include <cstring>
#include <stdio.h>
#include "Huffman_Tree.h"
#include "Priority_Queue.h"
#include "BitWriter.h"
using namespace std;

void _pack(char*, char*, char*);
void _unPack(char*, char*);
void _list(char*);
void newLine(char*);

int main()
{
	char command[16];
	do {
		cin >> command;
		if (!strcmp(command, "-Pack")) {
			char path[64];
			char name[64];
			char dir[1] = { '\0' };
			cin >> path;
			cin >> name;
			_pack(path, name, dir);
		}else if (!strcmp(command, "-Unpack")) {
			char path[64];
			char destination[64];
			cin >> path >> destination;
			_unPack(path, destination);
		}else if (!strcmp(command, "-List")) {
			char name[64];
			cin >> name;
			_list(name);
		}
	} while (strcmp(command, "-Exit"));
	return 0;
}

void _pack(char* path, char* fileName, char* dir)
{
	WIN32_FIND_DATA fd;
	char npath[64 + 4] = { '\0' };
	char ext[4] = { '*', '.', '*', '\0' };
	strcpy(npath, path);
	strcat(npath, ext);
	HANDLE hFind = ::FindFirstFile(npath, &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				cout << "Packing: " << fd.cFileName << " | ";
				ifstream ifile;
				char fullPath[64 + 64 + 1] = { '\0' };
				strcpy(fullPath, path);
				strcat(fullPath, fd.cFileName);
				ifile.open(fullPath, ios::binary);
				if (!ifile.is_open()) {
					cerr << "File could not be opened!\n";
					return;
				}else {
					//Pack the file name and new line
					ofstream ofile;
					ofile.open(fileName, ios::binary | ios::app);
					if (!ofile.is_open()) {
						cerr << "File could not be opened!\n";
						return;
					}else {
						for (unsigned int i = 0; i < strlen(fd.cFileName); i++) {
							ofile.write((char*)&fd.cFileName[i], sizeof(fd.cFileName[i]));
						}
					}
					ofile.close();
					newLine(fileName);
					//Handle empty files
					if (ifile.peek() == EOF) {
						ofstream sizenul;
						sizenul.open(fileName, ios::binary | ios::app);
						int nulsize = 0;
						//Size of tree is 0
						sizenul.write((char*)&nulsize, sizeof(nulsize));
						//Size of file is 0
						sizenul.write((char*)&nulsize, sizeof(nulsize));
						sizenul.close();
						cout << "Done!" << endl;
						return;
					}
					//Generate the Huffman tree for the file.
					HuffMan_Tree ht;
					int freq[256];
					for (int i = 0; i < 256; i++) {
						freq[i] = 0;
					}
					while (ifile.peek() != EOF) {
						char c;
						ifile.read((char*)&c, sizeof(c));
						freq[(int)c]++;
					}
					ifile.clear();
					ifile.seekg(0);
					priorityQueue<node> pq;
					for (int i = 0; i < 256; i++) {
						if (freq[i] != 0) {
							node* newNode = new node(i, freq[i]);
							pq.push(newNode, newNode->val);
						}
					}
					ht.buildTreeFromForest(pq);
					//Pack the Huffman tree and new line
					ofstream ostream;
					ostream.open(fileName, ios::binary | ios::app);
					if (ostream.is_open()) {
						int treeSizeNull = 0;
						ostream.write((char*)&treeSizeNull, sizeof(treeSizeNull));
						ht.save_tab(ostream);
					}else {
						cerr << "File could not be opened!\n";
						return;
					}
					ostream.close();
					fstream sizestream(fileName, ios::in | ios::out | ios::binary);
					int treeSize = ht.getTreeSize();
					sizestream.seekp(-treeSize - 4, ios::end);
					sizestream.write((char*)&treeSize, sizeof(treeSize));
					sizestream.close();
					//Set initial size of packed content to 0
					ofstream sizenul;
					sizenul.open(fileName, ios::binary | ios::app);
					int nulsize = 0;
					sizenul.write((char*)&nulsize, sizeof(nulsize));
					sizenul.close();
					//Pack file's content using the built Huffman tree
					while (ifile.peek() != EOF && ifile.peek() != '\n') {
						char reader[1024];
						reader[1023] = '\0';
						for (int i = 0; i < 1023; i++) {
							if (ifile.peek() == EOF || ifile.peek() == '\n') {
								reader[i] = '\0';
								break;
							}
							ifile.read((char*)&reader[i], sizeof(reader[i]));
						}
						ht.convert(reader, fileName);
					}
					//Write size of packed file content
					fstream fsize;
					fsize.open(fileName, ios::in | ios::out | ios::binary);
					int bytes = ht.getConvertedBytes();
					fsize.seekp(-bytes - 4, ios::end);
					fsize.write((char*)&bytes, sizeof(bytes));
					fsize.close();
				}
				ifile.close();
				cout << "Done!" << endl;
			}
			else {
				//                if(!strcmp(fd.cFileName, ".") && !strcmp(fd.cFileName, "..")) {
				//                    char delim[1] = {'\\'};
				//                    char fullPath[strlen(path) + strlen(fd.cFileName) + 2];
				//                    strcpy(fullPath, path);
				//                    strcat(fullPath, fd.cFileName);
				//                    strcat(fullPath, delim);
				//                    char newdir[strlen(dir) + strlen(fd.cFileName) + 2];
				//                    strcpy(newdir, dir);
				//                    strcat(newdir, fd.cFileName);
				//                    strcat(newdir, delim);
				//                    cout<<fd.cFileName;
				//                    _pack(fullPath, fileName, newdir);
				//                }
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
}

void _unPack(char* path, char* destination)
{
	ifstream ifile;
	ifile.open(path, ios::binary);
	if (!ifile.is_open()) {
		cerr << "Could not open the file!\n" << endl;
		return;
	}
	while (ifile.peek() != EOF) {
		char fileName[64];
		int treeSize = 0;
		int fileSize = 0;
		//Getting File Name
		for (int i = 0; i < 64; i++) {
			fileName[i] = '\0';
		}
		for (int i = 0; ifile.peek() != '\n'; i++) {
			ifile.read((char*)&fileName[i], sizeof(fileName[i]));
		}
		cout << "Unpacking: " << fileName << " | ";
		ifile.get();
		//Get tree size
		ifile.read((char*)&treeSize, sizeof(treeSize));
		//Build the Huffman tree
		HuffMan_Tree ht;
		ht.load_tab(ifile, treeSize);
		//Get file size
		ifile.read((char*)&fileSize, sizeof(fileSize));
		char fullPath[64];
		strcpy(fullPath, destination);
		strcat(fullPath, fileName);
		ofstream decode;
		decode.open(fullPath, ios::binary);
		if (!decode.is_open()) {
			cerr << "Could not create file!\n" << endl;
		}else {
			ht.decode(ifile, decode, fileSize);
		}
		decode.close();
		cout << "Done!" << endl;
	}
	ifile.close();
}

void _list(char* path)
{
	ifstream ifile;
	ifile.open(path, ios::binary);
	if (!ifile.is_open()) {
		cerr << "File could not be opened!\n";
		return;
	}else {
		while (ifile.peek() != EOF) {
			char fileName[64];
			int treeSize = 0;
			int fileSize = 0;
			for (int i = 0; i < 64; i++) {
				fileName[i] = '\0';
			}
			for (int i = 0; (char)ifile.peek() != '\n'; i++) {
				ifile.read((char*)&fileName[i], sizeof(fileName[i]));
			}
			ifile.get();
			ifile.read((char*)&treeSize, sizeof(treeSize));
			ifile.seekg(treeSize, ios::cur);
			ifile.read((char*)&fileSize, sizeof(fileSize));
			ifile.seekg(fileSize, ios::cur);
			cout << fileName << endl;
		}
	}
	ifile.close();
}

void newLine(char* fileName)
{
	ofstream ofile;
	ofile.open(fileName, ios::binary | ios::app);
	if (!ofile.is_open()) {
		cerr << "File could not be opened!\n";
		return;
	}else {
		char endLine = '\n';
		ofile.write((char*)&endLine, sizeof(endLine));
	}
	ofile.close();
}






