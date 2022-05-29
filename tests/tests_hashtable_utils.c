#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tests.h"
#include "hashtable.h"

bool    hashtable_key_string_compare(const void* pv_data1, const void* pv_data2) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    const ps_hash_entry p_hash_entry1 = (const ps_hash_entry)pv_data1;
    const ps_hash_entry p_hash_entry2 = (const ps_hash_entry)pv_data2;
#pragma GCC diagnostic pop

    return 0 == strcmp((char*)(p_hash_entry1->pv_key),(char*)(p_hash_entry2->pv_key));
}

void    vector_dump_string(unsigned int index, const void* pv_values) {
    printf("\t%s\n",(const char*)pv_values);
}

bool    hashtable_key_struct_int_compare(const void* pv_data1, const void* pv_data2) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    const ps_hash_entry p_hash_entry1 = (const ps_hash_entry)pv_data1;
    ps_h_int p_key_int_1 = (ps_h_int)p_hash_entry1->pv_key;
    
    const ps_hash_entry p_hash_entry2 = (const ps_hash_entry)pv_data2;    
    ps_h_int p_key_int_2 = (ps_h_int)p_hash_entry2->pv_key;
#pragma GCC diagnostic pop

    return p_key_int_1->idx == p_key_int_2->idx ;
}

unsigned int hashtable_func_hash_int(void* pv_data, size_t size) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    ps_h_int p_key_int = (ps_h_int)pv_data ;    
#pragma GCC diagnostic pop
    return p_key_int->idx ;
}

void    hashtable_int_cell_debug_dump_vector_kv(unsigned int index, const void* p_kv) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    const ps_hash_entry p_key_value = (const ps_hash_entry)p_kv;
    ps_h_int p_key = (ps_h_int)p_key_value->pv_key;
    ps_data_cell p_value = (ps_data_cell)p_key_value->pv_value ;
#pragma GCC diagnostic pop
    printf("{%d:%ld,%d:%s} ",p_key->idx, p_key_value->key_size,p_value->idx, p_value->value);
}

void    hashtable_int_cell_debug_dump_vector_entries(unsigned int index, const void* pv_vector_of_values) {
    if ( pv_vector_of_values != NULL ) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
        const ps_vector p_array_of_values = (const ps_vector)pv_vector_of_values;
#pragma GCC diagnostic pop
        printf("\t%u:[%u]:",index,p_array_of_values->nb_elements);
        vector_for_each(p_array_of_values, hashtable_int_cell_debug_dump_vector_kv);
        printf("\n");
    }
}

void    hashtable_int_cell_debug(ps_hashtable p_hashtable) {
    printf("hashtable\n");
    printf("\tnb_elements : %u\n",p_hashtable->nb_elements);
    vector_for_each_capacity(&(p_hashtable->v_entries),hashtable_int_cell_debug_dump_vector_entries);
}
