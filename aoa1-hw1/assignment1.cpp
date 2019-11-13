/*Hakan SARAC
150140061
Algo-1 Assignment 1
*/
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>
#include <ctime>

using namespace std;

class arrays{
    const char *sort_type;
    int size;
public:
    int *A;
    int *B;
    arrays(int max_size,const char *sort):size(max_size),sort_type(sort){A = new int[max_size]; B = new int[max_size];}
    void readFile(const char *fptr); 
    void createOutput();
    void sorting();
    void MergeSort(int,int);
    void Merge(int,int,int);
    void Bubble();
};

void arrays::readFile(const char *fptr){
    ifstream r(fptr);
    int temp;
    int i=0;
    while (i<size) {  //okunacak sayiya gore degistir
		r >> temp;
		A[i++] = temp;
	}
  r.close();
}

void arrays::sorting(){
  clock_t t;
  t = clock();
    if(*sort_type == 'm' || *sort_type == 'M'){
      MergeSort(0,size-1);
    }

    else if(*sort_type == 'b' || *sort_type == 'B'){
      Bubble();
    }
    else{
      cout << "Error! Wrong character was entered." << endl;
    }
    
  t = clock()-t;
  cout<< "Time: "<< ((float)t)/CLOCKS_PER_SEC<<endl;
}



//bubble sort pseudo code
void arrays::Bubble(){
  int i = size;
  bool sorted=false;
  int temp;

  while(i>1 && sorted==false){
      sorted = true;
      for(int j=1 ; j <= i-1 ; j++){
          if (A[j] < A[j-1]){
              temp = A[j-1];
              A[j-1] = A[j];
              A[j] = temp;
              sorted = false;
          }
      }
      i--;
  }
}
//bubble sort pseudo code

//merge sort pseudo code
void arrays::MergeSort(int low,int high){
  int mid;
  if(low<high){
    mid = floor(low+high)/2;
    MergeSort(low,mid);
    MergeSort(mid+1,high);
    Merge(low,mid,high);
  }
}
void arrays::Merge(int low,int mid,int high){
  int k = low, i = low, j = mid+1;
  while( k<= mid && j<=high){
      if(A[k]<=A[j]){
          B[i] = A[k];
          k++;
      }
      else{
          B[i] = A[j];
          j++;
      }
      i++;
  }

  if(k>mid){
      for(int h=j;h<=high;h++){
          B[i] = A[h];
          i++;
      }
  }
  else{
      for(int h=k;h<=mid;h++){
          B[i] = A[h];
          i++;
      }
  }

  for(int h=low;h<=high;h++){
      A[h] = B[h];
      //cout<< endl << A[h];
  }
}
//merge sort pseudo code


void arrays::createOutput(){
    const char* filename;
    filename = "output.txt";
    ofstream myFile;
    myFile.open("output.txt");
    for(int i = 0;i<size;i++){
      myFile<< i+1 << " - ";
      myFile<<A[i];
      myFile<<endl;
    }
    myFile.close(); 
}

int main(int argc, char **argv){
    arrays myArray(atoi(argv[2]),argv[1]);
    myArray.readFile(argv[3]);
    myArray.sorting();
    myArray.createOutput();
    return 0;
}


