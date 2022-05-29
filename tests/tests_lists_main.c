#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tests.h"

int main(int argc, char** argv) {
    test_list();
    test_list_bounds();
    test_list_sorted();
    test_list_data_sorted();
    test_list_copy();
    return 0;
}

