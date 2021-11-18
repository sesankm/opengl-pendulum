CFLAGS=-Wall -Wextra -std=c11 
LIBS=`pkg-config --libs glu gl` -lglut -lm

all: 
	$(CC) $(CFLAGS) -o pend pend.c $(LIBS)
