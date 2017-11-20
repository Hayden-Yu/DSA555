bool candidate(int array[],int& candidate, int sz){
    bool odd = false;
    int left = 0;
    if (sz & 1) {
        left = array[--sz];
        odd = true;
    }
    int szNew = 0;
    for(int i = 0; i < sz; i+=2){
        if (array[i] == array[i+1]){
            array[szNew++] = array[i];
        }
    }
    if(szNew == 1){
        candidate = array[0];
        return true;
    }
    if(szNew && ::candidate(array, candidate, szNew)){
        return true;
    } else {
        candidate = left;
        return odd;
    }	
}
bool majorityElement(const int arr[], int& majority, int sz){
	int cp[sz];
    int i;
    //create a duplicate of arr
    for(i = 0; i < sz; i++){
        cp[i] = arr[i];
    }
    //find the only possible candidate
    if(::candidate(cp, majority, sz)){
        int count = 0;
        for(i = 0; i < sz; ++i){
            //verify that the majority element is indeed the majority element
            if(arr[i] == majority){
                ++count;
            }
            if(count > sz/2){
                return true;
            }
        }
    }
    //this function is iterative
    return false;
}
