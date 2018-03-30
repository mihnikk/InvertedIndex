#pragma once

#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <iostream>
//#include <cctype>
#include <locale>
#include "ItemPosition.h"
#include "IndexItem.h"

using namespace std;

class Index
{
public:
	Index();
	~Index();
	void addFile(const string& path);
	set<ItemPosition*> find(const string& word);
private:
	vector<string> fileNames;
	vector<IndexItem*> items;
	IndexItem* findInItems(char ch);
	set<char> allowed;
};

