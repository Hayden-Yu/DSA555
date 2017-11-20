#include "a3.h"
#include <string>
#include<iostream>
using namespace std;


SpellCheck::SpellCheck(string data[],int sz) {
	root_ = new Node();
	for(int i =0; i < sz; addWord(data[i++]));
}

void SpellCheck::addWord(const string& newWord) {
	Node* ptr = root_;
	int i;
	for(i = 0; i < newWord.length() - 1; i++) {
		ptr = ptr->push(newWord[i]);
	}
	ptr->push(newWord[i], true);
}

bool SpellCheck::lookup(const string& word) const{
	Node* ptr = root_;
	int i;
	for(i = 0; i < word.length(); i++) {
		if(!(ptr = ptr->getChild(word[i]))) {
			return false;
		}
	}
	return ptr->terminate();
}

void SpellCheck::suggest(string partialWord, string*& suggestions, int& size, Node* ptr) const {
	partialWord += ptr->getLetter();

	if(ptr->terminate()) { //another word found
		suggestions[size++] = partialWord;
	}

	//continue with children nodes
	for(int i = 0; i < 26; i++) {
		if((*ptr)[i]) {
			suggest(partialWord, suggestions, size, (*ptr)[i]);
		}
	}
}

int SpellCheck::suggest(const string& partialWord, string suggestions[]) const{
	Node* ptr = root_;
	int ret = 0;
	for(int i = 0; i < partialWord.length(); i++) {
		if(!(ptr = ptr->getChild(partialWord[i]))) {
			return 0;
		}
	}

	suggest(partialWord.substr(0, partialWord.length() -1), suggestions, ret, ptr);
	return ret;
}
SpellCheck::~SpellCheck(){
	delete root_; //Node destructor will take care of the rest
}
