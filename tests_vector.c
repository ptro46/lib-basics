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

void    test_vector_string(void) {
    char*    words[] = {
        "1",      /* 00 */
        "2",      /* 01 */
        "3",      /* 02 */
        "4",      /* 03 */
        "5",      /* 04 */
        "6",      /* 05 */
        "7",      /* 06 */
        "8",      /* 07 */
        "9",      /* 08 */
        "10"      /* 09 */
    };
    s_vector    vector_of_strings;

    vector_init(&vector_of_strings, 8);

    int nb_elems = sizeof(words) / sizeof(char*) ;
    for(int i=0;i<nb_elems;i++) {
        vector_add_element(&vector_of_strings, words[i]);
    }
    printf("vector_for_each capacity(%u) nb_elements(%u)\n",vector_of_strings.capacity, vector_of_strings.nb_elements);
    vector_for_each(&vector_of_strings, vector_string_dump);

    vector_set_element_at(&vector_of_strings, "TROIS",2);
    printf("vector_set_element_at,09,8 capacity(%u) nb_elements(%u)\n",vector_of_strings.capacity, vector_of_strings.nb_elements);
    vector_for_each(&vector_of_strings, vector_string_dump);

    vector_insert_element_at(&vector_of_strings, "A",2);
    printf("vector_insert_element_at,A,8 capacity(%u) nb_elements(%u)\n",vector_of_strings.capacity, vector_of_strings.nb_elements);
    vector_for_each(&vector_of_strings, vector_string_dump);

    vector_insert_element_at(&vector_of_strings, "B",2);
    printf("vector_insert_element_at,B,8 capacity(%u) nb_elements(%u)\n",vector_of_strings.capacity, vector_of_strings.nb_elements);
    vector_for_each(&vector_of_strings, vector_string_dump);

    vector_insert_element_at(&vector_of_strings, "C",2);
    printf("vector_insert_element_at,C,8 capacity(%u) nb_elements(%u)\n",vector_of_strings.capacity, vector_of_strings.nb_elements);
    vector_for_each(&vector_of_strings, vector_string_dump);

    vector_insert_element_at(&vector_of_strings, "D",2);
    printf("vector_insert_element_at,D,8 capacity(%u) nb_elements(%u)\n",vector_of_strings.capacity, vector_of_strings.nb_elements);
    vector_for_each(&vector_of_strings, vector_string_dump);

    vector_remove_element_at(&vector_of_strings, 6);
    printf("vector_remove_element_at,6 capacity(%u) nb_elements(%u)\n",vector_of_strings.capacity, vector_of_strings.nb_elements);
    vector_for_each(&vector_of_strings, vector_string_dump);

    unsigned int index = vector_index_of(&vector_of_strings, "5", vector_string_compare);
    printf("vector_index_of,5 capacity(%u) nb_elements(%u) : %u\n",vector_of_strings.capacity, vector_of_strings.nb_elements,index);

    vector_remove_element(&vector_of_strings, "5", vector_string_compare);
    printf("vector_remove_element,5 capacity(%u) nb_elements(%u)\n",vector_of_strings.capacity, vector_of_strings.nb_elements);
    vector_for_each(&vector_of_strings, vector_string_dump);
    
    vector_free(&vector_of_strings);
}

