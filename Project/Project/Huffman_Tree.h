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
#ifndef HUFFMAN_TREE_H_INCLUDED
#define HUFFMAN_TREE_H_INCLUDED
#include <iostream>
#include <fstream>
#include "Priority_Queue.h"
#include "BitWriter.h"

struct node
{
	node();
	~node();
	node(char, int);

	char c;
	int val;
	node* left;
	node* right;
};

node::node()
{
	c = '\0';
	val = 0;
	left = NULL;
	right = NULL;
}

node::~node()
{
	delete left;
	delete right;
}

node::node(char _c, int _val)
{
	c = _c;
	val = _val;
	left = NULL;
	right = NULL;
}

//HUFFMAN TREE
class HuffMan_Tree
{
public:
	HuffMan_Tree();
	~HuffMan_Tree();

	void buildTreeFromForest(priorityQueue<node>&);
	void convert(char*, char*);
	void createTable(node*, char*);
	char* getCode(char);
	int getConvertedBytes() { return convertedBytes; }
	int getTreeSize() { return tree_size; }
	void decode(std::ifstream&, std::ofstream&, int);
	void save_tab(std::ofstream&);
	void save_tabb(std::ofstream&, node*);
	void load_tab(std::ifstream&, int);
	/************************FOR TESTING PURPOSES************************/
	//    void load(std::ifstream&);
	//    void save(std::ofstream&);
	//    void printCodes(node*, string);
	//    void print();
	//    void print_tab();
	/********************************************************************/
private:
	node* root;
	//void saveTree(std::ofstream&, node*, int);
	void loadTree(std::ifstream&, node*, char);
	char* code_table[256];
	int convertedBytes;
	int tree_size;
};

HuffMan_Tree::HuffMan_Tree()
{
	root = NULL;
	for (int i = 0; i < 256; i++) {
		code_table[i] = NULL;
	}
	convertedBytes = 0;
	tree_size = 0;
}

HuffMan_Tree::~HuffMan_Tree()
{
	delete root;
	for (int i = 0; i < 256; i++) {
		delete code_table[i];
	}
}

void HuffMan_Tree::buildTreeFromForest(priorityQueue<node>& pq)
{
	while (pq.hasNext()) {
		node* newNode = new node();
		newNode->left = pq.pop();
		newNode->right = pq.pop();
		newNode->val = newNode->left->val + newNode->right->val;
		pq.push(newNode, newNode->val);
	}
	root = pq.pop();
	char* start = new char[1];
	start[0] = '\0';
	createTable(root, start);
}

void HuffMan_Tree::createTable(node* _node, char* code)
{
	if (!_node) {
		delete code;
		return;
	}
	if (_node != NULL && _node->c != '\0') {
		code_table[(int)_node->c] = code;
	}
	char* left = new char[strlen(code) + 2];
	strcpy(left, code);
	left[strlen(code)] = '0';
	left[strlen(code) + 1] = '\0';
	createTable(_node->left, left);
	char* right = new char[strlen(code) + 2];
	strcpy(right, code);
	right[strlen(code)] = '1';
	right[strlen(code) + 1] = '\0';
	createTable(_node->right, right);
}

char* HuffMan_Tree::getCode(char letter)
{
	return code_table[(int)letter];
}

void HuffMan_Tree::loadTree(std::ifstream& istr, node* _node, char reader)
{
	if ((_node->left != NULL && _node->right != NULL) || _node->c != '\0' || reader == '\n') {
		return;
	}
	if (reader != '0' && reader != '1') {
		_node->c = reader;
		istr.read((char*)&reader, sizeof(reader));
		loadTree(istr, _node, reader);
	}
	if (reader == '0') {
		if ((_node->left != NULL && _node->right != NULL) || _node->c != '\0') {
			return;
		}
		_node->left = new node();
		istr.read((char*)&reader, sizeof(reader));
		loadTree(istr, _node->left, reader);

	}
	if (reader == '1') {
		if ((_node->left != NULL && _node->right != NULL) || _node->c != '\0') {
			return;
		}
		_node->right = new node();
		istr.read((char*)&reader, sizeof(reader));
		loadTree(istr, _node->right, reader);

	}
}

