//Evan Gordon

#include "Trie.h"

Trie::Trie() : rt(NULL), longest(), secLongest(), subCount(0){}

void Trie::insert(std::string newWord)
{
	auto curr = &rt;
	for (auto it = newWord.begin(); it != newWord.end(); it++)
	{
		if (curr->child[(*it) - AVALUE] == NULL)
		{
			curr->child[(*it) - AVALUE] = std::unique_ptr<Node>(new Node(curr));
		}

		curr = curr->child[(*it) - AVALUE].get();

		if (it + 1 == newWord.end()){curr->isWord = true;}
	}
	curr = NULL;
}

void Trie::findSubstr()
{
	auto curr = &rt;
	std::string word;

	traverse(curr, word);

	std::cout << "Longest word: " << longest << " with length of " << longest.size() 
				<< "\nSecond longest word: " << secLongest << " with length of " << secLongest.size() 
					<< "\nNumber of Concatenated words: " << subCount << "\n";
	curr = NULL;
}

//recursive in depth first in order traversal starting at the root node
void Trie::traverse(Node* curr, std::string& word)
{
	if (curr->isWord){ checkString(word); }
	
	for (int i = 0; i < ALPHABET; i++)
	{
		if (curr->child[i] != NULL)
		{
			word += (char)(i + AVALUE);
			traverse(curr->child[i].get(), word);
			word.pop_back();//remove last character
		}
	}
}

void Trie::checkString(const std::string& word)
{
	std::vector<int> checkPoints;//indecies of substrings
	checkPoints.push_back(0);
	auto curr = &rt;

	for (auto it = word.begin(); it != word.end(); it++)
	{
		curr = curr->child[(*it) - AVALUE].get();

		if (curr == NULL)
		{
			it = backtrack(curr, checkPoints, word) + word.begin();
		}
		else if (curr->isWord)//word exists in current context
		{
		    checkPoints.push_back(it - word.begin() + 1);
			curr = &rt;
		}
		else if ((int)(it - word.begin()) + 1 >= (int)word.size())//end of word not concat
		{
		    it = backtrack(curr, checkPoints, word) + word.begin();
		}
	}

	if (checkPoints.size() > 2)//substrings found
	{
		if (word.size() >= longest.size())
		{
			secLongest = longest;
			longest = word;
		}
		else if (word.size() >= secLongest.size())
		{
			secLongest = word;
		}
		subCount++; 
	}
	curr = NULL;
}

//previous concatination combination was invalid, try another from the end of previous selection
//return string index for location after previous end
int Trie::backtrack(Node*& curr, std::vector<int> & cps, const std::string& word)
{
	if (cps.size() > 1)
	{
		int prevCheckpoint = cps.at(cps.size() - 1);
		int prevStart = cps.at(cps.size() - 2);//previous start postition
		curr = &rt;
		for (int i = prevStart; i < prevCheckpoint; i++)//move to position just after prev concat
		{
			curr = curr->child[word.at(i) - AVALUE].get();
		}
		cps.pop_back();
		return prevCheckpoint - 1;
	}
	return 0;
}

Trie::~Trie(){}