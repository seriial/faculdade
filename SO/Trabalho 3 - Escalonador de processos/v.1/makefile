SOURCES = simproc.c
HEADERS = simproc.h 
NAMES = executarMain simproc.o

CC = clang
CFLAGS = -Wall

all: executarMain

executarMain: simproc.o
	$(CC) -o executarMain simproc.o $(CFLAG)

simproc.o: simproc.c simproc.h
	$(CC) -c simproc.c $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(NAMES)

pkg:
	tar -czvf trabalho3.tar.gz $(SOURCES) $(HEADERS) processos.csv makefile
