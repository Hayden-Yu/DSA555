#include "a3v2.h"
#include <string>
#include <iostream>
using namespace std;

SpellCheck::SpellCheck(string data[],int sz) {
	dict_ = new DList[26];
	for(size_t i = 0; i < sz; addWord(data[i++]));
}

void SpellCheck::addWord(const string& newWord){
	dict_[newWord[0] - 'a'].insert(newWord);
}
bool SpellCheck::lookup(const string& word) const{
    return dict_[word[0] - 'a'].search(word) != dict_[word[0] - 'a'].end();
}
int SpellCheck::suggest(const string& partialWord, string suggestions[]) const{
	int category = partialWord[0] - 'a';
	DList::const_iterator itor = dict_[category].partialSearch(partialWord);
	int sz = 0;
	for(; itor != dict_[category].end() && (*itor).substr(0, partialWord.size()) == partialWord; itor++) {
		suggestions[sz++] = (*itor);
	}
	return sz;
}
SpellCheck::~SpellCheck(){
	delete[] dict_;
}
