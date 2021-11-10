// Task6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "BinaryTree.h"
#include "BalancedBinTree.h"

using namespace std;

int main()
{
	BalancedBinTree tree;
	string str("word");
	tree.addWord(str);
	str = "answer";
	tree.addWord(str);
	str = "begin";
	tree.addWord(str);
	tree.addWord(str);
	tree.levelPrint();
	cout << endl;
	cout << endl << tree;
	cout << endl << "Search word: begin = " << tree.findWord(str);
	str = "try";
	cout << endl << "Search word: try = " << tree.findWord(str);
	tree.addWord(str);
	str = "away";
	tree.addWord(str);
	str = "value";
	tree.addWord(str);
	tree.addWord(str);
	tree.addWord(str);
	tree.addWord(str);
	cout << endl << tree;
	cout << endl;
	tree.levelPrint();
	cout << endl << "Search word: value = " << tree.findWord(str);
	str = "book";
	tree.addWord(str);
	str = "mark";
	tree.addWord(str);
	str = "do";
	tree.addWord(str);
	str = "like";
	tree.addWord(str);
	tree.addWord(str);
	str = "economy";
	tree.addWord(str);
	str = "action";
	tree.addWord(str);
	str = "stock";
	tree.addWord(str);
	tree.addWord(str);
	tree.addWord(str);
	cout << endl << tree;
	cout << endl << "Quantity words = " << tree.countWordsWithIn() << endl;
	tree.levelPrint();
	cout << endl;
	str = "mark";
	tree.removeWord(str);
	cout << "Remove mark (2)";
	tree.removeWord(str);
	str = "value";
	tree.removeWord(str);
	tree.removeWord(str);
	tree.removeWord(str);
	tree.removeWord(str);
	cout << endl << tree << endl;
	tree.removeWord("do");
	tree.levelPrint();

	tree.removeWord("economy");
	tree.levelPrint();

	tree.removeWord("like");
	tree.removeWord("like");
	tree.levelPrint();

	tree.removeWord("try");
	tree.levelPrint();

	cout << endl << "Quantity words = " << tree.countWordsWithIn() << endl;

	BalancedBinTree tree2 = tree;
	tree.~BalancedBinTree();

	tree2.levelPrint();
}