CFLAGS = 
LDLIBS = /usr/lib/libimobiledevice-1.0.so /usr/lib/libplist-2.0.so.4.7.0

run: main
	./main

main: main.o

.PHONY: clean
clean:
	rm -f main main.o
