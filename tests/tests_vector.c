#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tests.h"

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

void    test_vector_struct_add_vector(void) {
    s_data_cell    cells_1[] = {
        { 1 , "UN" } ,
        { 2 , "DEUX" } ,
        { 3 , "TROIS" } ,
        { 4 , "QUATRE" } ,
        { 5 , "CINQ" } ,
        { 6 , "SIX" } ,
        { 7 , "SEPT" } ,
        { 8 , "HUIT" } ,
        { 9 , "NEUF" } ,
        { 10 , "DIX" }
    } ;

    s_data_cell    cells_2[] = {
        { 11 , "ONE" } ,
        { 12 , "DOUZE" } ,
        { 13 , "TREIZE" } ,
        { 14 , "QUATORZE" } ,
        { 15 , "QUINZE" } ,
        { 16 , "SEIZE" } ,
        { 17 , "DIX-SEPT" } ,
        { 18 , "DIX-HUIT" } ,
        { 19 , "DIX-NEUF" } ,
        { 20 , "VINGT" }
    } ;

    s_vector    vector_1 ;
    s_vector    vector_2 ;

    vector_init(&vector_1, 8);
    int nb_elems = sizeof(cells_1) / sizeof(s_data_cell) ;
    for(int i=0;i<nb_elems;i++) {
        vector_add_element(&vector_1, &cells_1[i]);
    }

    vector_init(&vector_2, 8);
    nb_elems = sizeof(cells_2) / sizeof(s_data_cell) ;
    for(int i=0;i<nb_elems;i++) {
        vector_add_element(&vector_2, &cells_2[i]);
    }

    printf("vector_1, capacity(%u) nb_elements(%u)\n",vector_1.capacity, vector_1.nb_elements);
    vector_for_each(&vector_1, vector_data_cell_dump);

    printf("vector_2, capacity(%u) nb_elements(%u)\n",vector_2.capacity, vector_2.nb_elements);
    vector_for_each(&vector_2, vector_data_cell_dump);

    vector_add_vector(&vector_2, &vector_1);

    printf("after add vector vector_1, capacity(%u) nb_elements(%u)\n",vector_1.capacity, vector_1.nb_elements);
    vector_for_each(&vector_1, vector_data_cell_dump);

    vector_free(&vector_1);
    vector_free(&vector_2);
}
