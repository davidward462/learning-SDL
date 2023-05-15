all: hello

hello: hello.o
	gcc -lSDL2 -o hello hello.o

hello.o: hello.c
	gcc -c hello.c

clean:
	rm hello.o hello
