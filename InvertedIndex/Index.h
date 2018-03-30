#pragma once

#include <vector>
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
	vector<ItemPosition> find(const string& word);
private:
	vector<string> fileNames;
	vector<IndexItem*> items;
	IndexItem* findInItems(char ch);
};

