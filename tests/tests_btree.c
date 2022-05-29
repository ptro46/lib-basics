#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "tests.h"
#include "btree.h"
#include "list.h"
#include "vector.h"
#include "hashtable.h"

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
