#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tests.h"
#include "hashtable.h"

void    vector_dump_string(unsigned int index, const void* pv_values);

bool    hashtable_key_string_compare(const void* pv_data1, const void* pv_data2) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    const ps_hash_entry p_hash_entry1 = (const ps_hash_entry)pv_data1;
    const ps_hash_entry p_hash_entry2 = (const ps_hash_entry)pv_data2;
#pragma GCC diagnostic pop

    return 0 == strcmp((char*)(p_hash_entry1->pv_key),(char*)(p_hash_entry2->pv_key));
}

void    test_hashtable_string_string(void) {
    char*    keys[] = {
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

    char*    values[] = {
        "1_UN",      /* 00 */
        "2_DEUX",    /* 01 */
        "3_TROIS",   /* 02 */
        "4_QUATRE",  /* 03 */
        "5_CINQ",    /* 04 */
        "6_SIX",     /* 05 */
        "7_SEPT",    /* 06 */
        "8_HUIT",    /* 07 */
        "9_NEUF",    /* 08 */
        "10_DIX"     /* 09 */
    };

    char*    new_values[] = {
        "NEW_NEW_1_UN",      /* 00 */
        "NEW_NEW_2_DEUX",    /* 01 */
        "NEW_NEW_3_TROIS",   /* 02 */
        "NEW_NEW_4_QUATRE",  /* 03 */
        "NEW_NEW_5_CINQ",    /* 04 */
        "NEW_NEW_6_SIX",     /* 05 */
        "NEW_NEW_7_SEPT",    /* 06 */
        "NEW_NEW_8_HUIT",    /* 07 */
        "NEW_NEW_9_NEUF",    /* 08 */
        "NEW_NEW_10_DIX"     /* 09 */
    };

    s_hashtable    hash_string_string ;
    hashtable_init(&hash_string_string, 4, hashtable_key_string_compare);

    int nb_elems = sizeof(keys) / sizeof(char*) ;
    for(int i=0;i<nb_elems;i++) {
        hashtable_put(&hash_string_string, keys[i], strlen(keys[i]), values[i]);
    }
    hashtable_debug(&hash_string_string);
    printf("\n");

    printf("hashtable put with existing key UN,NEW_1_UN\n");
    hashtable_put(&hash_string_string, "UN", 2, "NEW_1_UN");
    hashtable_debug(&hash_string_string);
    printf("\n");

    printf("hashtable put with existing key QUATRE,NEW_4_QUATRE\n");
    hashtable_put(&hash_string_string, "QUATRE", 6, "NEW_4_QUATRE");
    hashtable_debug(&hash_string_string);
    printf("\n");

    printf("hashtable put with existing key DIX,NEW_10_DIX\n");
    hashtable_put(&hash_string_string, "DIX", 3, "NEW_10_DIX");
    hashtable_debug(&hash_string_string);
    printf("\n");

    printf("hashtable put with existing keys \n");
    nb_elems = sizeof(keys) / sizeof(char*) ;
    for(int i=0;i<nb_elems;i++) {
        hashtable_put(&hash_string_string, keys[i], strlen(keys[i]), new_values[i]);
    }
    hashtable_debug(&hash_string_string);
    printf("\n");

    nb_elems = sizeof(keys) / sizeof(char*) ;
    for(int i=0;i<nb_elems;i++) {
        printf("hashtable_get %s\n",keys[i]);
        char* p = hashtable_get(&hash_string_string, keys[i], strlen(keys[i])) ;
        if ( p != NULL ) {
            printf("\t%s\n",p);
        } else {
            printf("\tNOT FOUND\n");
        }
    }

    printf("hashtable_get TRUC\n");
    char* p = hashtable_get(&hash_string_string, "TRUC", strlen("TRUC")) ;
    if ( p != NULL ) {
        printf("\t%s\n",p);
    } else {
        printf("\tNOT FOUND\n");
    }

    s_vector v_keys ;
    s_vector v_values ;

    printf("all keys\n");
    hashtable_keys(&hash_string_string, &v_keys);    
    vector_for_each(&v_keys, vector_dump_string);
    printf("\n");
    
    printf("all values\n");
    hashtable_values(&hash_string_string, &v_values);
    vector_for_each(&v_values, vector_dump_string);
    printf("\n");

    printf("hashtable before removes\n");
    hashtable_debug(&hash_string_string);

    printf("hashtable remove key SIX\n");
    hashtable_remove_key(&hash_string_string, "SIX", 3);
    hashtable_debug(&hash_string_string);
    printf("\n");

    printf("hashtable remove key SEPT\n");
    hashtable_remove_key(&hash_string_string, "SEPT", 4);
    hashtable_debug(&hash_string_string);
    printf("\n");

    printf("hashtable remove key QUATRE\n");
    hashtable_remove_key(&hash_string_string, "QUATRE", 6);
    hashtable_debug(&hash_string_string);
    printf("\n");

    printf("hashtable remove key QUATRE\n");
    hashtable_remove_key(&hash_string_string, "QUATRE", 6);
    hashtable_debug(&hash_string_string);
    printf("\n");

    printf("hashtable remove key QUATRE\n");
    hashtable_remove_key(&hash_string_string, "QUATRE", 6);
    hashtable_debug(&hash_string_string);
    printf("\n");
    
    vector_free(&v_keys);
    vector_free(&v_values);
    hashtable_free(&hash_string_string);
    
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

void    test_hashtable_int_cell(void) {
    s_h_int        indexes[] = {
        { 5 },{ 8 },{ 6 },{ 9 },{ 2 },{ 10 },{ 1 },{ 4 },{ 3 },{ 7 },
        { 11 },{ 12 },{ 13 },{ 14 },{ 15 },{ 16 },{ 17 },{ 18 },{ 19 },{ 20 },
        { 21 },{ 22 },{ 23 },{ 24 },{ 25 },{ 26 },{ 27 },{ 28 },{ 29 },{ 30 }
    } ;
    
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
        { 7 , "SEPT" } ,
        { 11 , "ONZE" } ,
        { 12 , "DOUZE" } ,
        { 13 , "TREIZE" } ,
        { 14 , "QUATORZE" } ,
        { 15 , "QUINZE" } ,
        { 16 , "SEIZE" } ,
        { 17 , "DIX SEPT" } ,
        { 18 , "DIX HUIT" } ,
        { 19 , "DIX NEUF" } ,
        { 20 , "VINGT" } ,
        { 21 , "VINGT ET UN" } ,
        { 22 , "VINGT DEUX" } ,
        { 23 , "VINGT TROIS" } ,
        { 24 , "VINGT QUATRE" } ,
        { 25 , "VINGT CINQ" } ,
        { 26 , "VINGT SIX" } ,
        { 27 , "VINGT SEPT" } ,
        { 28 , "VINGT HUIT" } ,
        { 29 , "VINGT NEUF" } ,
        { 30 , "TRENTE" }         
    } ;

    s_hashtable    hash_int_cell ;
    hashtable_init_hash_func(&hash_int_cell, 4, hashtable_func_hash_int, hashtable_key_struct_int_compare);

    int nb_elems = sizeof(indexes) / sizeof(s_h_int) ;
    for(int i=0;i<nb_elems;i++) {
        hashtable_put(&hash_int_cell, &(indexes[i]), sizeof(int), &(cells[i]));
    }
    hashtable_int_cell_debug(&hash_int_cell);
    printf("\n");

    hashtable_free(&hash_int_cell);
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

