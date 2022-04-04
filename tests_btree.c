#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "tests.h"
#include "btree.h"
#include "list.h"
#include "vector.h"
#include "hashtable.h"

int    btree_key_struct_int_compare(const void* pv_data1, const void* pv_data2) ;
void   key_to_string(const void* pv_key, ps_buffer p_buffer);
void   value_to_string(const void* pv_value, ps_buffer p_buffer);

void   key_to_string_psz(const void* pv_key, char* p_buffer);
void   value_to_string_psz(const void* pv_value, char* p_buffer);

void   callback_for_each(const void* pv_key, const void* pv_value);
void   callback_for_each_with_parameters_list(const void* pv_key, const void* pv_value, const void* pv_param1, void* pv_param2);
void   callback_for_each_with_parameters_hashtable(const void* pv_key, const void* pv_value, const void* pv_param1, void* pv_param2);
void   callback_for_each_with_parameters_vector(const void* pv_key, const void* pv_value, const void* pv_param1, void* pv_param2);

static bool verify_list_order(ps_list p_list) ;
static void prepare_load_datas(int size_of_sample, ps_h_int* p_ar_indexes, ps_data_cell* p_ar_cells, ps_h_int* p_ar_key_remove) ;

//void    rebuild_with_pivot(ps_btree p_tree, ps_vector p_vector_of_kv, int index_min, int index_max) ;

