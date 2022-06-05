# operating_sys_6

# part1_final folder :

 ##### imple.hpp : 
 Queue implmentaion

#####  Active_obj.hpp :
implementing Active object (used later on client-server)

#####  main.cpp :

used to test the Queue (testing)

## makefile (part1) - open the part1_final file on terminal and run make all and then run ./main
/
/
# part2_final folder :

#####  client.cpp :

client from exercise 3

##### server.cpp -> server is impleminting active object pipline :

first active object : takes input from the socket (English letters) and applies to it Caesar cipher


seconed active object : takes the output of the first object and translate capital letters tom small letters(and in reverse)


third active object : takes the output of the third object and returns it back to the client


##### Active_obj.hpp :

implementing Active object (used later on client-server)

##### imple.hpp :
Queue implemention

##### Guard.cpp :
implementing Guard design pattern on a global variable, one thread can access it at a time
and chnage the global variable

##### Singelton.cpp :
implementing singelton design pattern which allows to map a file to memory

##### Reactor.cpp :
 implementing Reactor desgin pattern
 
 ##### file.txt : 
 used for testing
 
 
## makefile (part2) - open the part2_final file on terminal and run make all and then run ./server ,
## open another window and run ./client localhost (to check for clinet_srver using Active object implmention)
## run ./guard or ./reactor or ./singelton to check that they work.

thank you , make sure to smile always :)
 

