#include "iostream"

#include "imple.hpp"

using namespace std;

//create new struct(new type) called Active_obj
//Active_obj struct has 3 things :
//- queue
//- points to function that handles each element
//- points to function that handles elemnt after the fist function finish 
typedef struct Active_obj
{
    Queue queue;
    void (*for_each_elem)(void *);
    void (*after)(void *);
    
    //used within clinet_server active object imple...
    std::string st;
    int f;
    
} * obj;

//newAO
//creates new Active object
//return obj(new Active object)
obj newAO(Queue queue, void (*for_each_elem)(void *), void (*after)(void *))
{
    obj Ao = (obj)malloc(sizeof(Active_obj));

    Ao->queue = queue;
    Ao->for_each_elem = for_each_elem;
    Ao->after = after;

    return Ao;
}

//destroyAO
//destroy the Active object and free it from memory
void destroyAO(obj Ao)
{ 
    Ao->queue.destroyQ();
    free(Ao);
}

