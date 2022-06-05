#include <iostream>
#include <fstream>
#include <thread>

using namespace std;

//implementing singleton design pattern
// using template
template <typename T>
class Singleton
{

//constructor is protected because we are implementing singelton...
//in order to construct new object you need to use the instance function
protected:

    Singleton(T * _maped) {
        _maped_=_maped;
    }

    static Singleton *singleton_;

    T * _maped_;


public:

//create new Instance of the object
//if it's the frist time creating it
//then make a new object and return it
//else if it's already created
//then return the one created before
    static Singleton *Instance(T *_maped)
    {
        //check if created before
        if (singleton_ == nullptr)
        {
            singleton_ = new Singleton(_maped);
        }
        
        return singleton_;
    }


//destroy and remove the instance of the singelton object created

    static void Destroy(Singleton *s_obj)
    {
        delete s_obj;
    }

//file_data() function is used for file mapping
    T * file_data() {

         return this->_maped_; 

         }

};


//create new singelton type that takes template S as a paramater
//assign it to null
template <typename S>

Singleton<S> *Singleton<S>::singleton_ = nullptr;

//write(string line,Singleton<ofstream> *s_obj)
//this function is used to write for Singleton<ofstream> type
//used later for file mapping
void write(string line, Singleton<ofstream> *s_obj)
{
    //get string line ans assign to const char pos
    const char *pos = line.c_str();
    //return the _mapped var of the s_obj singelton object
    ofstream *stream = s_obj->file_data();
    //write it to output stream
    stream->write(pos, line.size());

}

// Singleton<std::string> s;



