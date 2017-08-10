#include "a3v2.h"
#include <string>
#include <iostream>
using namespace std;

SpellCheck::SpellCheck(string data[],int sz) {
	max_ = sz * 6;
	size_ = 0;
    vect_ = new string[max_];
	for(size_t i = 0; i < sz; addWord(data[i++]));
}

void SpellCheck::addWord(const string& newWord){
	size_t i = 0;
	for(; i < size_; i++) {
		if(vect_[i].empty() || vect_[i] > newWord){
			break;
		} else if(vect_[i] == newWord) {
			return;
		}
	}

	if(size_ == max_ - 1) {
		string* tmp = new string[max_ * 2];
		for(size_t j = 0; j < max_; j++) {
			tmp[j] = vect_[j];
		}
		max_ *= 2;
		delete[] vect_;
		vect_ = tmp;
	}
     //on matrix, size_ misteriously goes high after 6000
	for(size_t j = size_; j > i; j--) {
		vect_[j] = vect_[j - 1];
	}
	vect_[i] = newWord;
	++size_;
}
bool SpellCheck::lookup(const string& word) const{
    size_t l = 0;
	size_t h = size_ - 1;
	while(l <= h) {
		size_t m = (l + h) / 2;
		if(word < vect_[m]) {
			h = m - 1;
		}
		else if(word > vect_[m]) {
			l = m + 1;
		}
		else {
			return true;
		}
	}
	return false;
}
int SpellCheck::suggest(const string& partialWord, string suggestions[]) const{
	size_t length = partialWord.length();
	// size_t l = 0;
	// size_t h = size_ - 1;
	// while(l <= h) {
	// 	size_t m = (l + h) / 2;
	// 	if(partialWord < vect_[m].substr(0, length)) {
	// 		h = m - 1;
	// 	}
	// 	else if(partialWord > vect_[m].substr(0, length)) {
	// 		l = m + 1;
	// 	}
	// 	else {
	// 		for(; vect_[m].substr(0, length) == partialWord; m--);
	// 		m += 1;
	// 		for(l = 0; vect_[m].substr(0, length) == partialWord; suggestions[l++] = vect_[m++]);
	// 		return l;
	// 	}
	// }
	// return 0;
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@\n";
	//size_ = 233428;
	for(size_t i = 0; i < size_; i++) {
		cout << size_ << " **\n";
		if(vect_[i].substr(0, length) == partialWord) {
			cout << "--------------------------" << endl;
			size_t j = 0;
			for(; vect_[i].substr(0, length) == partialWord; suggestions[j++] = vect_[i++]);
			return j;
		} else {
			cout << partialWord << " *** " << vect_[i] << " *** " << vect_[i].substr(0, length) << endl;
		}
	}
	return 0;
}
SpellCheck::~SpellCheck(){
	delete[] vect_;
}
