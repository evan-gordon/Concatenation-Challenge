//Evan Gordon

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Trie.h"

//#include <vld.h>//visual link detector used for detecting memory leaks
//#pragma comment(linker, "/include:__imp_?g_vld@@3VVisualLeakDetector@@A")

std::string trimString(const std::string&  str)//change later to just using const refs, and then returning a substr
{
	if (str.size() == 0){ return ""; }

	int front = 0, back = 0;
	while (str.size() != 0 && isspace(str.front()))
	{
		front++;
	}

	while (str.size() != 0 && isspace(str.back()))
	{
		back++;
	}
	return str.substr(front, str.size() - back);
}

int main()
{
	Trie words;
	std::ifstream txtFile;
	std::string line;

	txtFile.open("wordsforproblem.txt");
	if (!txtFile)
	{
		std::cout << "Unable to open file, quitting.\n";
		return 0;
	}
	while (!txtFile.eof())
	{
		std::getline(txtFile, line);
		line = trimString(line);
		if (line.size() != 0){words.insert(line);}
	}
	txtFile.close();	

	words.findSubstr();
}