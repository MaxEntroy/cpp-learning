CC= gcc -std=gnu99
CFLAGS= -Wall -Wextra
LDFLAGS=
LIBS=

main: main.o foo.o
	$(CC) -o $@ $(LDFLAGS) main.o foo.o $(LIBS)

main.o: main.c foo.h
foo.o: foo.c

clean:
	rm -rf main main.o foo.o

.PHONY: clean
