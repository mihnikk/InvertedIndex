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
			Dla ka�dego znaku sprawdzi�:
			- czy jest alfanumeryczny, je�li nie to:
				- je�li jest ustawiony "item" to:
					- do jego "positions" dodajemy nowy ItemPosition
					- czy�cimy "item"
				- czy to koniec linii, je�li tak to zwi�kszamy numer linii
			- je�li to znak alfanumeryczny, to:
				- je�li ustawiony "item", to szukamy w jego "nextItems" takiego znaku
					- je�li jest to przestawiamy "item" na tamten
					- je�li nie ma to dodajemy nowy IndexItem i dodajemy go do nextItems poprzedniego, po czym przestawiamy "item" na ten nowy
				- je�li nie jest ustawiony "item", to szukamy takiego znaku w "items"
					- je�li znaleziony, to ustawiamy "item" na odpowiedni element z "items"
					- je�li nie znaleziony, to dodajemy nowy IndexItem, wstawiamy go do "items" i ustawiamy na niego "item"
			*/
			if (isalnum(ch, locale("polish")) || allowed.count(ch) > 0) {	// znak alfanumeryczny
				if (item != 0) {	// je�li ustawiony "item"
					IndexItem* next = item->find(ch);	// szukamy w jego "nextItems" takiego znaku
					if (next != 0) {	// je�li jest to przestawiamy "item" na tamten
						item = next;
					}
					else {	// je�li nie ma to dodajemy nowy IndexItem i dodajemy go do nextItems poprzedniego
						IndexItem* n = new IndexItem(ch);
						item->nextItems.push_back(n);
						item = n;
					}
				}
				else {	// nie jest ustawiony "item", wi�c to poinien by� pocz�tek nowego s�owa
					// szukamy takiego znaku w "items"
					IndexItem* next = findInItems(ch);
					if (next != 0) {	// je�li znaleziony, to ustawiamy "item" na odpowiedni element z "items"
						item = next;
					}
					else {	// je�li nie znaleziony, to dodajemy nowy IndexItem, wstawiamy go do "items" i ustawiamy na niego "item"
						IndexItem* n = new IndexItem(ch);
						items.push_back(n);
						item = n;
					}
				}
			}
			else {	// to nie jest znak alfanumeryczny
				if (item != 0) {	// je�li jest ustawiony "item" to:
					ItemPosition* pos = new ItemPosition(lineNumber, path);
					item->positions.insert(pos);
					item = 0;
				}
				if (ch == '\n') {	// koniec linii
					lineNumber++;
				}
			}
		}
		if (item != 0) {	// je�li jest ustawiony "item" to:
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