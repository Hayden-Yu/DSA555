#include <string>
#include <functional>
#include <utility>
#include <iostream>
using namespace std;

/*
 *Part B: functions modified:
  search, copy constructor, update, assignment operator, destructor
 */

template <class TYPE>
class Table{
public:
    Table(){}
    virtual bool update(const string& key, const TYPE& value)=0;
    virtual bool remove(const string& key)=0;
    virtual bool find(const string& key, TYPE& value)=0;
    virtual ~Table(){}
};

template <class TYPE>
class SimpleTable:public Table<TYPE>{

    struct Record{
        TYPE data_;
        string key_;
        Record(const string& key, const TYPE& data){
            key_=key;
            data_=data;
        }

    };

    Record** records_;   //the table
    int max_;           //capacity of the array
    int size_;          //current number of records held
    int search(const string& key);
    void sort();
    void grow();
public:
    SimpleTable(int maxExpected);
    SimpleTable(const SimpleTable& other);
    SimpleTable(SimpleTable&& other);
    virtual bool update(const string& key, const TYPE& value);
    virtual bool remove(const string& key);
    virtual bool find(const string& key, TYPE& value);
    virtual const SimpleTable& operator=(const SimpleTable& other);
    virtual const SimpleTable& operator=(SimpleTable&& other);
    virtual ~SimpleTable();
};


//returns index of where key is found.
template <class TYPE>
int SimpleTable<TYPE>::search(const string& key){
    int right = size_ - 1;
    int left = 0;
    while (left <= right) {
        int middle = (left + right) / 2;
        if (records_[middle]->key_ > key) {
            right = middle - 1;
        }
        else if(records_[middle]->key_ < key) {
            left = middle + 1;
        }
        else {
            return middle;
        }
    }
    return -1;
}
//sort the according to key in table
template <class TYPE>
void SimpleTable<TYPE>::sort(){
   int minIdx=0;
   for(int i=0;i<size_;i++){
        minIdx=i;
        for(int j=i+1;j<size_;j++){
            if(records_[j]->key_ < records_[minIdx]->key_){
                minIdx=j;
            }
        }
        Record* tmp=records_[i];
        records_[i]=records_[minIdx];
        records_[minIdx]=tmp;
   }
}

//grow the array by one element
template <class TYPE>
void SimpleTable<TYPE>::grow(){
    Record** newArray=new Record*[max_*2];
    max_=max_*2;
    for(int i=0;i<size_;i++){
        newArray[i]=records_[i];
    }
    delete [] records_;
    records_=newArray;
}

/* none of the code in the function definitions below are correct.  You can replace what you need
*/
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int maxExpected): Table<TYPE>(){
    records_=new Record*[maxExpected];
    max_=maxExpected;
    size_=0;
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& other){
    records_=new Record*[other.max_];
    max_=other.max_;
    size_=other.size_;
    for(int i=0;i<other.size_;i++){
        records_[i] = new Record(other.records_[i]->key_, other.records_[i]->data_);
    }
}
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE>&& other){
    size_=other.size_;
    max_=other.max_;
    records_=other.records_;
    other.records_=nullptr;
    other.size_=0;
    other.max_=0;
}

template <class TYPE>
bool SimpleTable<TYPE>::update(const string& key, const TYPE& value){
   int i;
    for(i = 0; i < size_; i++) {
        if(records_[i]->key_ == key) {
            records_[i]->data_ = value;
            return true;
        }
        else if(records_[i]->key_ > key) {
            break;
        }
    }
    if(max_ == size_) {
        grow();
    }
    //shift everything to its right to make room for new record
    for(int j = size_; j > i; j--) {
        records_[j] = records_[j - 1];
    }
    records_[i] = new Record(key, value);
    size_++;
    return true;
}

template <class TYPE>
bool SimpleTable<TYPE>::remove(const string& key){
    int idx=search(key);
    if(idx!=-1){
        delete records_[idx];
        for(int i=idx;i<size_-1;i++){
            records_[i]=records_[i+1];
        }
        size_--;
        return true;
    }
    else{
        return false;
    }
}

template <class TYPE>
bool SimpleTable<TYPE>::find(const string& key, TYPE& value){
    int idx=search(key);
    if(idx==-1)
        return false;
    else{
        value=records_[idx]->data_;
        return true;
    }
}

