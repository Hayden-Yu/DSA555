template <typename T>
class Stack{
	T* theStack_;
	int max_;
	int top_;  //index of top of stack
	void grow(){
		T* tmp=new T[max_*2];
		for(int i=0;i<max_;i++){
			tmp[i]=theStack_[i];
		}
		max_=max_*2;
		delete [] theStack_;
		theStack_=tmp;
	}
public:
	Stack(){
		max_=100;
		theStack_=new T[max_];
		top_=0;
	}
	void push(const T& data){
		if(top_==max_){
			grow();
		}
		theStack_[top_++]=data;
	}
	void pop(){
		if(top_ > 0){
			top_--;
		}
	}
	T top() const{
		return theStack_[top_-1];
	}
	~Stack(){
		delete [] theStack_;
	}
};
