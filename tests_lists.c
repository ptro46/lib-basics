#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tests.h"

void    test_list_data_sorted(void) {
    s_data_cell    cells[] = {
        { 5 , "123456" } ,
        { 8 , "12345" } ,
        { 6 , "123456789" } ,
        { 9 , "password" } ,
        { 2 , "iloveyou" } ,
        { 10 , "princess" } ,
        { 1 , "1234567" } ,
        { 4 , "rockyou" } ,
        { 3 , "12345678" } ,
        { 7 , "abc123" }
    } ;

    s_list    list_of_cells;

    list_init(&list_of_cells, true, list_data_cell_compare);

    int nb_elems = sizeof(cells) / sizeof(s_data_cell) ;
    for(int i=0;i<nb_elems;i++) {
        list_add(&list_of_cells, &cells[i]);
        // fprintf(stderr,"\n");
        // debug_list(&list_of_strings);
    }
    printf("list_for_each_with_limit 20/10\n");
    list_for_each_with_limit(&list_of_cells, list_data_cell_dump_with_index, 40);

    list_free(&list_of_cells);
}

void    test_list_copy(void) {
    s_data_cell    cells[] = {
        { 5 , "123456" } ,
        { 8 , "12345" } ,
        { 6 , "123456789" } ,
        { 9 , "password" } ,
        { 2 , "iloveyou" } ,
        { 10 , "princess" } ,
        { 1 , "1234567" } ,
        { 4 , "rockyou" } ,
        { 3 , "12345678" } ,
        { 7 , "abc123" }
    } ;

    s_list    list_of_cells;
    s_list    l_copy ;
    s_vector  to_vector;

    list_init(&list_of_cells, true, list_data_cell_compare);

    int nb_elems = sizeof(cells) / sizeof(s_data_cell) ;
    for(int i=0;i<nb_elems;i++) {
        list_add(&list_of_cells, &cells[i]);
        // fprintf(stderr,"\n");
        // debug_list(&list_of_strings);
    }

    list_copy(&list_of_cells, &l_copy) ;

    list_to_vector(&list_of_cells, &to_vector);

    printf("list_for_each list_of_cell\n");
    list_for_each_with_limit(&list_of_cells, list_data_cell_dump_with_index, 40);

    printf("list_for_each list_copy\n");
    list_for_each_with_limit(&l_copy, list_data_cell_dump_with_index, 40);

    printf("vector_for_each to_vector\n");
    vector_for_each(&to_vector, vector_cell_dump);

    list_free(&list_of_cells);
    list_free(&l_copy);
    vector_free(&to_vector);
}

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