void HuffMan_Tree::decode(std::ifstream& istr, std::ofstream& ostr, int fileSize)
{
	if (fileSize == 0) {
		return;
	}
	char buffer;
	node* tmp = root;
	while (fileSize > 0) {
		istr.read((char*)&buffer, sizeof(buffer));
		fileSize--;
		for (int i = 0; i < 8; i++) {
			if (tmp->c != '\0') {
				ostr.write((char*)&tmp->c, sizeof(tmp->c));
				tmp = root;
			}
			int nextBit = buffer & 128;
			buffer = buffer << 1;
			if (nextBit == 0) {
				tmp = tmp->left;
			}else {
				tmp = tmp->right;
			}
		}
	}
}

void HuffMan_Tree::load_tab(std::ifstream& istr, int treeSize)
{
	if (treeSize <= 0) {
		return;
	}
	int freq[256];
	for (int i = 0; i < 256; i++) {
		freq[i] = 0;
	}
	while (treeSize > 0) {
		char c;
		int fr;
		istr.read((char*)&c, sizeof(c));
		treeSize--;
		istr.read((char*)&fr, sizeof(fr));
		treeSize -= 4;
		freq[(int)c] = fr;
	}
	priorityQueue<node> pq;
	for (int i = 0; i < 256; i++) {
		if (freq[i] != 0) {
			node* newNode = new node(i, freq[i]);
			pq.push(newNode, newNode->val);
		}
	}
	buildTreeFromForest(pq);
}

void HuffMan_Tree::save_tab(std::ofstream& ostr)
{
	save_tabb(ostr, root);
}

void HuffMan_Tree::save_tabb(std::ofstream& ostr, node* _node)
{
	if (!_node) {
		return;
	}
	if (_node != NULL && _node->c != '\0') {
		ostr.write((char*)&_node->c, sizeof(_node->c));
		tree_size++;
		ostr.write((char*)&_node->val, sizeof(_node->val));
		tree_size += 4;
	}
	save_tabb(ostr, _node->left);
	save_tabb(ostr, _node->right);
}

void  HuffMan_Tree::convert(char* text, char* fileName)
{
	std::ofstream file;
	BitWriter bw(file);
	file.open(fileName, std::ios::binary | std::ios::app);
	if (!file.is_open()) {
		std::cerr << "File " << fileName << " could not be opened!\n";
		return;
	}else {
		for (int i = 0; text[i] != '\0'; i++) {
			char* code = getCode(text[i]);
			bw.write(code);
		}
	}
	file.close();
	convertedBytes += bw.getFileSizeInBytes();
}

/************************FOR TESTING PURPOSES************************/
//void HuffMan_Tree::printCodes(node* _node, string str)
//{
//    if (!_node){
//        return;
//    }
//    if (_node != NULL && _node->c != '\0'){
//        cout << _node->c << ": " << str << "\n";
//    }
//    printCodes(_node->left, str + "0");
//    printCodes(_node->right, str + "1");
//}
//
//void HuffMan_Tree::print()
//{
//    printCodes(root, "");
//}
//
//void HuffMan_Tree::print_tab()
//{
//    for(int i = 0; i<256; i++){
//        if(code_table[i] != NULL){
//            cout<<(char)i<<" "<<code_table[i]<<endl;
//        }
//    }
//}
//
//void HuffMan_Tree::load(std::ifstream& istr)
//{
//    root = new node();
//    char reader;
//    istr.read((char*)&reader, sizeof(reader));
//    loadTree(istr, root, reader);
//}
//
//void HuffMan_Tree::save(std::ofstream& ostr)
//{
//    saveTree(ostr, root, -1);
//}
//
//void HuffMan_Tree::saveTree(std::ofstream& ostr, node* _node, int from)
//{
//    if (!_node){
//        return;
//    }
//    char left = '0';
//    char right = '1';
//    if(from == 0){
//        ostr.write((char*)&left, sizeof(left));
//        tree_size++;
//    }else if(from == 1){
//        ostr.write((char*)&right, sizeof(right));
//        tree_size++;
//    }
//    if (_node != NULL && _node->c != '\0'){
//        ostr.write((char*)&_node->c, sizeof(_node->c));
//        tree_size++;
//    }
//    saveTree(ostr, _node->left, 0);
//    saveTree(ostr, _node->right, 1);
//}
/********************************************************************/

#endif // HUFFMAN_TREE_H_INCLUDED
