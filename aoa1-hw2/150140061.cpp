/*Hakan SARAC
150140061
Algo-1 Assignment 2
*/

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>

using namespace std;
int virtual_clock = 1;

typedef struct event_node{     //each event
    int event_time;
    string event_name; 
    string event_type;
}event_node;

class event_array{              //event array
    event_node *elements;       //elements of events 
    int size;                   //size of event array
public:
    event_array(int , const char* );
    void Min_Heapify(int );
    void Build_Min();
    void Heap_Sort();
};

int arr_size(const char *fptr){  //counting array size
    string line;
    int count=  0;
    ifstream r(fptr);
    while(getline(r,line)) count++;
    r.close();
    return count;
}

event_array::event_array(int event_size, const char *fptr){   //constructor of event_array
    int index = 0;
    string tempname;
    size = event_size*2;	//each event has start and end (x2)
    elements = new event_node[size];   //elements array size
    ifstream file(fptr);
    while(index<size){
      file >> tempname;
      elements[index].event_name = tempname;
      elements[index].event_type = "START";
      file >> elements[index].event_time;            
      index++;
      elements[index].event_name = tempname;
      elements[index].event_type = "END";
      file >> elements[index].event_time;      
      index++;
    }
    file.close();
}

void event_array::Build_Min(){  //this function is from recitation-3 slides
	int i;
	int heap_size = size;
	for(i=heap_size/2; i>=0; i--)	Min_Heapify(i);	
}

void event_array::Min_Heapify(int i){   //this function is from recitation-3 slides but there are changes for min-heapify 
	event_node temp;
	int left = 2*i+1;
	int right = 2*i+2;
	int smallest = i;
	if(left<size && elements[left].event_time < elements[i].event_time) smallest = left;
	if(right<size && elements[right].event_time < elements[smallest].event_time) smallest = right;
	if(smallest != i) {
		temp = elements[i];
		elements[i] = elements[smallest];
		elements[smallest] = temp; 
		Min_Heapify(smallest);
	} 
}

void event_array::Heap_Sort(){
	event_node temp;
	int flag = 0;		//this flag is to control multiple events at same virtual time 
						//if there are an event equal to virtual time flag is 1, ow 0
	Build_Min();
	int temp_size = size;
	for(int i=temp_size-1; i>=0 ; i--){		
		if(!flag){      //do not enter the function if there is an event equal to virtual time to control there may be another event at same vitual time   
			while(virtual_clock<elements[0].event_time){ 
				cout << "TIME " << virtual_clock << ": NO EVENT" << endl;
				virtual_clock++;
			}
		}
		if(virtual_clock==elements[0].event_time){
			cout << "TIME " << virtual_clock << ": " << elements[0].event_name << " " << elements[0].event_type << "ED" <<endl;
			flag = 1 ;
		}
		else{
			flag = 0;
			virtual_clock++;
			while(virtual_clock<elements[0].event_time){ 
				cout << "TIME " << virtual_clock << ": NO EVENT" << endl;
				virtual_clock++;
			}
			if(virtual_clock==elements[0].event_time){
			cout << "TIME " << virtual_clock << ": " << elements[0].event_name << " " << elements[0].event_type << "ED" <<endl;
			flag = 1;
			}
		}					
		temp = elements[i];
		elements[i] = elements[0];
		elements[0] = temp;
		size--;
		Min_Heapify(0);
		if(i==0) cout << "TIME " << virtual_clock << ": NO MORE EVENTS, SCHEDULER EXITS" << endl;	 //last event happened		
	}  
}

int main(int argc, char **argv){  
    event_array a(arr_size(argv[1]), argv[1]);    
	a.Heap_Sort();
    return 0;
}
