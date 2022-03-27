#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tests.h"

void    stack_string_dump(unsigned int, const void*);

void    test_stack_string(void) {
    char*    words[] = {
        "UN",      /* 00 */
        "DEUX",    /* 01 */
        "TROIS",   /* 02 */
        "QUATRE",  /* 03 */
        "CINQ",    /* 04 */
        "SIX",     /* 05 */
        "SEPT",    /* 06 */
        "HUIT",    /* 07 */
        "NEUF",    /* 08 */
        "DIX"      /* 09 */
    };
    char* p;
    
    s_stack_lifo stack;
    stack_init(&stack, 10);

    int nb_elems = sizeof(words) / sizeof(char*) ;
    for(int i=0;i<nb_elems;i++) {
        stack_lifo_push(&stack, words[i]);
    }

    printf("stack create\n");
    stack_for_each(&stack, stack_string_dump);

    p = stack_lifo_pop(&stack);
    printf("stack pop %s\n",p);
    stack_for_each(&stack, stack_string_dump);

    p = stack_lifo_pop(&stack);
    printf("stack pop %s\n",p);
    stack_for_each(&stack, stack_string_dump);

    stack_lifo_swap(&stack);
    printf("stack swap\n");
    stack_for_each(&stack, stack_string_dump);

    stack_lifo_dup(&stack);
    printf("stack dup\n");
    stack_for_each(&stack, stack_string_dump);
    
    stack_free(&stack);
}

void    test_stack_copy(void) {
    char*    words[] = {
        "UN",      /* 00 */
        "DEUX",    /* 01 */
        "TROIS",   /* 02 */
        "QUATRE",  /* 03 */
        "CINQ",    /* 04 */
        "SIX",     /* 05 */
        "SEPT",    /* 06 */
        "HUIT",    /* 07 */
        "NEUF",    /* 08 */
        "DIX"      /* 09 */
    };
    s_stack_lifo stack;
    s_vector    v_copy;
    s_list      l_copy;

    stack_init(&stack, 10);
    int nb_elems = sizeof(words) / sizeof(char*) ;
    for(int i=0;i<nb_elems;i++) {
        stack_lifo_push(&stack, words[i]);
    }

    stack_to_list(&stack, &l_copy);
    stack_to_vector(&stack, &v_copy);
    
    printf("stack create\n");
    stack_for_each(&stack, stack_string_dump);


    printf("vector_for_each v_copy capacity(%u) nb_elements(%u)\n",v_copy.capacity, v_copy.nb_elements);
    vector_for_each(&v_copy, vector_string_dump);

    printf("list_for_each l_copy\n");
    list_for_each_with_limit(&l_copy, list_string_dump_with_index, 40);

    stack_free(&stack);
    vector_free(&v_copy);
    list_free(&l_copy);
}

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

void    test_stack_struct(void) {
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

    s_stack_lifo    stack_of_cells ;
    s_vector        v_copy ;
    s_list          l_copy ;

    stack_init(&stack_of_cells, 10);

    int nb_elems = sizeof(cells) / sizeof(s_data_cell) ;
    for(int i=0;i<nb_elems;i++) {
        stack_lifo_push(&stack_of_cells, &cells[i]);
    }

    stack_to_list(&stack_of_cells, &l_copy);
    stack_to_vector(&stack_of_cells, &v_copy);
    
    printf("stack create\n");
    stack_for_each(&stack_of_cells, stack_data_cell_dump);


    printf("vector_for_each v_copy capacity(%u) nb_elements(%u)\n",v_copy.capacity, v_copy.nb_elements);
    vector_for_each(&v_copy, vector_data_cell_dump);

    printf("list_for_each l_copy\n");
    list_for_each_with_limit(&l_copy, list_data_cell_dump_with_index, 40);

    stack_free(&stack_of_cells);
    vector_free(&v_copy);
    list_free(&l_copy);
}
