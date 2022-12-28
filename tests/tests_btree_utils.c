#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "tests.h"
#include "btree.h"
#include "list.h"
#include "vector.h"
#include "hashtable.h"

int    btree_key_struct_int_compare(const void* pv_data1, const void* pv_data2) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    ps_h_int p_key_int_1 = (ps_h_int)pv_data1 ;
    ps_h_int p_key_int_2 = (ps_h_int)pv_data2;
#pragma GCC diagnostic pop

    return p_key_int_1->idx - p_key_int_2->idx ;
}

int
btree_key_string_compare(const void* pv_data1, const void* pv_data2) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    ps_buffer p_key_buf_1 = (ps_buffer)pv_data1 ;
    ps_buffer p_key_buf_2 = (ps_buffer)pv_data2;
#pragma GCC diagnostic pop
    if ( p_key_buf_1->offset == p_key_buf_2->offset ) {
        return memcmp(p_key_buf_1->data, p_key_buf_2->data, p_key_buf_1->offset);
    }
    if ( p_key_buf_1->offset < p_key_buf_2->offset ) {
        return memcmp(p_key_buf_1->data, p_key_buf_2->data, p_key_buf_1->offset);
    }
    return memcmp(p_key_buf_1->data, p_key_buf_2->data, p_key_buf_2->offset);
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

void
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

bool
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
