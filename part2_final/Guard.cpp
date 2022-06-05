#include <iostream>
#include <thread>
#include <mutex>

#include "vector"

using namespace std;

//global number
int shared = 0;

//lock_a is used to lock thread(synchronyzation)
pthread_mutex_t lock_a;

//implementing guard using class
//guard has a private lock_
//lock_ is used to lock threads from reaching the guard
class Guard
{
    
private:
     pthread_mutex_t lock_;

public:
    Guard(pthread_mutex_t &lock1) : lock_(lock1)
    {
       //using mutex for locking
       pthread_mutex_lock(&lock_);
    }
    ~Guard()
    {
        //using mutex for unlocking
        pthread_mutex_unlock(&lock_);
    }

};

/////////////////////////////////////////////////////////////////////////////////

// this function is used to modify global number
// different trying to modify global number
// modify_shared_num function is implemented with the help of guard design pattern
void modify_shared_num(int th_num,int line)
{
    //create new guard wich will lock the main lock
    //only one thread can access the global number
    //once at a time
    const Guard * guard=new Guard(lock_a);

    //save the last number before modifying the shared number(global)
    int last_num = shared;

    size_t i = 0;

    do
    {
        shared++;

        i++;

    } while(i < line);
   
   
    cout << "thread_number ----> " << th_num << endl;

    cout << last_num << " + " << line << " = " << shared << endl;


}

//main is used for testing

int main(int argc, char const *argv[])
{

    thread thread0 = thread(modify_shared_num, 0, (int)2);
    thread thread1 = thread(modify_shared_num, 1, (int)3);
    thread thread2 = thread(modify_shared_num, 2, (int)4);
    thread thread3 = thread(modify_shared_num, 3, (int)5);
    thread thread4 = thread(modify_shared_num, 4, (int)6);

    thread0.join();
    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();

    return 0;
}