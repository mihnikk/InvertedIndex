#include "stdafx.h"
#include "Index.h"


Index::Index()
{
	allowed = { '!','@','#','$','%','^','-','+','=' };
}


Index::~Index()
{
	for (auto&& i : items) {
		delete i;
	}
}

void Index::addFile(const string& path) {
	string line;
	int lineNumber = 1;
	ifstream file(path);
	if (file.is_open()) {
		// czytanie znak po znaku
		char ch;
		IndexItem* item = 0;
		while (file >> noskipws >> ch) {
			//cout << ch;
			/*
			Dla ka¿dego znaku sprawdziæ:
			- czy jest alfanumeryczny, jeœli nie to:
				- jeœli jest ustawiony "item" to:
					- do jego "positions" dodajemy nowy ItemPosition
					- czyœcimy "item"
				- czy to koniec linii, jeœli tak to zwiêkszamy numer linii
			- jeœli to znak alfanumeryczny, to:
				- jeœli ustawiony "item", to szukamy w jego "nextItems" takiego znaku
					- jeœli jest to przestawiamy "item" na tamten
					- jeœli nie ma to dodajemy nowy IndexItem i dodajemy go do nextItems poprzedniego, po czym przestawiamy "item" na ten nowy
				- jeœli nie jest ustawiony "item", to szukamy takiego znaku w "items"
					- jeœli znaleziony, to ustawiamy "item" na odpowiedni element z "items"
					- jeœli nie znaleziony, to dodajemy nowy IndexItem, wstawiamy go do "items" i ustawiamy na niego "item"
			*/
			if (isalnum(ch, locale("polish")) || allowed.count(ch) > 0) {	// znak alfanumeryczny
				if (item != 0) {	// jeœli ustawiony "item"
					IndexItem* next = item->find(ch);	// szukamy w jego "nextItems" takiego znaku
					if (next != 0) {	// jeœli jest to przestawiamy "item" na tamten
						item = next;
					}
					else {	// jeœli nie ma to dodajemy nowy IndexItem i dodajemy go do nextItems poprzedniego
						IndexItem* n = new IndexItem(ch);
						item->nextItems.push_back(n);
						item = n;
					}
				}
				else {	// nie jest ustawiony "item", wiêc to poinien byæ pocz¹tek nowego s³owa
					// szukamy takiego znaku w "items"
					IndexItem* next = findInItems(ch);
					if (next != 0) {	// jeœli znaleziony, to ustawiamy "item" na odpowiedni element z "items"
						item = next;
					}
					else {	// jeœli nie znaleziony, to dodajemy nowy IndexItem, wstawiamy go do "items" i ustawiamy na niego "item"
						IndexItem* n = new IndexItem(ch);
						items.push_back(n);
						item = n;
					}
				}
			}
			else {	// to nie jest znak alfanumeryczny
				if (item != 0) {	// jeœli jest ustawiony "item" to:
					ItemPosition* pos = new ItemPosition(lineNumber, path);
					item->positions.insert(pos);
					item = 0;
				}
				if (ch == '\n') {	// koniec linii
					lineNumber++;
				}
			}
		}
		if (item != 0) {	// jeœli jest ustawiony "item" to:
			ItemPosition* pos = new ItemPosition(lineNumber, path);
			item->positions.insert(pos);
		}
		file.close();
		fileNames.push_back(path);
	}
}

set<ItemPosition*> Index::find(const string& word) {
	IndexItem* item = 0;
	char c;
	for (auto it = word.begin(); it != word.end(); ++it) {
		c = (*it);
		if (item == 0) {
			item = findInItems(c);
		}
		else {
			item = item->find(c);
		}
	}
	if (item != 0) {
		return item->positions;
	}
	else {
		return set<ItemPosition*>();
	}
}

IndexItem* Index::findInItems(char ch) {
	for (auto it = items.begin(); it != items.end(); ++it) {
		if ((*it)->letter == ch) return *it;
	}
	return nullptr;
}