void    test_btree_int_cell(void) {
/*
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

  s_h_int to_find[] = { { 5 }, { 1 }, { 4 }, { 6 }, { 7 }, { 11 }, { 30 }, { 45 } } ;
*/
/*
  s_h_int        indexes[] = {
  { 40 },{ 50 },{ 14 },{ 16 },{ 5 },{ 3 },{ 7 },{ 55 },{ 45 }, { 28 } ,
  { 31 },{ 42 },{ 12 },{ 18 },{ 6 },{ 4 },{ 8 },{ 56 },{ 46 }, { 29 } ,
  { 32 },{ 43 },{ 15 },{ 19 },{ 10 },{ 11 },{ 13 },{ 57 },{ 47 }, { 33 } 
  } ;
    
  s_data_cell    cells[] = {
  { 40 , "QUARANTE" } ,
  { 50 , "CINQUANTE" } ,
  { 14 , "QUATORZE" } ,
  { 16 , "SEIZE" } ,
  { 5 , "CINQ" } ,
  { 3 , "TROIS" } ,
  { 7 , "SEPT" } ,
  { 55 , "CINQUANTE CINQ" } ,
  { 45 , "QUARANTE CINQ" } ,
  { 28 , "VINGT HUIT" } ,
  { 31 , "TRENTE ET UN"},
  { 42 , "QUARANTE DEUX"},
  { 12 , "DOUZE"},
  { 18 , "DIX HUIT"},
  { 6 , "SIX"},
  { 4 , "QUATRE"},
  { 8 , "HUIT"},
  { 56 , "CINQUANTE SIX"},
  { 46 , "QUARANTE SIX"},
  { 29 , "VINGT NEUF"} ,
  { 32 , "TRENTE DEUX"},
  { 43 , "QUARANTE TROIS"},
  { 15 , "QUINZE"},
  { 19 , "DIX NEUF"},
  { 10 , "DIX"},
  { 11 , "ONZE"},
  { 13 , "TREIZE"},
  { 57 , "CINQUANTE SEPT"},
  { 47 , "QUARANTE SEPT"},
  { 33 , "TRENTE TROIS"} 

  } ;
*/

    s_h_int        indexes[] = {
        { 66 },
        { 50 },
        { 76 },
        { 37 },
        { 56 },
        { 70 },
        { 81 },
        { 36 },
        { 44 },
        { 55 },
        { 68 },
        { 73 },
        { 80 },
        { 97 },
        { 35 },
        { 52 },
        { 72 },
//        { 74 },
        { 94 },
        { 51 },
        { 71 },
        { 88 }
    } ;
    
    s_data_cell    cells[] = {
        { 66 ,"66"},
        { 50 ,"50"},
        { 76 ,"76"},
        { 37 ,"37"},
        { 56 ,"56"},
        { 70 ,"70"},
        { 81 ,"81"},
        { 36 ,"36"},
        { 44 ,"44"},
        { 55 ,"55"},
        { 68 ,"68"},
        { 73 ,"73"},
        { 80 ,"80"},
        { 97 ,"97"},
        { 35 ,"35"},
        { 52 ,"52"},
        { 72 ,"72"},
//        { 74 ,"74"},
        { 94 ,"94"},
        { 51 ,"51"},
        { 71 ,"71"},
        { 88 ,"88"}

    } ;

    s_h_int to_find[] = {
        { 50 },{ 72 }
    } ;

    s_btree      tree_int_cell ;
    s_buffer     buf_value;
    
    s_list       list_of_kv_infixe ;
    s_list       list_of_kv_prefixe ;
    s_list       list_of_kv_postfixe ;
    
    s_hashtable  hashtable_int_cell_infixe;
    s_hashtable  hashtable_int_cell_prefixe;
    s_hashtable  hashtable_int_cell_postfixe;

    btree_init(&tree_int_cell, btree_key_struct_int_compare);
    buffer_init(&buf_value, 128);

    list_init(&list_of_kv_infixe,false,NULL);
    list_init(&list_of_kv_prefixe,false,NULL);
    list_init(&list_of_kv_postfixe,false,NULL);

    hashtable_init(&hashtable_int_cell_infixe, 20, hashtable_key_struct_int_compare);
    hashtable_init(&hashtable_int_cell_prefixe, 20, hashtable_key_struct_int_compare);
    hashtable_init(&hashtable_int_cell_postfixe, 20, hashtable_key_struct_int_compare);
    
    int nb_elems = sizeof(indexes) / sizeof(s_h_int) ;
    for(int i=0;i<nb_elems;i++) {
        btree_put(&tree_int_cell, &(indexes[i]), &(cells[i]));
    }

    btree_to_dot(&tree_int_cell, "tree_int_cell.dot", key_to_string, value_to_string);

    nb_elems = sizeof(to_find) / sizeof(s_h_int) ;
    for(int i=0;i<nb_elems;i++) {
        void* p_void = btree_get(&tree_int_cell, &(to_find[i])) ;
        if ( p_void != NULL ) {
            buffer_reset(&buf_value);
            value_to_string(p_void, &buf_value);
            printf("found for key %d --> %s\n",to_find[i].idx, buffer_stringify(&buf_value));
        } else {
            printf("not found for key %d\n",to_find[i].idx);
        }
    }

    printf("parcours infixe\n");
    btree_foreach_infix(&tree_int_cell, callback_for_each);

    printf("parcours prefixe\n");
    btree_foreach_prefix(&tree_int_cell, callback_for_each);

    printf("parcours postfixe\n");
    btree_foreach_postfix(&tree_int_cell, callback_for_each);

    btree_foreach_infix_with_parameter(&tree_int_cell, callback_for_each_with_parameters_list, NULL, &list_of_kv_infixe);
    btree_foreach_prefix_with_parameter(&tree_int_cell, callback_for_each_with_parameters_list, NULL, &list_of_kv_prefixe);
    btree_foreach_postfix_with_parameter(&tree_int_cell, callback_for_each_with_parameters_list, NULL, &list_of_kv_postfixe);

    btree_foreach_infix_with_parameter(&tree_int_cell, callback_for_each_with_parameters_hashtable, NULL, &hashtable_int_cell_infixe);
    btree_foreach_prefix_with_parameter(&tree_int_cell, callback_for_each_with_parameters_hashtable, NULL, &hashtable_int_cell_prefixe);
    btree_foreach_postfix_with_parameter(&tree_int_cell, callback_for_each_with_parameters_hashtable, NULL, &hashtable_int_cell_postfixe);


    printf("list_for_each infixe\n");
    list_for_each_with_limit(&list_of_kv_infixe, list_data_cell_dump_with_index, 40);

    printf("list_for_each prefixe\n");
    list_for_each_with_limit(&list_of_kv_prefixe, list_data_cell_dump_with_index, 40);

    printf("list_for_each postfixe\n");
    list_for_each_with_limit(&list_of_kv_postfixe, list_data_cell_dump_with_index, 40);

    
    printf("hashtable infixe\n");
    hashtable_int_cell_debug(&hashtable_int_cell_infixe);
    printf("\n");

    printf("hashtable prefixe\n");
    hashtable_int_cell_debug(&hashtable_int_cell_prefixe);
    printf("\n");

    printf("hashtable postfixe\n");
    hashtable_int_cell_debug(&hashtable_int_cell_postfixe);
    printf("\n");

    list_free(&list_of_kv_infixe);
    list_free(&list_of_kv_prefixe);
    list_free(&list_of_kv_postfixe);

    hashtable_free(&hashtable_int_cell_infixe);
    hashtable_free(&hashtable_int_cell_prefixe);
    hashtable_free(&hashtable_int_cell_postfixe);

    buffer_free(&buf_value);
    btree_free(&tree_int_cell);
}

