# variables
CC = gcc
CFLAGS = -Wall -g -std=c99
TARGETS = my_cat 
OBJECTS = my_cat.o

#build all programs
all: $(TARGETS)

my_cat: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

my_cat.o: my_cat.c
	$(CC) $(CFLAGS) $< -c

.PHONY:

clean:
	rm -f $(TARGETS) *.o a.out 
