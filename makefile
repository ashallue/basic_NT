paths = -I/usr/local/include -L/usr/local/lib
tags = -lm -lgmp -O3  
debugtags = -lm -lgmp -ggdb
objects = bigint.o int.o primetest.o fermat_factor.o test_functions.o

all: main

%.o:	%.cpp
	g++ $(paths) -c $<

main.o:	main.cpp
	g++ $(paths) -c main.cpp

main:	main.o $(objects)
	g++ $(paths) main.o $(objects) -o main $(tags)

clean:
	rm *.o
