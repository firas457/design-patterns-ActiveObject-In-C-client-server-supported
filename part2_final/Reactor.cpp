#include <iostream>
#include <vector>
#include <poll.h>
#include <string.h>
#include <unistd.h>
#include "Singelton_reactor.hpp"

using namespace std;

//creat reactor


//class Reactor has two main members:
//vector of type pollfd to handel polls coming from client
//vector of functions pointers to point for fuction that handles requests
    class Reactor
    {
        
    public:

        std::vector<pollfd> polls_c;
        std::vector<void (*)(int)> ptr_fs;
        
    };

//newReactor creates new Reactor using
//singleton design pattern wich was implemented on Singleton.hpp
//create new instance Singleton<Reactor>::Instance that takes new Reactor
//if it's already created the singelton returns it
    void *newReactor()
    {
        return Singleton<Reactor>::Instance(new Reactor());
    }

//Install Handler
//this function is used to handle requests from reactors
//it takes three paramaters :
// reactor
// pointer to functions
// socket descriptor
    void InstallHandler(Reactor *reactor, void (*func)(int), int sock_f)
    {
        //create pollfd type param
        pollfd curr_poll;
        //assign an socket fd to it
        curr_poll.fd = sock_f;
        //add events
        curr_poll.events = POLLIN;
        //add the curr_poll to the reactor polls vector
        //so it can be handled later
        reactor->polls_c.push_back(curr_poll);
        //add the request(fucntion) to the reactor request(functions) vector
        reactor->ptr_fs.push_back(func);
    }

//Remove Handler
//this function is used to release a handler from a given reactor and
//socket discriptor that the reactor handles
    void RemoveHandler(Reactor *r, int sock_f)
    {
       //for loop to check if sock_fd(socket decriptor) is
       //inside the given reactor polls_c vector
       //if it's there delete it from the polls vector
       //and from the functions pointers vector(requests)
       //close the socket after finish
       size_t j = 0;

        do
        {
            int temp=r->polls_c.at(j).fd;

            if (temp == sock_f)
            {
                r->polls_c.erase(r->polls_c.begin() + j);
                r->ptr_fs.erase(r->ptr_fs.begin() + j);
                break;
            }

            j++;

        }while( j < r->polls_c.size());

        close(sock_f);

    }



int main(){
    return 0;
}