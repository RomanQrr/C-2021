#pragma once
#include <iostream>
class BinaryTree
	{
	private: // Хранение

		struct Data
		{
			std::string key;
			int value;

			Data* right;
			Data* left;

			Data(std::string key = "", int value = 0,
				Data* right = nullptr, Data* left = nullptr)
				: key(key), value(value), right(right), left(left)
			{}
		};

		Data* root;
		BinaryTree(Data* root) : root(root) {}

	public: // Служебные

		BinaryTree();
		BinaryTree(const BinaryTree& binTree);
		BinaryTree(BinaryTree&& binTree);

		BinaryTree& operator= (const BinaryTree& binTree);
		BinaryTree& operator= (BinaryTree&& binTree);

		~BinaryTree() { while (root) { /*remove(root); */ } }

	private: // 

		Data* copy(Data* p);
		void remove(Data* p);
		int findWord(std::string word, Data* p) const;
		bool addWord(std::string word, Data* p);
		void removeMin(std::string);
		int countWords(Data* p) const;
		void levelPrint(Data* current, int level) const;

	public: //

		int findWord(std::string word) const;
		void addWord(std::string word);
		void removeWord(std::string word);
		int countWordsWithIn() const;

		void levelPrint() const;

		friend std::ostream& operator << (std::ostream& out, const BinaryTree& binTree);
		friend void printOperator(std::ostream& out, Data* p);
	};


