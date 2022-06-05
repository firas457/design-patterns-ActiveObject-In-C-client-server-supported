
all: client server	guard	reactor	singleton
	
client: client.o
	g++	-pthread -o client client.o


server: server.o 
	g++ -pthread  -o  server server.o  -lrt

guard: Guard.o 
	g++ -pthread  -o  guard Guard.o

reactor: Reactor.o 
	g++ -pthread  -o  reactor Reactor.o

singleton: Singleton.o
	g++	-pthread -o Singleton Singleton.o 
client.o: client.cpp
	g++	-pthread -c client.cpp

server.o: server.cpp
	g++ -pthread -c server.cpp 

Guard.o: Guard.cpp
	g++ -pthread -c Guard.cpp 

Singleton.o: Singleton.cpp
	g++ -pthread -c Singleton.cpp 

Reactor.o: Reactor.cpp
	g++ -pthread -c Reactor.cpp 


.PHONY: clean all

clean:
	rm -f *.o client server	guard	reactor	singleton