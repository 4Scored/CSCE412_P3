CC = g++
CFLAGS = -Wall -Werror

all: loadBalancerProgram

loadBalancerProgram: main.o loadbalancer.o webserver.o request.o
	$(CC) $(CFLAGS) -o loadBalancerProgram main.o loadbalancer.o webserver.o request.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

loadbalancer.o: loadbalancer.cpp
	$(CC) $(CFLAGS) -c loadbalancer.cpp

webserver.o: webserver.cpp
	$(CC) $(CFLAGS) -c webserver.cpp

request.o: request.cpp
	$(CC) $(CFLAGS) -c request.cpp

clean:
	rm -f loadBalancerProgram *.o