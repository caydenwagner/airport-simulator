CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean valgrind

all: bin bin/airportdriver bin/airporttestdriver

bin: 
	mkdir -p bin

bin/airportdriver: bin/airportdriver.o bin/airport.o \
					../QueueADT/bin/queue.o \
					../ListADT/bin/list.o
	${CC} ${CFLAGS} bin/airportdriver.o bin/airport.o \
					../QueueADT/bin/queue.o \
					../ListADT/bin/list.o -o bin/airportdriver

bin/airportdriver.o: src/airportdriver.c include/airport.h 
	${CC} ${CFLAGS} -c src/airportdriver.c -o bin/airportdriver.o

bin/airporttestdriver: bin/airporttestdriver.o bin/airport.o \
					../QueueADT/bin/queue.o \
					../ListADT/bin/list.o
	${CC} ${CFLAGS} bin/airporttestdriver.o bin/airport.o \
					../QueueADT/bin/queue.o \
					../ListADT/bin/list.o -o bin/airporttestdriver
					
bin/airporttestdriver.o: src/airporttestdriver.c include/airport.h 
	${CC} ${CFLAGS} -c src/airporttestdriver.c -o bin/airporttestdriver.o

bin/airport.o: src/airport.c include/airport.h \
				../QueueADT/include/queue.h \
				../ListADT/include/list.h
	${CC} ${CFLAGS} -c src/airport.c -o bin/airport.o

../QueueADT/bin/queue.o:
	cd ../QueueADT; make bin/queue.o
	
../ListADT/bin/list.o:
	cd ../ListADT; make bin/list.o

valgrind: bin/airportdriver bin/airporttestdriver
	valgrind -v --leak-check=yes --track-origins=yes \
	--leak-check=full --show-leak-kinds=all bin/airportdriver \
	bin/airporttestdriver data/airport.txt

clean:
	rm -rf bin/*.o bin/airportdriver bin/airporttestdriver
	