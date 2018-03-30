// InvertedIndex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include <locale>

#include "Index.h"
#include "ItemPosition.h"

int main(int argc, char** argv)
{
	//setlocale(LC_ALL, "polish");
	if (argc < 1) {
		std::cout << "Usage: InvertedIndex <file>" << std::endl;
		return 1;
	}
	Index idx;
	idx.addFile(argv[1]);
	std::cout << "Wpisz s³owo, które chcesz znaleŸæ: ";
	for (std::string word; std::getline(std::cin, word); ) {
		if (word.size() == 0) continue;
		std::vector<ItemPosition> positions = idx.find(word);
		if (positions.empty()) {
			std::cout << "Nie znaleziono" << std::endl;
		}
		else {
			for (auto&& p : positions) {
				std::cout << "Plik " << &p.fileName << " linia " << p.lineNumber << std::endl;
			}
		}
		std::cout << "Wpisz s³owo, które chcesz znaleŸæ: ";
	}
    return 0;
}

