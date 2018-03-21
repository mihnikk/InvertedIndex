// InvertedIndex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>

int main(int argc, char** argv)
{
	if (argc == 1) {
		// createIndex
	}
	else {
		std::cout << "Usage: InvertedIndex <index file> [<list file>]" << std::endl;
		return 1;
	}
	for (std::string word; std::getline(std::cin, word); ) {
		// search(word)
		std::cout << word << std::endl;
	}
    return 0;
}

