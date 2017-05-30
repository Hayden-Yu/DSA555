//templated doubly linked list
#include <iostream>
using namespace std;
template <typename T>
class DList{
	struct Node{
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data=T{},Node* n=nullptr,Node* p=nullptr){
			data_=data;
			next_=n;
			prev_=p;
		}		
	};
	Node* front_;
	Node* back_;
public:
	class const_iterator{
		friend class DList;
	protected:
		Node* curr_;
		const_iterator(Node* n){
			curr_=n;
		}
	public:
		const_iterator(){
			curr_=nullptr;
		}
		//++x
		const_iterator operator++(){
			if(curr_){
				curr_=curr_->next_;
			}
			return *this;
		}
		//x++
		const_iterator operator++(int){
			const_iterator old=*this;
			if(curr_){
				curr_=curr_->next_;
			}
			return old;			
		}
		const_iterator operator--(){
			if(curr_){
				curr_=curr_->prev_;
			}
			return *this;

		}
		const_iterator operator--(int){
			const_iterator old=*this;
			if(curr_){
				curr_=curr_->prev_;
			}
			return old;			
		}
		T operator*()const{
			return curr_->data_;
		}
		bool operator==(const_iterator other) const{
			return curr_==other.curr_;
		}
		bool operator!=(const_iterator other) const{
			return curr_!=other.curr_;
		}
	};
	class iterator:const_iterator{
		friend class DList;
		iterator(Node* n):const_iterator(n){

		}
	public:
		iterator():const_iterator(){
		}
		//++x
		iterator operator++(){
			if(this->curr_){
				this->curr_=this->curr_->next_;
			}
			return *this;
		}
		//x++
		iterator operator++(int){
			iterator old=*this;
			if(this->curr_){
				this->curr_=this->curr_->next_;
			}
			return old;			
		}
		iterator operator--(){
			if(this->curr_){
				this->curr_=this->curr_->prev_;
			}
			return *this;

		}
		iterator operator--(int){
			iterator old=*this;
			if(this->curr_){
				this->curr_=this->curr_->prev_;
			}
			return old;			
		}
		T& operator*(){
			return this->curr_->data_;
		}
		T operator*()const{
			return this->curr_->data_;
		}
		bool operator==(iterator other) const{
			return this->curr_==other.curr_;
		}
		bool operator!=(iterator other) const{
			return this->curr_!=other.curr_;
		}
	};
	//returns an iterator to first piece of data
	//in DList
	iterator begin(){
		return iterator(front_);
	}
	//returns an iterator to the thing that
	//FOLLOWS the last piece of data in DList;
	iterator end(){
		return iterator(nullptr);
	}
	//returns an iterator to first piece of data
	//in DList
	const_iterator begin() const{
		return iterator(front_);
	}
	//returns an iterator to the thing that
	//FOLLOWS the last piece of data in DList;
	const_iterator end() const{
		return iterator(nullptr);
	}
	DList(){
		front_=back_=nullptr;
	}
	void push_front(const T& data){
		if(front_==nullptr){
		//make a node
			Node* nn=new Node(data);
			//make front point to the node
			front_=nn;
			//make back point to the node
			back_=nn;
		}
		else{
			//make a node
			Node* nn=new Node(data,front_);
			//change previous pointer of old front node
			front_->prev_=nn;
			//change front pointer
			front_=nn;
		}	
	}
	void push_back(const T& data){		
		back_ = new Node(data, nullptr, back_);
        if(front_)
            (back_->prev_)->next_ = back_;
        else
            front_ = back_;
	}
	void pop_front(){
		if(front_){
			Node* rm = front_;
			front_=front_->next_;
			delete rm;
			if(front_!=nullptr){
				front_->prev_=nullptr;
			}
			else{
				//this else only happens if list had only one node
				back_=nullptr;
			}
		}
	}
	void pop_back(){
		if(!back_) return;
        back_ = back_->prev_;
        if(back_){
            delete back_->next_;
            back_->next_ = nullptr;
        } else {
            delete front_;
            front_ = nullptr;
        }
	}
	void print() const{
		Node* curr=front_;
		while(curr!=nullptr){
			cout << curr->data_ << endl;
			curr=curr->next_;
		}	
	}
};