template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& other){
    if(this!=&other){
        if(records_){
            int sz=size_;
            for(int i=0;i<sz;i++){
                delete records_[i];
            }
            delete [] records_;
        }
        records_=new Record*[other.max_];
        max_=other.max_;
        size_=other.size_;
        for(int i=0;i<other.size_;i++){
            records_[i] = new Record(other.records_[i]->key_, other.records_[i]->data_);    
        }

    }
    return *this;
}
template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(SimpleTable<TYPE>&& other){
    swap(records_,other.records_);
    swap(size_,other.size_);
    swap(max_,other.max_);
    return *this;
}
template <class TYPE>
SimpleTable<TYPE>::~SimpleTable(){
    if(records_){
        int sz=size_;
        for(int i=0;i<sz;i++){
            delete records_[i];
        }
        delete [] records_;
    }
}

template <class TYPE>
class LPTable:public Table<TYPE>{
    string* keys_;
    TYPE* data_;
    size_t max_;
    size_t size_;
    size_t max__;
public:
    LPTable(int maxExpected);
    LPTable(const LPTable& other);
    LPTable(LPTable&& other);
    virtual bool update(const string& key, const TYPE& value);
    virtual bool remove(const string& key);
    virtual bool find(const string& key, TYPE& value);
    virtual const LPTable& operator=(const LPTable& other);
    virtual const LPTable& operator=(LPTable&& other);
    virtual ~LPTable();
};
/* none of the code in the function definitions below are correct.  You can replace what you need
*/
template <class TYPE>
LPTable<TYPE>::LPTable(int maxExpected): Table<TYPE>(){
    keys_ = new string[max_ = (int)(maxExpected * 1.5)];
    max__ = maxExpected;
    data_ = new TYPE[max_];
}

template <class TYPE>
LPTable<TYPE>::LPTable(const LPTable<TYPE>& other){
    keys_ = new string[max_ = other.max_];
    data_ = new TYPE[max_];
    max__ = other.max__;
    for(size_t i = 0; i < max_; i++){
        if(!other.keys_[i].empty()) {
            keys_[i] = other.keys_[i];
            data_[i] = other.data_[i];
        }
    }
}
template <class TYPE>
LPTable<TYPE>::LPTable(LPTable<TYPE>&& other){
    keys_ = other.keys_;
    data_ = other.data_;
    max_ = other.max_;
    max__ = other.max__;
    other.keys_ = nullptr;
    other.data_ = nullptr;
}
template <class TYPE>
bool LPTable<TYPE>::update(const string& key, const TYPE& value){
    size_t idx = hash<string>{}(key) % max_;
    size_t i = idx;
    do {
        if(keys_[i] == key) {
            data_[i] = value;
            return true;
        }
        else if(keys_[i].empty()) { //key doesnt exist
            if(size_ == max__) {
                return false;
            }
            keys_[i] = key;
            data_[i] = value;
            size_++;
            return true;
        }
        i = (i + 1) % max_;
    } while(i != idx);
    return false;
}

template <class TYPE>
bool LPTable<TYPE>::remove(const string& key){
    size_t idx = hash<string>{}(key) % max_; 
    size_t emptySlot;
    size_t j;
    //find the record
    for(size_t i = idx; !keys_[i % max_].empty() && i - max_ != idx; i++) {
        if(keys_[i % max_] == key) {
            //delete the record
            keys_[i %= max_] = "";
            size_--;
            
            for(size_t j = i + 1; !keys_[j % max_].empty() && j - max_ != i; j++) {
                string k = keys_[j % max_];
                TYPE v = data_[j % max_];
                keys_[j % max_] = "";
                size_--;
                update(k, v);
            }
            return true;
        }
    }
    return false;
}

template <class TYPE>
bool LPTable<TYPE>::find(const string& key, TYPE& value){
    size_t idx = hash<string>{}(key) % max_; 
    for(size_t i = idx; !keys_[i % max_].empty() && i - max_ != idx; i++) {
        if(keys_[i % max_] == key) {
            value = data_[i % max_];
            return true;
        }
    }
    return false;
}

template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(const LPTable<TYPE>& other){
    if(this != &other) {
        delete [] keys_;
        delete [] data_;
        keys_ = new string[max_ = other.max_];
        data_ = new TYPE[max_];
        max__ = other.max__;
        for(size_t i = 0; i < max_; i++){
            if(!other.keys_[i].empty()) {
                keys_[i] = other.keys_[i];
                data_[i] = other.data_[i];
            }
        }
    }
    return *this;
}

template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(LPTable<TYPE>&& other){
    swap(keys_, other.keys_);
    swap(data_, other.data_);
    swap(max_, other.max_);
    swap(max__, other.max__);
    return *this;
}

template <class TYPE>
LPTable<TYPE>::~LPTable(){
    delete [] keys_;
    delete [] data_;
}

