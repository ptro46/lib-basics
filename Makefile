AR      = ar
RANLIB  = ranlib
CC      = gcc
CFLAGS 	= -D_GNU_SOURCE=1 -ggdb -Wall -Wmissing-declarations -Wshadow -Wstrict-prototypes -Wmissing-prototypes -Wpointer-arith -Wcast-qual -Wsign-compare -Wpedantic -fPIC
INCPATH	= -I. -I/usr/local/include
LINK	= gcc
LFLAGS	= -L/usr/local/lib/
LIBS	= -ljson-c -lcurl

.SUFFIXES:	.o .c

HEADERS_TESTS = tests.h
SOURCES_TESTS = tests.c tests_buffer.c tests_lists.c tests_vector.c tests_stack.c tests_hashtable.c tests_btree.c
OBJECTS_TESTS = tests.o tests_buffer.o tests_lists.o tests_vector.o tests_stack.o tests_hashtable.o tests_btree.o

HEADERS = b_types.h buffer.h curl.h hashtable.h list.h stack.h strl.h vector.h btree.h $(HEADERS_TESTS)
SOURCES = strl.c buffer.c curl.c list.c stack.c vector.c hashtable.c btree.c $(SOURCES_TESTS)
OBJECTS = strl.o buffer.o curl.o list.o stack.o vector.o hashtable.o btree.o $(OBJECTS_TESTS)

TARGET	= libbasics.a
EXE     = test-basics

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

all: $(TARGET) $(EXE)

$(EXE): $(OBJECTS)
	$(LINK) $(LFLAGS) -o $(EXE) $(OBJECTS) $(LIBS)

$(TARGET): $(OBJECTS)
	$(AR) rv $@ $(OBJECTS)
	$(RANLIB) $@

valgrind: $(TARGET)
	valgrind -v --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=yes --num-callers=20 --track-origins=yes ./$(EXE)

doc: $(SOURCES) $(HEADERS)
	doxygen libbasics.conf

clean:
	rm -f $(OBJECTS) $(TARGET) $(EXE) *~ *.bin

send:
	rsync -aP * nagios:/home/ptro/Lang-C/basics/

debug:
	cp *.c *.h ~/Documents/xcode/basics/basics/
	cp tests.c ~/Documents/xcode/basics/basics/main.c

