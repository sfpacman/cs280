//
// Created by yup on 27/01/19.
//

/*

Name: Pak Yu

Course: CS280

CRN: 39072-831
Assignment:  Count3sProcessSerial.cpp

Date:
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <climits>

using namespace std;

int array_size;

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
        ;


    }
    array_size = count;
    //cout  << count << "\n";
    file.close();

    int32_t *result = arr;
    return result ;
}

int count_three( int arr[]){
    int count =0;
    //int len=sizeof(arr) / sizeof(arr[0]);
    //cout << sizeof(arr) << "\n";
    for ( int i =0 ; i < array_size ; i++) {
        if( arr[i] == 3 ){count++;}
    }
    return  count;
}

int main() {
    string input;
    int size=0;
    int count =0;
    int a;
    input="threesData.bin";

    int *arr= store_array(input);
    int c = count_three(arr);

    delete [] arr ;
    cout << c << "\n";


}
