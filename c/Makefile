CC = gcc
IDIR = ./include
MUNIT = ./munit
TESTDIR = ./tests
CFLAGS = -g -I$(IDIR) # turn on debug info & include headers

_DEPS = dbllist.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_TESTDEPS = munit.c munit.h
TESTDEPS = $(patsubst %,$(MUNIT)/%,$(_TESTDEPS))

_TESTS = test-dbllist.c
TESTS = $(patsubst %,$(TESTDIR)/%,$(_TESTS))

#$@ is the LEFT side of the : and $^ is the RIGHT
hello: hello.o dbllist.o
	$(CC) -o $@ $^ $(CFLAGS)

hello.o: hello.c $(DEPS)
	$(CC) -c $^ $(CFLAGS)

dbllist.o: $(DEPS)
	$(CC) -c $^ $(CFLAGS)

test: munit.o $(DEPS) $(TESTS)
	$(CC) -o $@ $^ $(CFLAGS)
	./test

munit: $(TESTDEPS)
	$(CC) -c $^ -g

.PHONY: clean
clean:
	rm -rf *.o
	rm -rf *.gch
	rm -f hello