CC      = gcc
CFLAGS 	= -D_GNU_SOURCE=1 -ggdb -Wall -Wmissing-declarations -Wshadow -Wstrict-prototypes -Wmissing-prototypes -Wpointer-arith -Wcast-qual -Wsign-compare -Wpedantic -fPIC
INCPATH	= -I. -I../ -I/usr/local/include
LINK	= gcc
LFLAGS	= -L/usr/local/lib/ -L../
LIBS	= -ljson-c -lcurl -lbasics

.SUFFIXES:	.o .c

HEADERS_TESTS = tests.h

TEST_BUFFER    = tests_buffer
TEST_LISTS     = tests_lists
TEST_VECTOR    = tests_vector
TEST_STACK     = tests_stack
TEST_HASHTABLE = tests_hashtable
TEST_BTREE     = tests_btree

SOURCES_TEST_BUFFER = tests_buffer.c tests_buffer_utils.c tests_buffer_main.c
OBJECTS_TEST_BUFFER = tests_buffer.o tests_buffer_utils.o tests_buffer_main.o

SOURCES_TEST_LISTS = tests_lists.c tests_lists_utils.c tests_lists_main.c
OBJECTS_TEST_LISTS = tests_lists.o tests_lists_utils.o tests_lists_main.o

SOURCES_TEST_VECTOR = tests_vector.c tests_vector_utils.c tests_vector_main.c
OBJECTS_TEST_VECTOR = tests_vector.o tests_vector_utils.o tests_vector_main.o

SOURCES_TEST_STACK = tests_stack.c tests_stack_utils.c tests_stack_main.c
OBJECTS_TEST_STACK = tests_stack.o tests_stack_utils.o tests_stack_main.o

SOURCES_TEST_HASHTABLE = tests_hashtable.c tests_hashtable_utils.c tests_hashtable_main.c
OBJECTS_TEST_HASHTABLE = tests_hashtable.o tests_hashtable_utils.o tests_hashtable_main.o

SOURCES_TEST_BTREE = tests_btree.c tests_btree_utils.c tests_btree_main.c
OBJECTS_TEST_BTREE = tests_btree.o tests_btree_utils.o tests_btree_main.o

OBJECTS_TESTS = $(OBJECTS_TEST_BUFFER) $(OBJECTS_TEST_LISTS) $(OBJECTS_TEST_VECTOR) $(OBJECTS_TEST_STACK) $(OBJECTS_TEST_HASHTABLE) $(OBJECTS_TEST_BTREE)

TARGET = tests

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

all: $(TEST_BUFFER) $(TEST_LISTS) $(TEST_VECTOR) $(TEST_STACK) $(TEST_HASHTABLE) $(TEST_BTREE) $(TARGET)

$(TEST_BUFFER): tests.h $(OBJECTS_TEST_BUFFER)
	$(LINK) $(LFLAGS) -o $(TEST_BUFFER) $(OBJECTS_TEST_BUFFER) $(LIBS)

$(TEST_LISTS): tests.h $(OBJECTS_TEST_LISTS)
	$(LINK) $(LFLAGS) -o $(TEST_LISTS) $(OBJECTS_TEST_LISTS) $(LIBS)

$(TEST_VECTOR): tests.h $(OBJECTS_TEST_VECTOR) tests_lists_utils.o
	$(LINK) $(LFLAGS) -o $(TEST_VECTOR) $(OBJECTS_TEST_VECTOR) tests_lists_utils.o $(LIBS)

$(TEST_STACK): tests.h $(OBJECTS_TEST_STACK) tests_lists_utils.o tests_vector_utils.o
	$(LINK) $(LFLAGS) -o $(TEST_STACK) $(OBJECTS_TEST_STACK) tests_lists_utils.o tests_vector_utils.o $(LIBS)

$(TEST_HASHTABLE): tests.h $(OBJECTS_TEST_HASHTABLE) 
	$(LINK) $(LFLAGS) -o $(TEST_HASHTABLE) $(OBJECTS_TEST_HASHTABLE) $(LIBS)

$(TEST_BTREE): tests.h $(OBJECTS_TEST_BTREE) tests_hashtable_utils.o tests_lists_utils.o
	$(LINK) $(LFLAGS) -o $(TEST_BTREE)  $(OBJECTS_TEST_BTREE) tests_hashtable_utils.o tests_lists_utils.o $(LIBS)

$(TARGET): tests.h tests.o $(OBJECTS_TESTS)
	$(LINK) $(LFLAGS) -o $(TARGET) tests.o tests_buffer.o tests_buffer_utils.o tests_lists.o tests_lists_utils.o tests_vector.o tests_vector_utils.o tests_stack.o tests_stack_utils.o tests_hashtable.o tests_hashtable_utils.o tests_btree.o tests_btree_utils.o  $(LIBS)

valgrind: $(TARGET)
	valgrind -v --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=yes --num-callers=20 --track-origins=yes ./$(TARGET)

clean:
	rm -f $(OBJECTS_TESTS) $(TEST_BUFFER) $(TEST_LISTS) $(TEST_VECTOR) $(TEST_STACK) $(TEST_HASHTABLE) $(TEST_BTREE) $(TARGET) tests.o  *~ *.bin
