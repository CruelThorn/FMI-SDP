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
#ifndef BINARY_TREE_H_INCLUDED
#define BINARY_TREE_H_INCLUDED
using namespace std;
template<class K, class D>
struct node
{
    node(K, D);
    ~node();

    node* left;
    node* right;

    K key;
    D data;
};

template<class K, class D>
node<K, D>::node(K _key, D _data)
{
    key = _key;
    data = _data;
    left = NULL;
    right = NULL;
}

template<class K, class D>
node<K, D>::~node()
{
    delete left;
    delete right;
}

//Binary Search Tree
template<class K, class D>
class binaryTree
{
public:
	binaryTree();
	~binaryTree();

	void add(K, D);
	bool remove(K, D);
	int removeall(K);
	bool search(K, D);
private:
	node<K, D>* root;
	node<K, D>* findMinInRight(node<K, D>*);
	node<K, D>* findMinInRightParent(node<K, D>*);
	node<K, D>* search(int);
};

template<class K, class D>
binaryTree<K, D>::binaryTree()
{
	root = NULL;
}

template<class K, class D>
binaryTree<K, D>::~binaryTree()
{
	delete root;
}

template<class K, class D>
void binaryTree<K, D>::add(K _key, D _data)
{
	node<K, D>* newNode = new node<K, D>(_key, _data);
	if (!root) {
		root = newNode;
	}else {
		node<K, D>* cur = root;
		while (true) {
			if (newNode->key == cur->key && newNode->data == cur->data) {
				return;
			}
			if (newNode->key < cur->key) {
				if (cur->left == NULL) {
					cur->left = newNode;
					return;
				}
				cur = cur->left;
			}else {
				if (cur->right == NULL) {
					cur->right = newNode;
					return;
				}
				cur = cur->right;
			}
		}
	}
}

template<class K, class D>
bool binaryTree<K, D>::search(K _key, D _data)
{
	node<K, D>* agent = new node<K, D>(_key, _data);
	node<K, D>* cur = root;
	while (cur) {
		if (cur->key == agent->key && cur->data == agent->data) {
			return true;
		}else if (agent->key < cur->key) {
			cur = cur->left;
		}else {
			cur = cur->right;
		}
	}
	return false;
}

template<class K, class D>
bool binaryTree<K, D>::remove(K _key, D _data)
{
	node<K, D>* junk = new node<K, D>(_key, _data);
	node<K, D>* cur = root;
	node<K, D>* parent = NULL;
	while (cur) {
		if (cur->key == junk->key && cur->data == junk->data) {
			break;
		}else if (junk->key < cur->key) {
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
	}else {
		//Delete node with no children
		if (cur->left == NULL && cur->right == NULL) {
			if (cur == root) {
				root = NULL;
			}
			else {
				if (parent->left == cur) {
					parent->left = NULL;
				}
				else if (parent->right == cur) {
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
			}else {
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
				node<K, D>* mir = findMinInRight(cur);
				node<K, D>* mirp = findMinInRightParent(cur);
				root = mir;
				mirp->left = mir->right;
				root->left = cur->left;
				cur->left = NULL;
				root->right = cur->right;
				cur->right = NULL;
				delete cur;
			}else {
				node<K, D>* mir = findMinInRight(cur);
				node<K, D>* mirp = findMinInRightParent(cur);
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

template<class K, class D>
int binaryTree<K, D>::removeall(K _key)
{
	int removedItems = 0;
	while (true) {
		node<K, D>* toRemove = search(_key);
		if (toRemove == NULL) {
			break;
		}else {
			remove(toRemove->key, toRemove->data);
			removedItems++;
		}
	}
	return removedItems;
}

template<class K, class D>
node<K, D>* binaryTree<K, D>::findMinInRight(node<K, D>* _root)
{
	node<K, D>* mir = _root->right;
	while (mir->left) {
		mir = mir->left;
	}
	return mir;
}

template<class K, class D>
node<K, D>* binaryTree<K, D>::findMinInRightParent(node<K, D>* _root)
{
	if (findMinInRight(_root) == _root->right) {
		return _root;
	}else {
		node<K, D>* mirp = _root->right;
		while (mirp->left->left) {
			mirp = mirp->left;
		}
		return mirp;
	}
}

template<class K, class D>
node<K, D>* binaryTree<K, D>::search(int _key)
{
	node<K, D>* cur = root;
	while (cur) {
		if (cur->key == _key) {
			return cur;
		}else if (_key < cur->key) {
			cur = cur->left;
		}else {
			cur = cur->right;
		}
	}
	return cur;
}

#endif // BINARY_TREE_H_INCLUDED