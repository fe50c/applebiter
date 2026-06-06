CFLAGS = 
LDLIBS = /usr/lib/libimobiledevice-1.0.so
main: main.o

.PHONY: clean
clean:
	rm -f main main.o
