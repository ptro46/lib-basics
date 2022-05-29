#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tests.h"
#include "hashtable.h"


int main(int argc, char** argv) {
    test_hashtable_string_string();
    test_hashtable_int_cell();
    return 0;
}

