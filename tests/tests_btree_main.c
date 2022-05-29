#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "tests.h"
#include "btree.h"
#include "list.h"
#include "vector.h"
#include "hashtable.h"

int main(int argc, char** argv) {
    test_btree_int_cell();
    test_btree_int_cell_big();
    test_btree_int_cell_remove();
    test_btree_int_cell_remove_big();
    test_btree_int_cell_rebuild();
    test_btree_rebuild();

    return 0;
}

