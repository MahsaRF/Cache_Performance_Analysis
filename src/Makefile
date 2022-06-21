INCDIR = -I. -I/opt/papi/5.7.0/include
DBG    = -Wall 
OPT    = -O3
CC     = gcc
CPP    = g++
CFLAGS = $(DBG) $(OPT) $(INCDIR)
LDFLAGS = -lm -L/opt/papi/5.7.0/lib64 -lpapi #-lperfctr

OBJ =   sort-test.o	\
	bsearch.o	\
	heapsort.o	\
	quicksort.o	\
	insort.o	\
	shellsort.o	


HEADER =  timer.h		\
	sort.h

.SUFFIXES: .o.cpp .o.c

all: sort-test

sort-test: $(OBJ)
	$(CPP) $(CFLAGS) -o sort-test $(OBJ)  $(LDFLAGS)

$(OBJ): 
.cpp.o: $(HEADER)
	$(CPP) $(CFLAGS) -c $< -o $@
.c.o:   $(HEADER)
	$(CC) $(CFLAGS) -c $<



clean:
	/bin/rm -f sort-test *.o
	/bin/rm -f *~ 



