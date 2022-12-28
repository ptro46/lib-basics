AR      = ar
RANLIB  = ranlib
CC      = gcc
CFLAGS 	= -D_GNU_SOURCE=1 -ggdb -Wall -Wmissing-declarations -Wshadow -Wstrict-prototypes -Wmissing-prototypes -Wpointer-arith -Wcast-qual -Wsign-compare -Wpedantic -fPIC
INCPATH	= -I. -I/usr/local/include
LINK	= gcc
LFLAGS	= -L/usr/local/lib/
LIBS	= -ljson-c -lcurl

.SUFFIXES:	.o .c

HEADERS = b_types.h buffer.h curl.h hashtable.h list.h stack.h strl.h vector.h btree.h console.h 
SOURCES = strl.c buffer.c curl.c list.c stack.c vector.c hashtable.c btree.c console.c 
OBJECTS = strl.o buffer.o curl.o list.o stack.o vector.o hashtable.o btree.o console.o 

TARGET	    = libbasics.a

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(AR) rv $@ $(OBJECTS)
	$(RANLIB) $@

doc: $(SOURCES) $(HEADERS)
	doxygen libbasics.conf

clean:
	rm -f $(OBJECTS) $(TARGET) $(EXE) *~ *.bin