void    test_btree_int_cell_big(void) {
    s_h_int         search_index;
    ps_data_cell    cell_found;
    
    ps_h_int        ar_indexes ;
    ps_data_cell    ar_cells ;
    s_btree         tree_int_cell ;
    s_hashtable     hash_keys;
    int             size_of_sample = 100 ;
    char            buf_int[14];
    int             i_search;

    btree_init(&tree_int_cell, btree_key_struct_int_compare);
    hashtable_init_hash_func(&hash_keys, 2*size_of_sample , hashtable_func_hash_int, hashtable_key_struct_int_compare);

    ar_indexes = calloc(size_of_sample, sizeof(s_h_int));
    ar_cells = calloc(size_of_sample, sizeof(s_data_cell));

    srand(time(NULL));
    
    ar_indexes[0].idx = (int)size_of_sample/2;
    ar_cells[0].idx = (int)size_of_sample/2;
    sprintf(buf_int,"%d",ar_cells[0].idx);
    strcpy(ar_cells[0].value, buf_int);
    hashtable_put(&hash_keys, &(ar_indexes[0]), sizeof(int), &(ar_cells[0]));
    for(int i=1;i<size_of_sample;i++) {
        i_search = 0 ;
        search_index.idx = rand() % size_of_sample ;
        cell_found = hashtable_get(&hash_keys, &search_index, sizeof(s_h_int));
        while ( cell_found != NULL && i_search < 10 ) {
            i_search++;
            search_index.idx = rand() % size_of_sample ;
            cell_found = hashtable_get(&hash_keys, &search_index, sizeof(s_h_int));
        }

        ar_indexes[i].idx = search_index.idx ;
        ar_cells[i].idx = search_index.idx ;
        sprintf(buf_int,"%d",search_index.idx);
        strcpy(ar_cells[i].value, buf_int);
        hashtable_put(&hash_keys, &(ar_indexes[i]), sizeof(int), &(ar_cells[i]));
    }

    for(int i=0;i<size_of_sample;i++) {
        btree_put(&tree_int_cell, &(ar_indexes[i]), &(ar_cells[i]));
    }

    btree_to_dot(&tree_int_cell, "tree_int_cell.dot", key_to_string, value_to_string);

    printf("parcours infixe\n");
    btree_foreach_infix(&tree_int_cell, callback_for_each);

    printf("parcours prefixe\n");
    btree_foreach_prefix(&tree_int_cell, callback_for_each);

    printf("parcours postfixe\n");
    btree_foreach_postfix(&tree_int_cell, callback_for_each);

    
    free(ar_cells);
    free(ar_indexes);
    
    hashtable_free(&hash_keys);
    btree_free(&tree_int_cell);
}

int    btree_key_struct_int_compare(const void* pv_data1, const void* pv_data2) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    ps_h_int p_key_int_1 = (ps_h_int)pv_data1 ;
    ps_h_int p_key_int_2 = (ps_h_int)pv_data2;
#pragma GCC diagnostic pop

    return p_key_int_1->idx - p_key_int_2->idx ;
}

void   key_to_string(const void* pv_key, ps_buffer p_buffer) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    ps_h_int p_key = (ps_h_int)pv_key ;
#pragma GCC diagnostic pop
    buffer_append_f(p_buffer, "%d",p_key->idx);
}

