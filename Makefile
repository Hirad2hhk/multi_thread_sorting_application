CC = gcc
CFLAGS = -Wall -pthread

all: bubble_sort

bubble_sort: bubble_sort.c
	$(CC) $(CFLAGS) -o bubble_sort bubble_sort.c

clean:
	rm -f bubble_sort