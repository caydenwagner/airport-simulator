CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean valgrind

all: bin bin/queuedriver

bin:
	mkdir -p bin

bin/queuedriver: bin/queuedriver.o bin/queue.o \
					../ListADT/bin/list.o \
					../PriorityQueueADT/bin/pqueue.o
	${CC} ${CFLAGS} bin/queuedriver.o bin/queue.o \
					../ListADT/bin/list.o \
					../PriorityQueueADT/bin/pqueue.o -o bin/queuedriver

bin/queuedriver.o: src/queuedriver.c include/queue.h
	${CC} ${CFLAGS} -c src/queuedriver.c -o bin/queuedriver.o

bin/queue.o: src/queue.c include/queue.h \
				../ListADT/include/list.h \
				../PriorityQueueADT/include/pqueue.h
	${CC} ${CFLAGS} -c src/queue.c -o bin/queue.o \
				../ListADT/bin/list.o \
				../PriorityQueueADT/bin/pqueue.o

../ListADT/bin/list.o:
	cd ../ListADT; make bin/list.o
	
../PriorityQueueADT/bin/pqueue.o:
	cd ../PriorityQueueADT;  make bin/pqueue.o

valgrind: bin/queuedriver
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full \
	--show-leak-kinds=all bin/queuedriver

clean:
	rm -rf bin/*.o bin/queuedriver