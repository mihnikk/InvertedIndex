#pragma once

#include <vector>
#include <set>
#include "ItemPosition.h"

struct IndexItem {
	char letter;
	std::vector<IndexItem*> nextItems;
	std::set<ItemPosition*> positions;

	IndexItem(char a) : letter(a) {}
	~IndexItem() {
		for (auto&& i : nextItems) {
			delete i;
		}
	}

	IndexItem* find(char a) {
		for (auto it = nextItems.begin(); it != nextItems.end(); ++it) {
			if ((*(*it)).letter == a) return *it;
		}
		return nullptr;
	}
};