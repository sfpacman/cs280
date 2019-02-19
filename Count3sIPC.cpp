/*
Name: Pak Yu

Course: CS280

CRN: 39072-831
Assignment:  CountIPC.txt

Date: 2/11/2019
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <assert.h>

using namespace std;

#if !defined(__GNU_LIBRARY__) || defined(_SEM_SEMUN_UNDEFINED)
union semun
{
int val;
// value for SETVAL
struct semid_ds* buf;
// buffer for IPC_STAT, IPC_SET
unsigned short* array; // array for GETALL, SETALL
struct seminfo* __buf; // buffer for IPC_INFO
};
#endif

typedef struct
{
    int32_t *arr;
    int     len =0 ;
    int     count_sum =0 ;
    int     start = 0 ;
    int     semaphore_id;
} num_collection;

int AllocateSharedMemory(int n)
{
    assert(n > 0);
    return shmget(IPC_PRIVATE, n, IPC_CREAT | SHM_R | SHM_W);
}


/**
* Maps a shared memory segment onto our address space.
*
* @param id Shared memory block to map.
* @return Address of mapped block.
*/

void* MapSharedMemory(int id)
{
    void* addr;
    assert(id != 0); /* Idiot-proof the call. */
    addr = shmat(id, NULL, 0); /* Attach the segment...
*/
    shmctl(id, IPC_RMID, NULL); /* ...and mark it destroyed. */
    return addr;
}

int CreateSemaphoreSet(int n, unsigned short* vals)
{
    union semun arg;
    int id;
    assert(n > 0); /* You need at least one! */
    assert(vals != NULL); /* And they need initialising! */
    id = semget(IPC_PRIVATE, n, SHM_R | SHM_W);
    arg.array = vals;
    semctl(id, 0, SETALL, arg);
    return id;
}
/**
* Frees up the given semaphore set.
*
* @param id Id of the semaphore group.
*/
void DeleteSemaphoreSet(int id)
{
    if (semctl(id, 0, IPC_RMID, NULL) == -1)
    {
        perror("Error releasing semaphore!");
        exit(EXIT_FAILURE);
    }
}
/**
* Locks a semaphore within a semaphore set.
*
* @param id Semaphore set it belongs to.
* @param i
Actual semaphore to lock.
*
* @note If it’s already locked, you’re put to sleep.
*/
void LockSemaphore(int id, int i)
{
    struct sembuf sb;
    sb.sem_num = i;
    sb.sem_op = -1;
    sb.sem_flg = SEM_UNDO;
    semop(id, &sb, 1);
}
/**
* Unlocks a semaphore within a semaphore set.
*
* @param id Semaphore set it belongs to.
* @param i
Actual semaphore to unlock.
*/
void UnlockSemaphore(int id, int i)
{
    struct sembuf sb;
    sb.sem_num = i;
    sb.sem_op = 1;
    sb.sem_flg = SEM_UNDO;
    semop(id, &sb, 1);
}
enum
{
    SEM_USER_1,
    SEM_USER_2
};

int32_t* store_array(  string file_path, num_collection& array ){
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
    array.len = count;
    //cout  << count << "\n";
    file.close();

    int32_t *result = arr;
    return result ;
}
int count_three( num_collection nun_array, int &interval){
    //cout << "process_id: " << id << "start at: " << start << " to " << start+ interval << "\n";
    int count =0;
    for ( int i = nun_array.start ; i < num_array.start+ interval ; i++) {
        if( num_arrat.arr[i] == 3 ){count++;}
    }
    return  count;
}

int main() {
    string input;
    int size = 0;
    int fork_loop = 1;
    num_collection num_array;
    input = "threesData.bin";

    // variables for shared memory
    int shmem_id;
    char* buf_address;
    int *arr= store_array(input,num_array);
    num_array.arr = arr;
    int bufsize = sizeof(num_array) + num_array.len*sizeof(int);
    int interval = num_array.len / (fork_loop + 1 );
    shmem_id = AllocateSharedMemory(bufsize);
    buf_address = (char*) MapSharedMemory(shmem_id);
    *((num_collection *) buf_address )= num_array;
    //*((int *) buf_address) = 0;


    for ( int i = 0; i < fork_loop ; i++) {
        pid_t pid = fork();
        if (pid == 0) {
          num_collection temp = *( (num_collection *) buf_address);
          count_three(,temp)
          *( (num_collection *) buf_address) = temp;

          cout << pid << "\t" << temp.count_sum << "\n";
          exit(0);
        }
        else {

            int exitstat = -1;
            wait(&exitstat);
            num_collection temp = *((num_collection *) buf_address);
            cout << pid << "\t" << temp.count_sum << "\n";
            temp.count_sum += 11;
            cout<< pid <<"\t" << temp.count_sum << "\n";

              }

    }


}