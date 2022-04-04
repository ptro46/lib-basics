#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "tests.h"

void    test_rebuild_with_pivot(ps_vector p_vector_of_kv, int index_min, int index_max) ;

int main(int argc, char** argv) {
    /*
      test_buffer();
      test_list();
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
    */
//    test_btree_int_cell();
//    test_btree_int_cell_big();
//    test_btree_int_cell_remove();
//    test_btree_int_cell_remove_big();
//    test_btree_int_cell_rebuild();
    test_btree_rebuild();

    /*
    s_h_int        values[] = {
        { 1 },
        { 2 },
        { 3 },
        { 4 },
        { 5 },
        { 6 },
        { 7 },
        { 8 },
        { 9 },
        { 10 }
    } ;

    s_vector v_of_kv ;

    int nb_elems = sizeof(values) / sizeof(s_h_int) ;
    vector_init(&v_of_kv, nb_elems);
    for(int i=0;i<nb_elems;i++) {
        vector_add_element(&v_of_kv, &values[i]);
    }

    test_rebuild_with_pivot(&v_of_kv, 0, nb_elems-1);
    printf("\n");
    vector_free(&v_of_kv);
    */
    return 0;
}

void    test_rebuild_with_pivot(ps_vector p_vector_of_kv, int index_min, int index_max) {
    ps_h_int p_kv ;
    int sample_size = index_max - index_min + 1 ;
    int pivot = 0 ;

    if ( sample_size == 1 ) {
        p_kv = vector_element_at(p_vector_of_kv, index_min);
        printf("%d ",p_kv->idx);
        
    } else if ( sample_size == 2 ) {
        p_kv = vector_element_at(p_vector_of_kv, index_max);
        printf("%d ",p_kv->idx);

        p_kv = vector_element_at(p_vector_of_kv, index_min);
        printf("%d ",p_kv->idx);
        
    } else {
        pivot = (int)sample_size / 2 ;

        p_kv = vector_element_at(p_vector_of_kv, index_min + pivot);
        printf("%d ",p_kv->idx);

        test_rebuild_with_pivot(p_vector_of_kv, index_min, index_min + pivot - 1);
        test_rebuild_with_pivot(p_vector_of_kv, index_min + pivot + 1, index_max);
        
    }
}

