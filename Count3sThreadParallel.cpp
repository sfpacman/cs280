/*
Name: Pak Yu

Course: CS280

        CRN: 39072-831
Assignment:  Count3sThreadParallel.cpp

        Date: 2/11/2019
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <pthread.h>
#include "Count3sThreadParallel.h"

using namespace std;





#define NUMTHRDS 4

num_collection num_array;
pthread_t thread[NUMTHRDS];
pthread_mutex_t mutexsum;

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
    num_array.len = count;
    //cout  << count << "\n";
    file.close();

    int32_t *result = arr;
    return result ;
}

void *count_three( void (*arg)){
    int start, end;
    long partition;
    partition= long(arg);

    start= num_array.len / NUMTHRDS * partition;
    if ( partition == NUMTHRDS-1 ){
        end = num_array.len;
    }
    else{ end = num_array.len/NUMTHRDS * ( partition +1);}
    int count =0;
    //printf("thread %d - start: %d , end: %d \n" , partition ,start,end  );
    for ( int i = start ; i < end ; i++) {
        if( num_array.arr[i] == 3 ){count++;}
    }

    pthread_mutex_lock (&mutexsum);
    num_array.count_sum += count;
    //cout <<partition << " is adding " << count << " to " << num_array.count_sum<< "\n";
    pthread_mutex_unlock (&mutexsum);

    pthread_exit((void*) 0);

}

int main(){
    string input;
    input="threesData.bin";
    void *status;

    int *arr= store_array(input);
    //cout << "count length"<<num_array.len << "\n";
    num_array.arr = arr;
    pthread_attr_t attr;

    pthread_mutex_init(&mutexsum, NULL);
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    long i;
    for( i=0; i<NUMTHRDS; i++) {
        pthread_create(&thread[i], &attr, count_three, (void *) i);
    }
    pthread_attr_destroy(&attr);
    for(i=0; i<NUMTHRDS; i++)
    {
        pthread_join(thread[i], &status);
        //printf("thread %d joining \n" , i );
    }

    int result= num_array.count_sum;
    cout<< result << "\n";
    delete [] arr ;
    pthread_mutex_destroy(&mutexsum);
    pthread_exit(NULL);


}