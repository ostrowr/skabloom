# Initial Makefile. 

# inspired by http://www.cs.colby.edu/maxwell/courses/tutorials/


CC=gcc
CFLAGS=-I$(IDIR) -std=c99 -Wall -Wextra -O0 -g

IDIR=include
ODIR=obj
LDIR=lib
SDIR=src

LIBS=-lm

# All relevant source files are listed here:
_SRC = skabloom.c, skabloom_test.c
SRC = $(patsubst %,$(SDIR)/%,$(_SRC))

# All .h files here
_DEPS = skabloom.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

# Desired .o files here
_OBJ = skabloom.o skabloom_test.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean again

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ 

again:
	make clean && make