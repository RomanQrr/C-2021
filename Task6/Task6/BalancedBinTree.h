#pragma once
#include <iostream>


class BalancedBinTree
{
private: // Хранение

	struct Data
	{
		std::string key;
		int value;
		unsigned char height = 1;

		Data* right;
		Data* left;

		Data(std::string key = "", int value = 0,
			Data* right = nullptr, Data* left = nullptr)
			: key(key), value(value), right(right), left(left)
		{}
	};

	Data* root;
	BalancedBinTree(Data* root) : root(root) {}
	void removeTree(Data* p) {
		if (!p) return;
		removeTree(p->left);
		removeTree(p->right);
	}

public: // Служебные

	BalancedBinTree();
	BalancedBinTree(const BalancedBinTree& binTree);
	BalancedBinTree(BalancedBinTree&& binTree) noexcept;

	BalancedBinTree& operator= (const BalancedBinTree& binTree);
	BalancedBinTree& operator= (BalancedBinTree&& binTree);

	~BalancedBinTree() { removeTree(root); }

private: // Баланс

	Data* balance(Data* p);
	unsigned char height(Data* p) { return p ? p->height : 0; }
	int bfactor(Data* p) { return height(p->right) - height(p->left); }
	Data* rotateRight(Data* p);
	Data* rotateLeft(Data* q);

	void fixheight(Data* p) {
		unsigned char hl = height(p->left);
		unsigned char hr = height(p->right);
		p->height = (hl > hr ? hl : hr) + 1;
	}

private: // 

	Data* copy(Data* p);
	int findWord(std::string word, Data* p) const;
	Data* addWord(std::string word, Data* p);
	Data* remove(Data* p, std::string key);
	Data* removeMin(Data* p);
	Data* findMin(Data* p) { return p->left ? findMin(p->left) : p; }
	int countWords(Data* p) const;
	void levelPrint(Data* current, int level) const;

public: //

	int findWord(std::string word) const;
	void addWord(std::string word);
	void removeWord(std::string key);
	int countWordsWithIn() const;

	void levelPrint() const;

	friend std::ostream& operator << (std::ostream& out, const BalancedBinTree& binTree);
	friend void printOperator(std::ostream& out, Data* p);
};

