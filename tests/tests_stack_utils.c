#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tests.h"

void    stack_string_dump(unsigned int index, const void* pv_data) {
    printf("\t%u:%s\n",index,(const char*)pv_data);
}

void    stack_data_cell_dump(unsigned int i, const void* pv_data) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    const ps_data_cell p_cell = (const ps_data_cell)pv_data ;
#pragma GCC diagnostic pop
    printf("\t%d:{%d %s}\n",i,p_cell->idx, p_cell->value);
}

