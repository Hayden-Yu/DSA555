#ifndef A3_V2_H
#define A3_V2_H
#include <string>
using namespace std;

class DList{
	struct Node{
        Node(const string& data="", Node* next=nullptr, Node* prev=nullptr){
            data_ = data;
            next_ = next;
            prev_ = prev;
        }
        string data_;
        Node* prev_;
        Node* next_;
	};
    Node* front_;
    Node* back_;
    int size_;
    void init() {
        back_ = new Node();
        front_ = new Node("", back_);
        size_ = 0;
        back_->prev_ = front_;
    }
public:
	class const_iterator{
        friend class DList;
    protected:
        Node* curr_;
	public:
        const_iterator(Node* n) {
            curr_ = n;
        }
        const_iterator(){
            curr_ = nullptr;
        }
        bool operator==(const_iterator rhs){
            return curr_ == rhs.curr_;
        }
        bool operator!=(const_iterator rhs){
            return curr_ != rhs.curr_;
        }
        const_iterator operator++(){
            if(curr_)
                curr_ = curr_->next_;
            return *this;
        }
        const_iterator operator++(int){
            const_iterator ret = *this;
            if(curr_)
                curr_ = curr_->next_;
            return ret;
        }
        const_iterator operator--(){
            if(curr_)
                curr_ = curr_->prev_;
            return *this;
        }
        const_iterator operator--(int){
            const_iterator ret = *this;
            if(curr_)
                curr_ = curr_->prev_;
            return ret;
        }
        const string& operator*() const{
            return curr_->data_;
        }
	};
	class iterator:public const_iterator{
	public:
        iterator():const_iterator(){}
        iterator(Node* n):const_iterator(n){}
        string& operator*(){
            return this->curr_->data_;
        }
        iterator operator++(){
            if(this->curr_)
                this->curr_ = this->curr_->next_;
            return *this;
        }
        iterator operator++(int){
            iterator ret = *this;
            if(this->curr_)
                this->curr_ = this->curr_->next_;
            return ret;
        }
        iterator operator--(){
            if(this->curr_)
                this->curr_ = this->curr_->prev_;
            return *this;
        }
        iterator operator--(int){
            iterator ret = *this;
            if(this->curr_)
                this->curr_ = this->curr_->prev_;
            return ret;
        }
	};
    DList(){
        init();
    }
    iterator begin(){
        return iterator(front_->next_);
    }
    iterator end(){
        return iterator(back_);
    }
    const_iterator begin() const{
        return const_iterator(front_->next_);
    }
    const_iterator end() const{
        return const_iterator(back_);
	}

	void insert(string data) {
		iterator itor = begin();
		for(; itor != end(); itor++) {
			if((*itor) > data) {
				break;
			}
		}
		itor.curr_->prev_ =
			itor.curr_->prev_->next_ = new Node(data, itor.curr_, itor.curr_->prev_);
		++size_;
	}
    void erase(iterator first, iterator last){
        Node* prev = first.curr_->prev_;
        while(first != last && first != end()){
            ++first;
            delete first.curr_->prev_;
            --size_;
        }
        Node* next = (first == last ? last.curr_ : back_);
        prev->next_ = next;
        next->prev_ = prev;
    }
    iterator search(const string& data){
        for(iterator itor = begin(); itor != end(); itor++){
            if(*itor == data){
                return itor;
            }
        }
        return end();
	}

	const_iterator partialSearch(const string& data) const {
		for(const_iterator itor = begin(); itor != end(); itor++){
            if((*itor).substr(0, data.size()) == data){
                return itor;
            }
        }
        return end();
	}

    const_iterator search(const string& data) const{
        for(const_iterator itor = begin(); itor != end(); itor++){
            if(*itor == data){
                return itor;
            }
        }
        return end();
    }
    bool empty() const{
        return front_->next_ == back_;
    }
    int size() const{
        return size_;
    }
    ~DList(){
        erase(begin(), end());
        delete front_;
        delete back_;
    }
};

class SpellCheck{
	DList* dict_;
public:
	SpellCheck(string data[],int sz);
	void addWord(const string& newWord);
	bool lookup(const string& word) const;
	int suggest(const string& partialWord, string suggestions[]) const;
	~SpellCheck();
};
#endif
