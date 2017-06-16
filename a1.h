template <typename T>
class DList{
	struct Node{
        Node(const T& data=T{}, Node* next=nullptr, Node* prev=nullptr){
            data_ = data;
            next_ = next;
            prev_ = prev;
        }
        T data_;
        Node* prev_;
        Node* next_;
	};
    Node* front_;
    Node* back_;
    int size_;
    void init() {
        back_ = new Node();
        front_ = new Node(T{}, back_);
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
        const T& operator*() const{
            return curr_->data_;
        } 
	};
	class iterator:public const_iterator{
	public:
        iterator():const_iterator(){}
        iterator(Node* n):const_iterator(n){}
        T& operator*(){
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
    void push_front(const T& data){
         front_->next_ = front_->next_->prev_ = new Node(data, front_->next_, front_);
         ++size_;
    }
    void push_back(const T& data){
        back_->prev_ = back_->prev_->next_ = new Node(data, back_, back_->prev_);
        ++size_;
    }
    void pop_front(){
        if(front_->next_ != back_) {
            front_->next_ = front_->next_->next_;
            delete front_->next_->prev_;
            front_->next_->prev_ = front_;
            --size_;
        }
    }
    void pop_back(){
        if(back_->prev_ != front_) {
            back_->prev_ = back_->prev_->prev_;
            delete back_->prev_->next_;
            back_->prev_->next_ = back_;
            --size_;
        }
    }
    iterator insert(iterator loc, const T& data){
        if(loc.curr_){
            loc.curr_->prev_ = 
                loc.curr_->prev_->next_ = new Node(data, loc.curr_, loc.curr_->prev_);
            ++size_;
        }
        return --loc;
    }
    void erase(iterator it){
        if(it.curr_ && it != end()){
            it.curr_->next_->prev_ = it.curr_->prev_;
            it.curr_->prev_->next_ = it.curr_->next_;
            delete it.curr_;
            --size_;
        }
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
    iterator search(const T& data){
        for(iterator itor = begin(); itor != end(); itor++){
            if(*itor == data){
                return itor;
            }
        }
        return end();
    }
    const_iterator search(const T& data) const{
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
    DList(const DList& rhs){
        init();
        for(const_iterator itor = rhs.begin(); itor != rhs.end(); itor++){
            push_back(*itor);
        }
    }
    DList& operator=(const DList& rhs){
        erase(begin(), end());
        for(const_iterator itor = rhs.begin(); itor != rhs.end(); itor++){
            push_back(*itor);
        }
    }
    DList(DList&& rhs){
        init();
        front_->next_ = rhs->front_->next_;
        back_->prev_ = rhs->back_->prev_;
        rhs->front_->next_ = rhs->back_->prev_ = nullptr;
    }
    DList& operator=(DList&& rhs){
        erase(begin(), end());
        front_->next_ = rhs->front_->next_;
        back_->prev_ = rhs->back_->prev_;
        rhs->front_->next_ = rhs->back_->prev_ = nullptr;
    }
};