void   value_to_string(const void* pv_value, ps_buffer p_buffer) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    ps_data_cell p_value = (ps_data_cell)pv_value ;
#pragma GCC diagnostic pop
    buffer_append_f(p_buffer, " %d:%s ",p_value->idx,p_value->value);
}

void   callback_for_each(const void* pv_key, const void* pv_value) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    ps_h_int p_key = (ps_h_int)pv_key ;
    ps_data_cell p_value = (ps_data_cell)pv_value ;
#pragma GCC diagnostic pop
    printf("\t%d %d/%s\n",p_key->idx,p_value->idx,p_value->value);
}

void   callback_for_each_with_parameters_list(const void* pv_key, const void* pv_value, const void* pv_param1, void* pv_param2) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
//    ps_h_int p_key = (ps_h_int)pv_key ;
    ps_data_cell p_value = (ps_data_cell)pv_value ;
    ps_list p_list = (ps_list)pv_param2;
#pragma GCC diagnostic pop
    list_add(p_list, p_value);
}

void   callback_for_each_with_parameters_hashtable(const void* pv_key, const void* pv_value, const void* pv_param1, void* pv_param2) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    ps_h_int p_key = (ps_h_int)pv_key ;
    ps_data_cell p_value = (ps_data_cell)pv_value ;
    ps_hashtable p_hash = (ps_hashtable)pv_param2;
#pragma GCC diagnostic pop
    hashtable_put(p_hash, p_key, sizeof(int), p_value);
}

void   callback_for_each_with_parameters_vector(const void* pv_key, const void* pv_value, const void* pv_param1, void* pv_param2) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    ps_vector p_vector = (ps_vector)pv_param2;
    ps_kv p_kv = calloc(1,sizeof(s_kv));
    p_kv->pv_key = (void*)pv_key ;
    p_kv->pv_value = (void*)pv_value ;
#pragma GCC diagnostic pop
    vector_add_element(p_vector, p_kv);
}

void    test_btree_int_cell_remove(void) {
    s_h_int        indexes[] = {
        { 66 },
        { 50 },
        { 76 },
        { 37 },
        { 56 },
        { 70 },
        { 81 },
        { 36 },
        { 44 },
        { 55 },
        { 68 },
        { 73 },
        { 80 },
        { 97 },
        { 35 },
        { 45 } ,
        { 52 },
        { 72 },
        { 74 },
        { 94 },
        { 51 },
        { 71 },
        { 88 }
    } ;
    
    s_data_cell    cells[] = {
        { 66 ,"66"},
        { 50 ,"50"},
        { 76 ,"76"},
        { 37 ,"37"},
        { 56 ,"56"},
        { 70 ,"70"},
        { 81 ,"81"},
        { 36 ,"36"},
        { 44 ,"44"},
        { 55 ,"55"},
        { 68 ,"68"},
        { 73 ,"73"},
        { 80 ,"80"},
        { 97 ,"97"},
        { 35 ,"35"},
        { 45 ,"45"} ,
        { 52 ,"52"},
        { 72 ,"72"},
        { 74 ,"74"},
        { 94 ,"94"}, // { 94 ,"94"} { 98 ,"98"}
        { 51 ,"51"},
        { 71 ,"71"},
        { 88 ,"88"}  // { 88 ,"88"} { 99 ,"99"}
    } ;

    s_h_int to_find[] = {
        { 76 }
    } ;

    s_btree      tree_int_cell ;

    btree_init(&tree_int_cell, btree_key_struct_int_compare);
    
    int nb_elems = sizeof(indexes) / sizeof(s_h_int) ;
    for(int i=0;i<nb_elems;i++) {
        btree_put(&tree_int_cell, &(indexes[i]), &(cells[i]));
    }

    btree_to_dot(&tree_int_cell, "tree_int_cell_before.dot", key_to_string, value_to_string);

    nb_elems = sizeof(to_find) / sizeof(s_h_int) ;
    for(int i=0;i<nb_elems;i++) {
        btree_remove_key(&tree_int_cell, &(to_find[i])) ;
    }

    btree_to_dot(&tree_int_cell, "tree_int_cell_after.dot", key_to_string, value_to_string);


    btree_free(&tree_int_cell);
}

