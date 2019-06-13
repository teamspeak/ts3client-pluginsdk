#
# Makefile to build TeamSpeak 3 Client Test Plugin
#

CFLAGS = -c -O2 -Wall -fPIC

all: test_plugin

test_plugin: plugin.o
	gcc -o test_plugin.so -shared plugin.o

plugin.o: ./src/plugin.c
	gcc -Iinclude src/plugin.c $(CFLAGS)

clean:
	rm -rf *.o test_plugin.so
