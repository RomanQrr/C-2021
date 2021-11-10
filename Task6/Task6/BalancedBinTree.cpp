
#include "BalancedBinTree.h"

// ÏÐÈÂÀÒÍÛÅ

BalancedBinTree::Data* BalancedBinTree::copy(Data* p) {
	if (p == nullptr) return nullptr;
	Data* temp = new Data(p->key, p->value, copy(p->right), copy(p->left));
	return temp;
}

BalancedBinTree::Data* BalancedBinTree::remove(Data* p, std::string key) {
	if (!p) return 0;
	if (key < p->key)
		p->left = remove(p->left, key);
	else if (key > p->key)
		p->right = remove(p->right, key);
	else //  k == p->key 
	{
		if (p->value <= 1) {
			Data* q = p->left;
			Data* r = p->right;
			delete p;
			if (!r) return q;
			Data* min = findMin(r);
			min->right = removeMin(r);
			min->left = q;
			return balance(min);
		}
		else {
			p->value--;
		}
	}
	return balance(p);
}

int BalancedBinTree::findWord(std::string word, Data* p) const
{
	if (p == nullptr) return 0;
	if (p->key < word) { return findWord(word, p->right); }
	else if (p->key > word) { return findWord(word, p->left); }
	else return p->value;
}

BalancedBinTree::Data* BalancedBinTree::addWord(std::string word, Data* p)
{
	if (!p) return new Data(word, 1);
	if (word < p->key)
		p->left = addWord(word, p->left);
	else if (word > p->key)
		p->right = addWord(word, p->right);
	else if (word == p->key) { p->value++; }
	return balance(p);
}

BalancedBinTree::Data* BalancedBinTree::removeMin(Data* p)
{
	if (p->left == 0)
		return p->right;
	p->left = removeMin(p->left);
	return balance(p);
}

int BalancedBinTree::countWords(Data* p) const
{
	if (!p) return 0;
	return p->value + countWords(p->left) + countWords(p->right);
}


// ÑËÓÆÅÁÍÛÅ
BalancedBinTree::BalancedBinTree()
{
	root = nullptr;
}

BalancedBinTree::BalancedBinTree(const BalancedBinTree& binTree)
{
	root = copy(binTree.root);
}

BalancedBinTree::BalancedBinTree(BalancedBinTree&& binTree) noexcept
{
	root = binTree.root;
	binTree.root = nullptr;
}

BalancedBinTree& BalancedBinTree::operator=(const BalancedBinTree& binTree)
{
	if (this == &binTree) return *this;
	removeTree(root);
	root = copy(binTree.root);
	return *this;
}

BalancedBinTree& BalancedBinTree::operator=(BalancedBinTree&& binTree)
{
	if (this == &binTree) { return *this; }
	std::swap(root, binTree.root);
	return *this;
}

BalancedBinTree::Data* BalancedBinTree::balance(Data* p)
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateRight(p->right);
		return rotateLeft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateLeft(p->left);
		return rotateRight(p);
	}
	return p; // áàëàíñèðîâêà íå íóæíà
}

BalancedBinTree::Data* BalancedBinTree::rotateRight(Data* p)
{
	Data* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

BalancedBinTree::Data* BalancedBinTree::rotateLeft(Data* q)
{
	Data* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}


// ÈÑÏÎËÜÇÓÅÌÛÅ
int BalancedBinTree::findWord(std::string word) const
{
	return findWord(word, root);
}

void BalancedBinTree::addWord(std::string word)
{
	root = addWord(word, root);
}

void BalancedBinTree::removeWord(std::string key)
{
	root = remove(root, key);
}

int BalancedBinTree::countWordsWithIn() const
{
	return countWords(root);
}

void printOperator(std::ostream& out, BalancedBinTree::Data* p) {
	if (!p) return;
	printOperator(out, p->left);
	out << " " << p->key << " : " << p->value << " |";
	printOperator(out, p->right);
}

std::ostream& operator<<(std::ostream& out, const BalancedBinTree& binTree)
{
	if (binTree.root == nullptr) return out;
	printOperator(out, binTree.root->left);
	out << " " << binTree.root->key << " : " << binTree.root->value << " |";
	printOperator(out, binTree.root->right);
	return out;
}

void BalancedBinTree::levelPrint() const {
	levelPrint(root, 0);
}

void BalancedBinTree::levelPrint(Data* current, int level) const
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