void   key_to_string_psz(const void* pv_key, char* p_buffer) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    ps_h_int p_key = (ps_h_int)pv_key ;
#pragma GCC diagnostic pop
    sprintf(p_buffer, "%d",p_key->idx);
}

void   value_to_string_psz(const void* pv_value, char* p_buffer) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    ps_data_cell p_value = (ps_data_cell)pv_value ;
#pragma GCC diagnostic pop
    sprintf(p_buffer, "%d:%s ",p_value->idx,p_value->value);
}

static void
prepare_load_datas(int size_of_sample, ps_h_int* p_ar_indexes, ps_data_cell* p_ar_cells, ps_h_int* p_ar_key_remove) {
    s_h_int         search_index;
    ps_data_cell    cell_found;

    char            buf_int[14];
    int             i_search;
    s_hashtable     hash_keys;

    struct stat    st;
    FILE*          h_values ;
    FILE*          h_remove ;

    int            i_rand_value ;

    hashtable_init_hash_func(&hash_keys, 2*size_of_sample , hashtable_func_hash_int, hashtable_key_struct_int_compare);

    (*p_ar_indexes) = calloc(size_of_sample, sizeof(s_h_int));
    (*p_ar_key_remove) = calloc(size_of_sample, sizeof(s_h_int));
    (*p_ar_cells) = calloc(size_of_sample, sizeof(s_data_cell));

    bool read_from_cache = false ;
    if ( 0 == stat("ar_values.bin",&st) ) {
        if ( 0 == stat("ar_remove.bin",&st) ) {
            read_from_cache = true ;
        }
    }

    if ( true == read_from_cache ) {
        printf("read_from_cache\n");
        h_values = fopen("ar_values.bin","rb") ;
        h_remove = fopen("ar_remove.bin","rb") ;
        fread((*p_ar_indexes), sizeof(s_h_int), size_of_sample, h_values);
        fread((*p_ar_key_remove), sizeof(s_h_int), size_of_sample, h_remove);
        fclose(h_values);
        fclose(h_remove);

        printf("ar_indexes\n");
        for(int i=0; i<size_of_sample; i++) {
            printf("%d ",(*p_ar_indexes)[i].idx);
        }
        printf("\n");

        printf("ar_remove\n");
        for(int i=0; i<size_of_sample; i++) {
            printf("%d ",(*p_ar_key_remove)[i].idx);
        }
        printf("\n");

        for(int i=0;i<size_of_sample;i++) {
            (*p_ar_cells)[i].idx = (*p_ar_indexes)[i].idx;
            sprintf(buf_int,"%d",(*p_ar_indexes)[i].idx);
            strcpy((*p_ar_cells)[i].value, buf_int);
        }

    } else {
        printf("build_cache\n");
        srand(time(NULL));
    
        (*p_ar_indexes)[0].idx = (int)size_of_sample/2;
        (*p_ar_cells)[0].idx = (int)size_of_sample/2;
        sprintf(buf_int,"%d",(*p_ar_cells)[0].idx);
        strcpy((*p_ar_cells)[0].value, buf_int);
        hashtable_put(&hash_keys, &((*p_ar_indexes)[0]), sizeof(int), &((*p_ar_cells)[0]));
        for(int i=1;i<size_of_sample;i++) {
            i_search = 0 ;
            search_index.idx = rand() % size_of_sample ;
            cell_found = hashtable_get(&hash_keys, &search_index, sizeof(s_h_int));
            while ( cell_found != NULL && i_search < 10 ) {
                i_search++;
                search_index.idx = rand() % size_of_sample ;
                cell_found = hashtable_get(&hash_keys, &search_index, sizeof(s_h_int));
            }

            i_rand_value = rand() % size_of_sample ;
            while ( i_rand_value == (*p_ar_indexes)[0].idx ) {
                i_rand_value = rand() % size_of_sample ;
            }
            (*p_ar_key_remove)[i].idx =  i_rand_value ;
            (*p_ar_indexes)[i].idx = search_index.idx ;
            (*p_ar_cells)[i].idx = search_index.idx ;
            sprintf(buf_int,"%d",search_index.idx);
            strcpy((*p_ar_cells)[i].value, buf_int);
            hashtable_put(&hash_keys, &((*p_ar_indexes)[i]), sizeof(int), &((*p_ar_cells)[i]));
        }

        printf("ar_indexes\n");
        for(int i=0; i<size_of_sample; i++) {
            printf("%d ",(*p_ar_indexes)[i].idx);
        }
        printf("\n");

        printf("ar_remove\n");
        for(int i=0; i<size_of_sample; i++) {
            printf("%d ",(*p_ar_key_remove)[i].idx);
        }
        printf("\n");

        h_values = fopen("ar_values.bin","wb") ;
        h_remove = fopen("ar_remove.bin","wb") ;
        fwrite((*p_ar_indexes), sizeof(s_h_int), size_of_sample, h_values);
        fwrite((*p_ar_key_remove), sizeof(s_h_int), size_of_sample, h_remove);
        fclose(h_values);
        fclose(h_remove);
    }

    hashtable_free(&hash_keys);

}

