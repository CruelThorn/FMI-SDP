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
#ifndef BINARY_TREE_H_INCLUDED
#define BINARY_TREE_H_INCLUDED

#include <fstream>

template<class T>
struct node
{
	node(T);
	~node();

	node* left;
	node* right;

	T data;
};

template<class T>
node<T>::node(T _data)
{
	data = _data;
	left = NULL;
	right = NULL;
}

template<class T>
node<T>::~node()
{
	delete left;
	delete right;
}

//Binary Search Tree
template<class T>
class binaryTree
{
public:
	binaryTree();
	~binaryTree();

	void add(T);
	bool remove(T);
	bool search(T);
	void save(std::ofstream&);
private:
	node<T>* root;
	node<T>* findMinInRight(node<T>*);
	node<T>* findMinInRightParent(node<T>*);
	void write(std::ofstream&, node<T>*);
	int getHeight(node<T>*);
	int b_factor(node<T>*);
	node<T>* balance(node<T>*);
	node<T>* rr_rotation(node<T>*);
	node<T>* ll_rotation(node<T>*);
	node<T>* rl_rotation(node<T>*);
	node<T>* lr_rotation(node<T>*);
};

template<class T>
binaryTree<T>::binaryTree()
{
	root = NULL;
}

template<class T>
binaryTree<T>::~binaryTree()
{
    delete root;
}

template<class T>
void binaryTree<T>::add(T val)
{
	node<T>* newNode = new node<T>(val);
	if (!root) {
		root = newNode;
	}
	else {
		node<T>* cur = root;
		while (true) {
			if (newNode->data == cur->data) {
				return;
			}if (newNode->data < cur->data) {
				if (cur->left == NULL) {
					cur->left = newNode;
					root = balance(root);
					return;
				}
				cur = cur->left;
			}else {
				if (cur->right == NULL) {
					cur->right = newNode;
					root = balance(root);
					return;
				}
				cur = cur->right;
			}
		}
	}
}

template<class T>
bool binaryTree<T>::search(T val)
{
	node<T>* agent = new node<T>(val);
	node<T>* cur = root;
	while (cur) {
		if (cur->data == agent->data) {
			return true;
		}else if (agent->data < cur->data) {
			cur = cur->left;
		}else {
			cur = cur->right;
		}
	}
	return false;
}

template<class T>
bool binaryTree<T>::remove(T val)
{
	node<T>* junk = new node<T>(val);
	node<T>* cur = root;
	node<T>* parent = NULL;
	while (cur) {
		if (cur->data == junk->data) {
			break;
		}else if (junk->data < cur->data) {
			parent = cur;
			cur = cur->left;
		}else {
			parent = cur;
			cur = cur->right;
		}
	}
	delete junk;
	if (!cur) {
		return false;
	}
	//Delete node with no children
	else {
		if (cur->left == NULL && cur->right == NULL) {
			if (cur == root) {
				root = NULL;
			}
			else {
				if (parent->left == cur) {
					parent->left = NULL;
				}else if (parent->right == cur) {
					parent->right = NULL;
				}
			}
			delete cur;
			return true;
		}
		//Delete node with right child only
		else if (cur->left == NULL && cur->right != NULL) {
			if (cur == root) {
				root = root->right;
				cur->right = NULL;
				delete cur;
			}
			else {
				if (cur == parent->left) {
					parent->left = cur->right;
				}else {
					parent->right = cur->right;
				}
				cur->right = NULL;
				delete cur;
			}
			return true;
		}
		//Delete node with left child only
		else if (cur->left != NULL && cur->right == NULL) {
			if (cur == root) {
				root = root->left;
				cur->left = NULL;
				delete cur;
			}else {
				if (cur == parent->left) {
					parent->left = cur->left;
				}else {
					parent->right = cur->left;
				}
				cur->left = NULL;
				delete cur;
			}
			return true;
		}
		//Delete node with two children
		else if (cur->left != NULL && cur->right != NULL) {
			if (cur == root) {
				node<T>* mir = findMinInRight(cur);
				node<T>* mirp = findMinInRightParent(cur);
				root = mir;
				mirp->left = mir->right;
				root->left = cur->left;
				cur->left = NULL;
				root->right = cur->right;
				cur->right = NULL;
				delete cur;
			}else {
				node<T>* mir = findMinInRight(cur);
				node<T>* mirp = findMinInRightParent(cur);
				if (cur == parent->right) {
					parent->right = mir;
				}else {
					parent->left = mir;
				}
				mir->left = cur->left;
				cur->left = NULL;
				if (cur->right != mir) {
					mirp->left = mir->right;
					mir->right = cur->right;
				}
				cur->right = NULL;
				delete cur;
			}
			return true;
		}
	}
}

template<class T>
node<T>* binaryTree<T>::findMinInRight(node<T>* _root)
{
	node<T>* mir = _root->right;
	while (mir->left) {
		mir = mir->left;
	}
	return mir;
}

template<class T>
node<T>* binaryTree<T>::findMinInRightParent(node<T>* _root)
{
	if (findMinInRight(_root) == _root->right) {
		return _root;
	}else {
		node<T>* mirp = _root->right;
		while (mirp->left->left) {
			mirp = mirp->left;
		}
		return mirp;
	}
}

template<class T>
void binaryTree<T>::save(std::ofstream& file)
{
	write(file, root);
}

template<class T>
void binaryTree<T>::write(std::ofstream& file, node<T>* _node)
{
	if (_node) {
		file.write((char*)&_node->data, sizeof(_node->data));
	}
	if (_node->left) {
		write(file, _node->left);
	}
	if (_node->right) {
		write(file, _node->right);
	}
}


template<class T>
node<T>* binaryTree<T>::rr_rotation(node<T>* _node)
{
	node<T>* tmp;
	tmp = _node->right;
	_node->right = tmp->left;
	tmp->left = _node;
	return tmp;
}

template<class T>
node<T>* binaryTree<T>::ll_rotation(node<T>* _node)
{
	node<T>* tmp;
	tmp = _node->left;
	_node->left = tmp->right;
	tmp->right = _node;
	return tmp;
}

template<class T>
node<T>* binaryTree<T>::lr_rotation(node<T>* _node)
{
    node<T>* tmp;
    tmp = _node->left;
    _node->left = rr_rotation (tmp);
    return ll_rotation (_node);
}

template<class T>
node<T>* binaryTree<T>::rl_rotation(node<T>* _node)
{
    node<T>* tmp;
    tmp = _node->right;
    _node->right = ll_rotation (tmp);
    return rr_rotation (_node);
}

template<class T>
int binaryTree<T>::getHeight(node<T>* _node) {
	int height = 0;
	if (_node) {
		int left = getHeight(_node->left);
		int right = getHeight(_node->right);
		if (left < right) {
			height = right + 1;
		}else {
			height = left + 1;
		}
	}
	return height;
}

template<class T>
int binaryTree<T>::b_factor(node<T>* _node) {
	int left = getHeight(_node->left);
	int right = getHeight(_node->right);
	int b_factor = (left - right);
	return b_factor;
}

template<class T>
node<T>* binaryTree<T>::balance(node<T>* _node) {
	int bal = b_factor(_node);
	if (bal > 1) {
		if (b_factor(_node->left) > 0) {
			_node = ll_rotation(_node);
		}else {
			_node = lr_rotation(_node);
		}
	}else if (bal < -1) {
		if (b_factor(_node->right) > 0) {
			_node = rl_rotation(_node);
		}else {
			_node = rr_rotation(_node);
		}
	}
	return _node;
}

#endif // BINARY_TREE_H_INCLUDED
