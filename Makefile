CC=arm-none-linux-gnueabi-gcc
CFLAGS=-I./include -I ./jpeg-lib/include/ -L jpeg-lib/lib/ -ljpeg 
LDFLAGS=-lm
dpf:fb.o main.o jpeg.o
	$(CC) fb.o jpeg.o main.o -o dpf $(CFLAGS) $(LDFLAGS)
fb.o:fb.c
	$(CC) fb.c -c $(CFLAGS)
jpeg.o:jpeg.c
	$(CC) jpeg.c -c $(CFLAGS)
main.o:main.c
	$(CC) main.c -c $(CFLAGS)

clean:
	-rm *.o
	-rm dpf
