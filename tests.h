#ifndef __TESTS_H__
#define __TESTS_H__

#include "buffer.h"
#include "strl.h"
#include "curl.h"
#include "list.h"
#include "vector.h"
#include "stack.h"
#include "hashtable.h"

void    test_buffer(void);
void    buffer_dump(ps_buffer p_buffer) ;


void    debug_list(ps_list p_list);

//************
// list_string
void    test_list(void) ;
void    test_list_bounds(void);
void    test_list_sorted(void);

void    list_string_dump(const void*);
void    list_string_dump_with_index(int, const void*);

int     list_string_compare(const void*, const void*);
// list_string
//************

//************
// list_struct
typedef struct data_cell {
    int        idx ;
    char       value[64];
} s_data_cell, *ps_data_cell ;

void    test_list_data_sorted(void);
void    test_list_copy(void);
void    list_data_cell_dump(const void*);
void    list_data_cell_dump_with_index(int, const void*);
int     list_data_cell_compare(const void*, const void*);
void    vector_cell_dump(unsigned int i, const void* pv_data) ;
// list_struct
//************

//************
// vector_string
void    vector_string_dump(unsigned int i, const void* pv_data);
int     vector_string_compare(const void* pv_data1, const void* pv_data2);
void    test_vector_string(void);
void    test_vector_copy(void);
// vector_string
//************

//************
// vector_struct
void    vector_data_cell_dump(unsigned int, const void*);
void    test_vector_struct(void);
// vector_struct
//************

//************
// stack_string
void    test_stack_string(void);
void    test_stack_copy(void);
// stack_string
//************

//************
// stack_struct
void    stack_data_cell_dump(unsigned int, const void*);
void    test_stack_struct(void);
// stack_struct
//************


//************
// hashtable_string
void    test_hashtable_string_string(void);
bool    hashtable_key_string_compare(const void* pv_data1, const void* pv_data2);

// hashtable_string
//************

//************
// hashtable_struct
typedef struct h_int {
    int    idx;
} s_h_int, *ps_h_int;

unsigned int hashtable_func_hash_int(void* pv_data, size_t size);
bool    hashtable_key_struct_int_compare(const void* pv_data1, const void* pv_data2) ;
void    test_hashtable_int_cell(void);
void    hashtable_int_cell_debug_dump_vector_kv(unsigned int index, const void* p_kv) ;
void    hashtable_int_cell_debug_dump_vector_entries(unsigned int index, const void* pv_vector_of_values) ;
void    hashtable_int_cell_debug(ps_hashtable p_hashtable) ;
// hashtable_struct
//************


//************
// btree_struct
void    test_btree_int_cell(void);
void    test_btree_int_cell_big(void);
void    test_btree_int_cell_remove(void);
void    test_btree_int_cell_remove_big(void);
void    test_btree_int_cell_rebuild(void);
void    test_btree_rebuild(void);
// hashtable_struct
//************


#endif /* __TESTS_H__ */


