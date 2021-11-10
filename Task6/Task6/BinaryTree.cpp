#include "BinaryTree.h"

// ПРИВАТНЫЕ

BinaryTree::Data* BinaryTree::copy(Data* p) {
	if (p == nullptr) return nullptr;
	Data* temp = new Data(p->key, p->value, copy(p->right), copy(p->left));
	return temp;
}

void BinaryTree::remove(Data* p) {
	remove(p->left);
	remove(p->right);
	delete p;
}

int BinaryTree::findWord(std::string word, Data* p) const
{
	if (p == nullptr) return 0;
	if (p->key < word) { return findWord(word, p->right); }
	else if (p->key > word) { return findWord(word, p->left); }
	else return p->value;
}

bool BinaryTree::addWord(std::string word, Data* p)
{
	if (p == nullptr) return true;
	if (p->key > word && addWord(word, p->left)) {
		p->left = new Data(word, 1);
		return false;
	}
	else if (p->key < word && addWord(word, p->right)) {
		p->right = new Data(word, 1);
		return false;
	}
	else if (p->key == word) {
		p->value++; return false;
	}
	return false;
}

void BinaryTree::removeMin(std::string word)
{
	Data* curr = root;
	Data* parent = NULL;
	bool deletable = false;
	while (curr && curr->key != word)
	{
		parent = curr;
		if (curr->key > word) curr = curr->left;
		else curr = curr->right;
	}

	if (!curr)return;

	if (curr->left == NULL)
	{
		if (parent && parent->left == curr)
			parent->left = curr->right;
		if (parent && parent->right == curr)
			parent->right = curr->right;
		delete curr;
		return;
	}
	if (curr->right == NULL)
	{
		if (parent && parent->left == curr)
			parent->left = curr->left;
		if (parent && parent->right == curr)
			parent->left = curr->left;
		delete curr;
		return;
	}
	Data* replace = curr->right;
	while (replace->left)
		replace = replace->left;
	std::string replaceKey = replace->key;
	int replaceValue = replace->value;
	removeMin(replaceKey);
	curr->key = replaceKey;
	curr->value = replaceValue;
}

int BinaryTree::countWords(Data* p) const
{
	if (!p) return 0;
	return p->value + countWords(p->left) + countWords(p->right);
}


// СЛУЖЕБНЫЕ
BinaryTree::BinaryTree()
{
	root = nullptr;
}

BinaryTree::BinaryTree(const BinaryTree& binTree)
{
	root = copy(binTree.root);
}

BinaryTree::BinaryTree(BinaryTree&& binTree)
{
	root = binTree.root;
	binTree.root = nullptr;
}

BinaryTree& BinaryTree::operator=(const BinaryTree& binTree)
{
	if (this == &binTree) return *this;
	remove(root);
	root = copy(binTree.root);
	return *this;
}

BinaryTree& BinaryTree::operator=(BinaryTree&& binTree)
{
	if (this == &binTree) { return *this; }
	std::swap(root, binTree.root);
	return *this;
}


// ИСПОЛЬЗУЕМЫЕ
int BinaryTree::findWord(std::string word) const
{
	return findWord(word, root);
}

void BinaryTree::addWord(std::string word)
{
	if (root == nullptr) {
		root = new Data(word, 1);
		return;
	}
	addWord(word, root);
}

void BinaryTree::removeWord(std::string word)
{
	Data* curr = root;
	Data* parent = NULL;
	bool deletable = false;
	while (curr && curr->key != word)
	{
		parent = curr;
		if (curr->key > word) curr = curr->left;
		else curr = curr->right;
	}

	if (!curr)return;

	if (curr->value <= 1) {
		// Просто ставим поддерево, если одна ветка
		if (curr->left == NULL)
		{
			if (parent && parent->left == curr)
				parent->left = curr->right;
			if (parent && parent->right == curr)
				parent->right = curr->right;
			delete curr;
			return;
		}
		if (curr->right == NULL)
		{
			if (parent && parent->left == curr)
				parent->left = curr->left;
			if (parent && parent->right == curr)
				parent->left = curr->left;
			delete curr;
			return;
		}
		// Выбираем минимальный элемент и перемещаем его на место curr
		Data* replace = curr->right;
		while (replace->left)
			replace = replace->left;
		std::string replaceKey = replace->key;
		int replaceValue = replace->value;
		removeMin(replaceKey);
		curr->key = replaceKey;
		curr->value = replaceValue;
	}
	else {
		curr->value--;
	}
}

int BinaryTree::countWordsWithIn() const
{
	return countWords(root);
}

void printOperator(std::ostream& out, BinaryTree::Data* p) {
	if (!p) return;
	printOperator(out, p->left);
	out << " " << p->key << " : " << p->value << " |";
	printOperator(out, p->right);
}

std::ostream& operator<<(std::ostream& out, const BinaryTree& binTree)
{
	if (binTree.root == nullptr) return out;
	printOperator(out, binTree.root->left);
	out << " " << binTree.root->key << " : " << binTree.root->value << " |";
	printOperator(out, binTree.root->right);
	return out;
}

void BinaryTree::levelPrint() const {
	levelPrint(root, 0);
}

void BinaryTree::levelPrint(Data* current, int level) const
{
	if (current != nullptr) {
		for (int i = 0; i < level; i++) {
			std::cout << "\t";
		}
		std::cout << current->key << std::endl;
		level++;
		levelPrint(current->left, level);
		levelPrint(current->right, level);
	}
}