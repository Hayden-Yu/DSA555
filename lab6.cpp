#include <cstdlib>
#include <iostream>
#include <fstream>
#include "timer.h"

using namespace std;

void generateReverseData(int array[],int sz){
    for(int i = 0; i < sz; array[i++] = sz - i);
}

void generateManyDuplicates(int array[],int sz){
    for(int i = 0; i < sz; array[i++] = (rand() % 1000 + 5));
}

void generateNearlySorted(int array[],int sz){
    for(int i = 0; i < sz; array[i++] = i + 1);
    for(int j = sz * 0.05; j >= 0; j--){
        int idxA = rand() % sz;
        int idxB = rand() % sz;
        int tmp = array[idxA];
        array[idxA] = array[idxB];
        array[idxB] = tmp;
    }
}

void insertionSort(int arr[],int left,int right){
  int curr;
  int i, j;
  for(i=left+1;i<=right;i++){
    curr=arr[i];
    for(j=i;j>0 && arr[j-1] > curr;j--){
      arr[j]=arr[j-1];
    }
    arr[j]=curr;
  }
}


void quickSort(int arr[], int left, int right, int threshold){
  if(right-left <= threshold){
    insertionSort(arr,left,right);
  }
  else{
    int pivotpt=(left + right)/2;   //index of the pivot
    /*if(arr[pivotpt] > arr[left] && arr[pivotpt] > arr[right])
        pivotpt = arr[left] > arr[right] ? left : right;
    if(arr[pivotpt] < arr[left] && arr[pivotpt] < arr[right])
        pivotpt = arr[left] > arr[right] ? right : left;*/
    int i=left;
    int j=right-1;
    int pivot=arr[pivotpt];
    while(i<j){
      while(i< right-1 && arr[i]<pivot) i++;
      while(j > 0 && arr[j]>pivot) j--;
      if(i<j)
        swap(arr[i++],arr[j--]);
    }
    if(i==j && arr[i] < arr[pivotpt])
      i++;
    swap(arr[i],arr[pivotpt]);
    quickSort(arr,left,i-1, threshold);
    quickSort(arr,i+1,right, threshold);
  }
}

void quickSort(int arr[],int size, int threshold){
  quickSort(arr,0,size-1, threshold);
}
void generateRandomArray(int array[],int size){
  for(int i=0;i<size;i++){
    array[i]=rand();
  }

}
int main(int argc, char* argv[]){
  int threshold = atoi(argv[2]);
  int size=atoi(argv[1]);
  int* myarr=new int[size];
  Timer stopwatch;
  ofstream log("quick.log");
  generateRandomArray(myarr,size);
  stopwatch.start();
  quickSort(myarr,size, threshold);
  stopwatch.stop();
  cout << stopwatch.currtime() << endl;
  /*for(int i=0;i<size;i++){
    log <<myarr[i]<< endl;
  }*/
  return 0;
}

/*int main(int argc, char** argv) {
    int size=atoi(argv[1]);
    int* myarr=new int[size];
    Timer stopwatch;
    ofstream log("quick.log");

    generateRandomArray(myarr,size);
    stopwatch.start();
    quickSort(myarr,size);
    stopwatch.stop();
    cout << "Random array " << stopwatch.currtime() << endl;

    generateReverseData(myarr,size);
    stopwatch.start();
    quickSort(myarr,size);
    stopwatch.stop();
    cout << "Reverse array " << stopwatch.currtime() << endl;

    generateManyDuplicates(myarr,size);
    stopwatch.start();
    quickSort(myarr,size);
    stopwatch.stop();
    cout << "Duplicates array " << stopwatch.currtime() << endl;

    generateNearlySorted(myarr,size);
    stopwatch.start();
    quickSort(myarr,size);
    stopwatch.stop();
    cout << "NearlySorted array " << stopwatch.currtime() << endl;

    return 0;
}*/
