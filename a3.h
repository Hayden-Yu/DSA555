#ifndef A3_H
#define A3_H
#include <string>
using namespace std;
class SpellCheck{
	class Node {
		char letter_;
		bool term_;
		Node* children_[26];
	public:
		Node() : children_(), letter_(0), term_(false) {
		}

		Node(char letter, bool terminate = false) : children_() {
			letter_ = letter;
			term_ = terminate;
		}

		~Node() {
			for(Node* n : children_) {
				delete n;
			}
		}

		char getLetter() const{
			return letter_;
		}

		Node* getChild(char letter) {
			return children_[letter - 'a'];
		}

		Node* push(char letter, bool terminate = false) {
			int idx = letter - 'a'; //find index from ascii value
			if(!children_[idx]) {
				children_[idx] = new Node(letter, terminate);
			} else if(terminate) {
				children_[idx]->term_ = true;
			}
			return children_[idx];
		}

		Node* operator[](int idx) {
			return idx < 26 ? children_[idx] : nullptr;
		}

		bool terminate() {
			return term_;
		}

	};
	Node* root_;
	void suggest(string partialWord, string*& suggestions, int& size, Node* ptr) const;
public:
	SpellCheck(string data[],int sz);
	void addWord(const string& newWord);
	bool lookup(const string& word) const;
	int suggest(const string& partialWord, string suggestions[]) const;
	~SpellCheck();
};
#endif
