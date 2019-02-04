/*
Name: Pak Yu

Course: CS280

        CRN: 39072-831
Assignment:  Count3sProcessParallel.cpp

        Date: 2/4/2019
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include<sys/wait.h>
#include "Count3sProcessParallel.h"



int32_t* store_array(  string file_path){
    ifstream file (file_path, ios::in | ios::binary);
    file.seekg(0,ios::end);
    int size=(int32_t)file.tellg();
    file.seekg(0,ios::beg);
    int count =0;
    int32_t *arr = new int32_t[size] ;
    int32_t a ;
    while( file.tellg() < size)
    {
        file.read ((char*)&a, sizeof(a));
        if (sizeof(a) == 4 ) {
            arr[count] = int(a);
            count ++;
        }
        else{ cout << a << "\n" ;};

    }
    array_size = count;
    //cout  << count << "\n";
    file.close();

    int32_t *result = arr;
    return result ;
}

int* split_array_pos( int part){

    int *pos = new int [part];
    int portion;
    int remainer= array_size % part;
    portion = array_size / part;
    for( int i =0;i <= part; i++){
        pos[i]= 0 + i *portion;
        if(i == part){ pos[i]= remainer;}
        //cout << pos[i] << "\n";
    }
    return  pos;

}
int count_three( int arr[],int start , int interval ,int id){
     //cout << "process_id: " << id << "start at: " << start << " to " << start+ interval << "\n";
    int count =0;
    for ( int i = start ; i < start+ interval ; i++) {
        if( arr[i] == 3 ){count++;}
    }
    return  count;
}

int main() {
    string input;
    int size=0;
    int fork_loop = 1;
    int count = 0;
    int child_count;
    int childvals = 0 ;
    input="threesData.bin";

    int *arr= store_array(input);
    int count_process = pow(2, fork_loop);
    //cout << count_process << "\n";
    int *pos= split_array_pos(count_process);
    //cout << array_size << "\n";
    //cout << childval << "\n";
    for ( int i = 0; i < fork_loop ; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            int count = count_three(arr,pos[i+1],array_size/count_process, getpid());
            ofstream out("temp.txt");
            out<<  count << "\n" ;
            out.close();
            exit(0);
        }}
    //  cout << "Parent " <<  getpid() <<"\n";
        int exitstat = -1;
        wait(&exitstat);
        count = count_three(arr,pos[0],array_size/count_process, getpid());
        // reading values from child process from temp file
        ifstream infile("temp.txt");
        while (infile >> child_count) {
            childvals = child_count + childvals;
        }
        infile.close();
        childvals = count + childvals ;
        cout <<  childvals << "\n";


    delete [] arr ;
   // cout << c <<  "\n";


}