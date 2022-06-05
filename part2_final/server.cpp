/*
** server.c -- a stream socket server demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include "Active_obj.hpp"

#define PORT "3490" // the port users will be connecting to

#define BACKLOG 10 // how many pending connections queue will hold
#define MAXDATASIZE 1024

Active_obj Active_obj1;
Active_obj Active_obj2;
Active_obj Active_obj3;

void *seconed_obj_reverse_words(void *args);
void *first_obj_read_from_client(void *st);
void *third_obj_return_to_client(void *c);

char buf[1024];

void sigchld_handler(int s)
{
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while (waitpid(-1, NULL, WNOHANG) > 0)
        ;

    errno = saved_errno;
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in *)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

void *third_obj_return_to_client(void *c)
{
 if (send(Active_obj3.f,Active_obj3.st.c_str(), 13, 0) == -1){
        perror("send");
    }

}

void *seconed_obj_reverse_words(void *args)
{
    std::string temp;

    for (int i = 0; i < Active_obj2.st.length(); i++)
    {
        if (Active_obj2.st[i] >= 'a' && Active_obj2.st[i] <= 'z')
        {
            temp += (char)(Active_obj2.st[i] -= 32);
        }
        else if (Active_obj2.st[i] >= 'A' && Active_obj2.st[i] <= 'Z')
        {
            temp += (char)(Active_obj2.st[i] += 32);
        }
    }

     Active_obj3.st = temp;
     Active_obj3.after = (void (*)(void *))third_obj_return_to_client;
    (*Active_obj3.after)(NULL);
}

void *first_obj_read_from_client(void *st)
{

    std::string temp;

    for (int i = 0; i < Active_obj1.st.length(); i++)
    {
        temp += (char)(Active_obj1.st[i] += 1);
    }

    Active_obj2.st = temp;

    (*Active_obj1.after)(NULL);
}

void *handle_client(void *args)
{
    Queue queue;

    // Active_obj1=newAO(queue,first_obj_read_from_client(void *),seconed_obj_reverse_words(void*));

    int new_fd = *(int *)(args);
    while (1)
    {
    
    recv(new_fd, buf, MAXDATASIZE - 1, 0);
    Active_obj3.f=new_fd;
    Active_obj1.st = buf;
    Active_obj1.for_each_elem = (void (*)(void *))first_obj_read_from_client;
    Active_obj1.after = (void (*)(void *))seconed_obj_reverse_words;

    (*Active_obj1.for_each_elem)(NULL);

    // Active_obj1.for_each_elem(buf);
   
    // sleep(10);
    }
    close(new_fd);
}

int main(void)
{
    int sockfd, new_fd; // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa;
    int yes = 1;
    char s[INET6_ADDRSTRLEN];
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for (p = servinfo; p != NULL; p = p->ai_next)
    {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1)
        {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                       sizeof(int)) == -1)
        {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (p == NULL)
    {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1)
    {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    while (1)
    { // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1)
        {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family,
                  get_in_addr((struct sockaddr *)&their_addr),
                  s, sizeof s);
        printf("server: got connection from %s\n", s);

        pthread_t thr;
        pthread_create(&thr, NULL, handle_client, (void *)&new_fd);
    }

    return 0;
}