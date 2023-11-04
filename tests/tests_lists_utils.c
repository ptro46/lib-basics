#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tests.h"

void    list_data_cell_dump(const void* pv_data) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    const ps_data_cell p_cell = (const ps_data_cell)pv_data ;
#pragma GCC diagnostic pop
    printf("{%d %s}\n",p_cell->idx, p_cell->value);
}

void    list_data_cell_dump_with_index(int index, const void* pv_data) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    const ps_data_cell p_cell = (const ps_data_cell)pv_data ;
#pragma GCC diagnostic pop
    printf("\t%d::{%d,%s}\n",index, p_cell->idx, p_cell->value);
}

void    vector_cell_dump(unsigned int i, const void* pv_data) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    const ps_data_cell p_data_cell = (const ps_data_cell)pv_data;
#pragma GCC diagnostic pop
    printf("%d:(%d,%s)\n",i,p_data_cell->idx, p_data_cell->value);
}

int     list_data_cell_compare(const void* pv_data1, const void* pv_data2) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    const ps_data_cell p_cell1 = (const ps_data_cell)pv_data1 ;    
    const ps_data_cell p_cell2 = (const ps_data_cell)pv_data2 ;
#pragma GCC diagnostic pop

    return p_cell1->idx - p_cell2->idx ;
}

void    debug_list(ps_list p_list) {
    ps_list_data p_current = p_list->p_first ;
    printf("list %d elements\n",p_list->count);
    while ( p_current != NULL ) {
        printf("p_current       %p\n",(void*)p_current);
        printf("         p_data %s\n",(char*)(p_current->pv_data));         
        printf("         p_prev %p\n",(void*)p_current->p_prev);
        printf("         p_next %p\n",(void*)p_current->p_next);
        p_current = p_current->p_next ;
    }
    printf("\n");
}

void    list_string_dump(const void* data) {
    const char* psz = (const char*)data;
    printf("\t%s\n",psz);
}

void    list_string_dump_with_index(int index, const void* data) {
    const char* psz = (const char*)data;
    printf("\t%d:%s\n",index, psz);
}

int     list_string_compare(const void* data1, const void* data2) {
    const char* psz1 = (const char*)data1;
    const char* psz2 = (const char*)data2;

    int n = strcmp(psz1, psz2);
//    fprintf(stderr,"%d strcmp(%s,%s)\n",n,psz1, psz2);
    return n;
}
