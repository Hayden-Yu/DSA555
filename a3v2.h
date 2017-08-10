#ifndef A3_V2_H
#define A3_V2_H
#include <string>
using namespace std;

class SpellCheck{
		string* vect_;
		size_t max_;
		size_t size_;
public:
	SpellCheck(string data[],int sz);
	void addWord(const string& newWord);
	bool lookup(const string& word) const;
	int suggest(const string& partialWord, string suggestions[]) const;
	~SpellCheck();
};
#endif
