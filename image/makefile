all: blit

blit: blit.o
	gcc -lSDL2 -o blit blit.o

blit.o: blit.c
	gcc -c blit.c

clean:
	rm blit.o blit
