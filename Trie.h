//Evan Gordon
//some code inspiration was taken from http://theoryofprogramming.com/2015/01/16/trie-tree-implementation/
#include <string>
#include <vector>
#include <memory>
#include <iostream>

#pragma warning (disable:4351)

#define ALPHABET 26
#define AVALUE 'a'

struct Node
{
	bool isWord;
	Node*  p;
	std::unique_ptr<Node>  child[ALPHABET];

	Node::Node(Node* n): isWord(false), p(n), child() {}
	Node::~Node(){ p = NULL; }
};

class Trie
{
public:
	Trie();
	~Trie();
	void insert(std::string newWord);
	void findSubstr();
	void checkString(const std::string& word);

private:
	Node rt;
	int subCount;
	std::string longest, secLongest;

	void traverse(Node* curr, std::string& word);
	int backtrack(Node*& curr, std::vector<int> & cps, const std::string& word);
};