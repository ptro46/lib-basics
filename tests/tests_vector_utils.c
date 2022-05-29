#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tests.h"

void    vector_string_dump(unsigned int i, const void* pv_data) {
    printf("%d:%s\n",i,(const char*)pv_data);
}

int     vector_string_compare(const void* pv_data1, const void* pv_data2) {
    const char* psz1 = (const char*)pv_data1 ;
    const char* psz2 = (const char*)pv_data2 ;
    return 0 == strcmp(psz1, psz2);
}

void    vector_data_cell_dump(unsigned int i, const void* pv_data) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    const ps_data_cell p_cell = (const ps_data_cell)pv_data ;
#pragma GCC diagnostic pop
    printf("\t%d:{%d %s}\n",i,p_cell->idx, p_cell->value);
}