void    test_vector_copy(void) {
    char*    words[] = {
        "1",      /* 00 */
        "2",      /* 01 */
        "3",      /* 02 */
        "4",      /* 03 */
        "5",      /* 04 */
        "6",      /* 05 */
        "7",      /* 06 */
        "8",      /* 07 */
        "9",      /* 08 */
        "10"      /* 09 */
    };
    s_vector    vector_of_strings;
    s_vector    v_copy;
    s_list      l_copy;

    vector_init(&vector_of_strings, 8);

    int nb_elems = sizeof(words) / sizeof(char*) ;
    for(int i=0;i<nb_elems;i++) {
        vector_add_element(&vector_of_strings, words[i]);
    }

    vector_copy(&vector_of_strings, &v_copy);
    vector_to_list(&vector_of_strings, &l_copy);
    
    printf("vector_for_each vector_for_each capacity(%u) nb_elements(%u)\n",vector_of_strings.capacity, vector_of_strings.nb_elements);
    vector_for_each(&vector_of_strings, vector_string_dump);

    printf("vector_for_each v_copy capacity(%u) nb_elements(%u)\n",vector_of_strings.capacity, vector_of_strings.nb_elements);
    vector_for_each(&v_copy, vector_string_dump);

    printf("list_for_each l_copy\n");
    list_for_each_with_limit(&l_copy, list_string_dump_with_index, 40);

    vector_free(&vector_of_strings);
    vector_free(&v_copy);
    list_free(&l_copy);
}

void    vector_data_cell_dump(unsigned int i, const void* pv_data) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    const ps_data_cell p_cell = (const ps_data_cell)pv_data ;
#pragma GCC diagnostic pop
    printf("\t%d:{%d %s}\n",i,p_cell->idx, p_cell->value);
}

void    test_vector_struct(void) {
    s_data_cell    cells[] = {
        { 5 , "CINQ" } ,
        { 8 , "HUIT" } ,
        { 6 , "SIX" } ,
        { 9 , "NEUF" } ,
        { 2 , "DEUX" } ,
        { 10 , "DIX" } ,
        { 1 , "UN" } ,
        { 4 , "QUATRE" } ,
        { 3 , "TROIS" } ,
        { 7 , "SEPT" }
    } ;

    s_data_cell    cell_insert_1 = {21,"VINT UN"};
    s_data_cell    cell_insert_2 = {32,"TRENTE DEUX"};
    s_data_cell    cell_insert_3 = {43,"QUARENTE TROIS"};

    s_vector    vector_of_cells ;
    s_vector    v_copy ;
    s_list      l_copy ;

    vector_init(&vector_of_cells, 8);

    int nb_elems = sizeof(cells) / sizeof(s_data_cell) ;
    for(int i=0;i<nb_elems;i++) {
        vector_add_element(&vector_of_cells, &cells[i]);
    }
    
    printf("vector_for_each vector_of_cells capacity(%u) nb_elements(%u)\n",vector_of_cells.capacity, vector_of_cells.nb_elements);
    vector_for_each(&vector_of_cells, vector_data_cell_dump);

    vector_insert_element_at(&vector_of_cells, &cell_insert_1 ,2);
    printf("vector_insert_element_at,2 capacity(%u) nb_elements(%u)\n",vector_of_cells.capacity, vector_of_cells.nb_elements);
    vector_for_each(&vector_of_cells, vector_data_cell_dump);

    vector_insert_element_at(&vector_of_cells, &cell_insert_2 ,6);
    printf("vector_insert_element_at,6 capacity(%u) nb_elements(%u)\n",vector_of_cells.capacity, vector_of_cells.nb_elements);
    vector_for_each(&vector_of_cells, vector_data_cell_dump);

    vector_insert_element_at(&vector_of_cells, &cell_insert_3 ,8);
    printf("vector_insert_element_at,8 capacity(%u) nb_elements(%u)\n",vector_of_cells.capacity, vector_of_cells.nb_elements);
    vector_for_each(&vector_of_cells, vector_data_cell_dump);

    vector_copy(&vector_of_cells, &v_copy);
    vector_to_list(&vector_of_cells, &l_copy);

    printf("vector_for_each v_copy capacity(%u) nb_elements(%u)\n",vector_of_cells.capacity, vector_of_cells.nb_elements);
    vector_for_each(&v_copy, vector_data_cell_dump);

    printf("list_for_each l_copy\n");
    list_for_each_with_limit(&l_copy, list_data_cell_dump_with_index, 40);

    vector_free(&vector_of_cells);
    vector_free(&v_copy);
    list_free(&l_copy);
}