void    test_btree_rebuild(void) {
    ps_h_int        ar_indexes ;
    ps_data_cell    ar_cells ;
    ps_h_int        ar_key_remove ;
    int             size_of_sample = 100 ;
    s_btree         tree_int_cell ;
    s_btree         tree_abre;

    prepare_load_datas(size_of_sample, &ar_indexes, &ar_cells, &ar_key_remove);

    btree_init(&tree_int_cell, btree_key_struct_int_compare);
    for(int i=0;i<size_of_sample;i++) {
        btree_put(&tree_int_cell, &(ar_indexes[i]), &(ar_cells[i]));
    }

    btree_to_dot(&tree_int_cell, "tree_rebuild_before.dot", key_to_string, value_to_string);
    btree_init(&tree_abre, btree_key_struct_int_compare);
    btree_rebuild(&tree_int_cell, &tree_abre);
    btree_free(&tree_int_cell);
    btree_to_dot(&tree_abre, "tree_rebuild_after.dot", key_to_string, value_to_string);
    
    free(ar_key_remove);
    free(ar_cells);
    free(ar_indexes);
    btree_free(&tree_abre);
}

void    test_btree_int_cell_remove_big(void) {    
    ps_h_int        ar_indexes ;
    ps_data_cell    ar_cells ;
    ps_h_int        ar_key_remove ;
    int             size_of_sample = 100 ;

    char            buf_name[128];
    int             index_name = 0 ;
    s_btree         tree_int_cell ;
    s_list          list_remove_key ;

    ps_list_data    p_current_list_data = NULL ;

    s_list          list_of_kv_infixe ;
    
    prepare_load_datas(size_of_sample, &ar_indexes, &ar_cells, &ar_key_remove);

    btree_init(&tree_int_cell, btree_key_struct_int_compare);
    list_init(&list_remove_key, false, NULL);

    for(int i=0;i<size_of_sample;i++) {
        btree_put(&tree_int_cell, &(ar_indexes[i]), &(ar_cells[i]));
        list_add(&list_remove_key, &(ar_key_remove[i]));
    }

    printf("tree created, remove some keys\n");
    btree_to_dot(&tree_int_cell, "tree_int_cell_before.dot", key_to_string, value_to_string);
    p_current_list_data = list_get_first(&list_remove_key) ;
    while ( p_current_list_data != NULL ) {
        btree_remove_key(&tree_int_cell, (ps_h_int)p_current_list_data->pv_data);
        sprintf(buf_name, "tree_int_cell_after_%d_%d.dot",index_name++,((ps_h_int)p_current_list_data->pv_data)->idx);
        btree_to_dot(&tree_int_cell, buf_name, key_to_string, value_to_string);
        
        list_init(&list_of_kv_infixe,false,NULL);
        btree_foreach_infix_with_parameter(&tree_int_cell, callback_for_each_with_parameters_list, NULL, &list_of_kv_infixe);
        if ( verify_list_order(&list_of_kv_infixe) ) {
            printf("%d:Ok ",((ps_h_int)p_current_list_data->pv_data)->idx); fflush(stdout);
        } else {
            printf("%d:*** KO *** ",((ps_h_int)p_current_list_data->pv_data)->idx); fflush(stdout);
        }        
        list_free(&list_of_kv_infixe);
        
        p_current_list_data = list_get_next(&list_remove_key, p_current_list_data);
    }

    printf("\nparcours infixe\n");
    btree_foreach_infix(&tree_int_cell, callback_for_each);

    printf("parcours prefixe\n");
    btree_foreach_prefix(&tree_int_cell, callback_for_each);

    printf("parcours postfixe\n");
    btree_foreach_postfix(&tree_int_cell, callback_for_each);

    list_free(&list_remove_key);
    btree_free(&tree_int_cell);
    
    free(ar_key_remove);
    free(ar_cells);
    free(ar_indexes);
}

