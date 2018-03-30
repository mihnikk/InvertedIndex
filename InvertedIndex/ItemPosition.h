#pragma once

#include <string>

struct ItemPosition {
	ItemPosition(int l, const std::string& file) : lineNumber(l), fileName(file) {}
	int lineNumber;
	const std::string fileName;
};