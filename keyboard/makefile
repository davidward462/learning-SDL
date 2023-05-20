all: keyboard

keyboard: keyboard.o
	gcc -lSDL2 -o keyboard keyboard.o

keyboard.o: keyboard.c
	gcc -c keyboard.c

clean:
	rm keyboard.o keyboard
