/*
Name: Pak Yu

Course: CS280

        CRN: 39072-831
Assignment:  Count3sThreadParallel.cpp

        Date: 2/11/2019
*/

#ifndef CS280_COUNT3STHREADPARALLEL_H
#define CS280_COUNT3STHREADPARALLEL_H

typedef struct
{
    int32_t *arr;
    int     len;
    int     count_sum;
} num_collection;

int32_t* store_array(  string file_path);
void *count_three( void (*arg));

#endif //CS280_COUNT3STHREADPARALLEL_H
