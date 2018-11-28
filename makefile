all: shell.o
	gcc shell.o

shell.o: shell.c
	gcc -c shell.c

run:
	./a.out
	make clean

clean:
	rm ./a.out
