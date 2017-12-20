CFLAGS = -std=c99 -Wall -O3 -lm 
GCC = gcc $(CFLAGS)
COMP = compress.o linked.o binary.o
DECOMP = decompress.o linked.o binary.o
VALGRIND = valgrind -v --tool=memcheck --leak-check=full --show-reachable=yes --track-origins=yes

all: compress decompress

compress: $(COMP) compress.h linked.h binary.h
	$(GCC) $(COMP) -o compress

decompress: $(DECOMP) compress.h linked.h binary.h 
	$(GCC) $(DECOMP) -o decompress

c.o:
	$(GCC) -c $*.c

clean:
	/bin/rm -f compress
	/bin/rm -f decompress
	/bin/rm -f *.o
	/bin/rm -f *.compress
	/bin/rm -f *.decompress
