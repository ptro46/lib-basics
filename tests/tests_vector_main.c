#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tests.h"

int main(int argc, char** argv) {
    test_vector_string();
    test_vector_copy();
    test_vector_struct();
    test_vector_struct_add_vector();
    return 0;
}

