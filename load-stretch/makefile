all: stretch

stretch: stretch.o
	gcc -lSDL2 -o stretch stretch.o

stretch.o: stretch.c
	gcc -c stretch.c

clean:
	rm stretch.o stretch