static bool
verify_list_order(ps_list p_list) {
    ps_list_data    p_current_list_data = NULL ;

    p_current_list_data = list_get_first(p_list) ;
    while ( p_current_list_data != NULL ) {
        if ( p_current_list_data->p_prev != NULL ) {
            if ( ((ps_h_int)(p_current_list_data->pv_data))->idx < ((ps_h_int)(p_current_list_data->p_prev->pv_data))->idx ) {
                return false ;
            }
        }
        p_current_list_data = list_get_next(p_list, p_current_list_data);
    }
    return true;
}

void    test_btree_int_cell_rebuild(void) {
    s_h_int        indexes[] = {
        { 50 },

        { 26 },
        { 84 },

        { 13 },
        { 45 },
        { 80 },
        { 97 },
        
        { 12 },
        { 23 },
        { 36 },
        { 48 },
        { 62 },
        { 92 },
        { 98 },
        
        { 20 },
        { 30 },
        { 37 },
        { 47 },
        { 49 },
        { 54 },
        { 77 },
        { 89 },
        { 95 },
        { 99 },

        { 18 },
        { 27 },
        { 35 },
        { 39 },
        { 46 },
        { 61 },
        { 69 },
        { 88 },
        { 91 },
        { 93 },
        { 96 },
        
        { 66 },
        { 71 },
        { 70 },
        { 75 }
    } ;
    
    s_data_cell    cells[] = {
        { 50, "50"},
        
        { 26, "26"},
        { 84, "84"},
        
        { 13, "13"},
        { 45, "45"},
        { 80, "80"},
        { 97, "97"},
        
        { 12, "12"},
        { 23, "23"},
        { 36, "36"},
        { 48, "48"},
        { 62, "62"},
        { 92, "92"},
        { 98, "98"},
        
        { 20, "20"},
        { 30, "30"},
        { 37, "37"},
        { 47, "47"},
        { 49, "49"},
        { 54, "54"},
        { 77, "77"},
        { 89, "89"},
        { 95, "95"},
        { 99, "99"},
        
        { 18, "18"},
        { 27, "27"},
        { 35, "35"},
        { 39, "39"},
        { 46, "46"},
        { 61, "61"},
        { 69, "69"},
        { 88, "88"},
        { 91, "91"},
        { 93, "93"},
        { 96, "96"},
        
        { 66, "66"},
        { 71, "71"},
        { 70, "70"},
        { 75, "75"}
    } ;

    s_btree      tree_int_cell ;
    s_vector     v_of_kv ;
    s_btree      tree_abre;

    int nb_elems = sizeof(indexes) / sizeof(s_h_int) ;

    btree_init(&tree_int_cell, btree_key_struct_int_compare);
    vector_init(&v_of_kv, nb_elems);
    btree_init(&tree_abre, btree_key_struct_int_compare);
    
    for(int i=0;i<nb_elems;i++) {
        btree_put(&tree_int_cell, &(indexes[i]), &(cells[i]));
    }

    btree_to_dot(&tree_int_cell, "tree_rebuild.dot", key_to_string, value_to_string);
    btree_rebuild(&tree_int_cell, &tree_abre);
    btree_to_dot(&tree_abre, "tree_rebuild_equilibre.dot", key_to_string, value_to_string);

    btree_free(&tree_abre);
    vector_free(&v_of_kv);
    btree_free(&tree_int_cell);
}
