#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tests.h"

int main(int argc, char** argv) {
    test_buffer();    
    test_list() ;
    test_list_bounds();
    test_list_sorted();
    test_list_data_sorted();
    test_list_copy();
    test_vector_string();
    test_vector_copy();
    test_vector_struct();
    test_stack_string();
    test_stack_copy();
    test_stack_struct();
    test_hashtable_string_string();
    test_hashtable_int_cell();    
    return 0;
}
