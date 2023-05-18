all: event

event: event.o
	gcc -lSDL2 -o event event.o

event.o: event.c
	gcc -c event.c

clean:
	rm event.o event
