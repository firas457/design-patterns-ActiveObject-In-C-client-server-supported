#include <iostream>
#include <mutex>
using namespace std;

class node
{
public:
    node *next;
    int data;

    node(int& data)
    {
        this->data = data;
        next = NULL;
    }
};

class queue
{

    pthread_mutex_t lock;

private:
    node *head = NULL;

public:
    queue()
    {
    }

    void enQ(int new_node)
    {
        // char data[1024];
        // data = (std::string)new_node;
        // std::string &data = *(static_cast<std::string*>(new_node));
        node * new_node1=new node(new_node);

   
        node *temp = NULL;

        if (head == NULL)
        {
            head = new_node1;
         
        }

        else
        {
            temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }

            new_node1->next = NULL;
            temp->next = new_node1;
    
        }
    }

    void deQ()
    {
      
        if (empty())
        {
            std::__throw_out_of_range("there is no elements");
        }

        else
        {
            head = head->next;
   
        }
    }

    int size()
    {
        node *temp;
        temp = head;

        if (temp == NULL)
        {
            return 0;
        }

        int size = 1;

        while (temp->next != NULL)
        {
            temp = temp->next;
            size++;
        }

        return size;
    }

    bool empty()
    {

        bool ans = true;

        if (head == NULL)
        {
            return ans;
        }
        return (!ans);
    }

    void print()
    {
        node *temp;
        temp = head;

        while (temp != NULL)
        {
            std::cout << temp->data << "-------->";
            temp = temp->next;
        }
    }
};

class Queue
{
    queue *queue_;
    pthread_mutex_t lock2;

public:
    void createQ()
    {
        
        queue_ = new queue();
   
    }
    void destroyQ()
    {
       
        delete queue_;
       
    }
    void enQ(int new_node)
    {
        queue_->enQ(new_node);
    }
    void deQ()
    {
        queue_->deQ();
    }
    void print()
    {
        queue_->print();
    }

    int size()
    {
        return queue_->size();
    }
};