void    test_list_sorted(void) {
    char*    words[] = {
        "123456",        /* 00 */
        "12345",         /* 01 */
        "123456789",     /* 02 */
        "password",      /* 03 */
        "iloveyou",      /* 04 */
        "princess",      /* 05 */
        "1234567",       /* 06 */
        "rockyou",       /* 07 */
        "12345678",      /* 08 */
        "abc123",        /* 09 */
        "nicole",        /* 10 */ // remove_at 10
        "daniel",        /* 11 */
        "babygirl",      /* 12 */
        "monkey",        /* 13 */
        "lovely",        /* 14 */
        "jessica",       /* 15 */
        "654321",        /* 16 */
        "michael",       /* 17 */
        "ashley",        /* 18 */
        "qwerty",        /* 19 */
        "111111",        /* 20 */
        "iloveu",        /* 21 */
        "000000",        /* 22 */
        "michelle",      /* 23 */
        "tigger",        /* 24 */
        "sunshine",      /* 25 */
        "chocolate",     /* 26 */
        "password1",     /* 27 */
        "soccer",        /* 28 */
        "anthony"        /* 29 */
    };
    s_list    list_of_strings;

    list_init(&list_of_strings, true, list_string_compare);

    int nb_elems = sizeof(words) / sizeof(char*) ;
    for(int i=0;i<nb_elems;i++) {
        list_add(&list_of_strings, words[i]);
        fprintf(stderr,"\n");
        debug_list(&list_of_strings);
    }
    printf("list_for_each_with_limit 20/10\n");
    list_for_each_with_limit(&list_of_strings, list_string_dump_with_index, 40);

    list_free(&list_of_strings);
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

void    test_list_bounds(void) {
    char*    words[] = {
        "123456",        /* 00 */
        "12345",         /* 01 */
        "123456789",     /* 02 */
        "password",      /* 03 */
        "iloveyou",      /* 04 */
        "princess",      /* 05 */
        "1234567",       /* 06 */
        "rockyou",       /* 07 */
        "12345678",      /* 08 */
        "abc123",        /* 09 */
        "nicole"         /* 10 */ // remove_at 10
    } ;

    s_list    list_of_strings;

    list_init(&list_of_strings, false, NULL);

    int nb_elems = sizeof(words) / sizeof(char*) ;
    for(int i=0;i<nb_elems;i++) {
        list_add(&list_of_strings, words[i]);
    }

    printf("list_for_each\n");
    list_for_each(&list_of_strings, list_string_dump);

    printf("list_for_each_with_limit 20/10\n");
    list_for_each_with_limit(&list_of_strings, list_string_dump_with_index, 20);

    printf("list_get_at 20\n");
    char* psz = (char*)list_get_at(&list_of_strings, 20);
    if ( psz != NULL ) {
        printf("\t%s\n",psz);
    } else {
        printf("\tnot found\n");
    }

    printf("list_get_element soccer\n");
    psz = list_get_element(&list_of_strings, "soccer", list_string_compare);
    if ( psz != NULL ) {
        printf("\t%s\n",psz);
    } else {
        printf("\tnot found\n");
    }

    printf("list_remove_element monkey\n");
    list_remove_element(&list_of_strings, "monkey", list_string_compare);
    list_for_each(&list_of_strings, list_string_dump);

    printf("list_remove_at 20\n");
    list_remove_at(&list_of_strings, 20);
    list_for_each(&list_of_strings, list_string_dump);

    list_free(&list_of_strings);

}

void     test_list(void) {
    char*    words[] = {
        "123456",        /* 00 */
        "12345",         /* 01 */
        "123456789",     /* 02 */
        "password",      /* 03 */
        "iloveyou",      /* 04 */
        "princess",      /* 05 */
        "1234567",       /* 06 */
        "rockyou",       /* 07 */
        "12345678",      /* 08 */
        "abc123",        /* 09 */
        "nicole",        /* 10 */ // remove_at 10
        "daniel",        /* 11 */
        "babygirl",      /* 12 */
        "monkey",        /* 13 */
        "lovely",        /* 14 */
        "jessica",       /* 15 */
        "654321",        /* 16 */
        "michael",       /* 17 */
        "ashley",        /* 18 */
        "qwerty",        /* 19 */
        "111111",        /* 20 */
        "iloveu",        /* 21 */
        "000000",        /* 22 */
        "michelle",      /* 23 */
        "tigger",        /* 24 */
        "sunshine",      /* 25 */
        "chocolate",     /* 26 */
        "password1",     /* 27 */
        "soccer",        /* 28 */
        "anthony"        /* 29 */
    };

    s_list    list_of_strings;

    list_init(&list_of_strings, false, NULL);

    int nb_elems = sizeof(words) / sizeof(char*) ;
    for(int i=0;i<nb_elems;i++) {
        list_add(&list_of_strings, words[i]);
    }

    printf("list_for_each\n");
    list_for_each(&list_of_strings, list_string_dump);

    printf("list_for_each_with_limit\n");
    list_for_each_with_limit(&list_of_strings, list_string_dump_with_index, 10);

    printf("list_get_at 10\n");
    char* psz = (char*)list_get_at(&list_of_strings, 10);
    if ( psz != NULL ) {
        printf("\t%s\n",psz);
    }

    printf("list_get_element soccer\n");
    psz = list_get_element(&list_of_strings, "soccer", list_string_compare);
    if ( psz != NULL ) {
        printf("\t%s\n",psz);
    }

    printf("list_remove_element monkey\n");
    list_remove_element(&list_of_strings, "monkey", list_string_compare);
    list_for_each(&list_of_strings, list_string_dump);

    printf("list_remove_at\n");
    list_remove_at(&list_of_strings, 10);
    list_for_each(&list_of_strings, list_string_dump);

    list_free(&list_of_strings);
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
    fprintf(stderr,"%d strcmp(%s,%s)\n",n,psz1, psz2);
    return n;
}

