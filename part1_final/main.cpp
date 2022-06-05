
#include "stdio.h"
#include <iostream>

#include "imple.hpp"

using namespace std;

int main(){


Queue queue;
queue.createQ();
queue.enQ(1);
queue.enQ(2);
queue.enQ(3);
queue.enQ(4);

queue.deQ();
queue.deQ();

cout << "stack size is :" <<endl;
cout << queue.size() <<endl;

cout << "print elements in stack  :" <<endl;

queue.print();

}