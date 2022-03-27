/**
 * \file hashtable.c
 * \brief handling of a hashtable structure
 * \author Patrice Trognon
 * \version 1.0
 * \date 30 mars 2022
 */
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "hashtable.h"

unsigned int    default_hash_func(void* pv_data, size_t size);
void            hashtable_debug_dump_vector_kv(unsigned int index, const void* p_kv) ;
void            hashtable_debug_dump_vector_entries(unsigned int index, const void* pv_vector_of_values) ;

void            hashtable_free_vector_kv(unsigned int index, const void* p_kv) ;
void            hashtable_free_vector_entries(unsigned int index, const void* pv_vector_of_values) ;


/**
 * \fn default_hash_func(void* pv_data, size_t size)
 * \brief calculate key hash as sum of array of bytes, this is default hash function can by override
 *
 * \param pv_data pointer to key
 * \param size sizeof(key)
 * \return hash value is sum of array of key bytes
 */
unsigned int
default_hash_func(void* pv_data, size_t size) {
    unsigned int sigma = 0;
    unsigned char* puc_data = (unsigned char*)pv_data ;
    for(unsigned int i=0; i<size; i++) {
        sigma += puc_data[i];
    }
    return sigma;
}

/**
 * \fn hashtable_init(ps_hashtable p_hashtable, unsigned int initial_capacity, p_func_compare_key pf_comp)
 * \brief init a hashtable with default_hash_func and default load_factor (0.75f)
 *
 * \param p_hashtable hashtable pointer
 * \param initial_capacity initial hashtable vector capacity
 * \param pf_comp callback to compare two keys
 */
void
hashtable_init(ps_hashtable p_hashtable, unsigned int initial_capacity, p_func_compare_key pf_comp) {
    hashtable_init_hash_func_load_factor(p_hashtable, initial_capacity, default_hash_func, 0.75f, pf_comp);
}

/**
 * \fn hashtable_init_hash_func(ps_hashtable p_hashtable, unsigned int initial_capacity, p_func_hash pf_hash, p_func_compare_key pf_comp)
 * \brief init a hashtable with custom hash_func and default load_factor (0.75f)
 *
 * \param p_hashtable hashtable pointer
 * \param initial_capacity initial hashtable vector capacity
 * \param pf_hash callback to perform key hash value
 * \param pf_comp callback to compare two keys
 */
void
hashtable_init_hash_func(ps_hashtable p_hashtable, unsigned int initial_capacity, p_func_hash pf_hash, p_func_compare_key pf_comp) {
    hashtable_init_hash_func_load_factor(p_hashtable, initial_capacity, pf_hash, 0.75f,pf_comp);
}

/**
 * \brief compare two int 
 */
#define min(a,b) (a<=b?a:b)

/**
 * \fn hashtable_init_hash_func_load_factor(ps_hashtable p_hashtable, unsigned int initial_capacity, p_func_hash pf_hash, float load_factor, p_func_compare_key pf_comp)
 * \brief init a hashtable with custom hash_func and custom load_factor
 *
 * \param p_hashtable hashtable pointer
 * \param initial_capacity initial hashtable vector capacity
 * \param pf_hash callback to perform key hash value
 * \param load_factor custom load factor
 * \param pf_comp callback to compare two keys
 */
void
hashtable_init_hash_func_load_factor(ps_hashtable p_hashtable, unsigned int initial_capacity, p_func_hash pf_hash, float load_factor, p_func_compare_key pf_comp) {
    vector_init(&(p_hashtable->v_entries),initial_capacity);
    p_hashtable->pf_hash = pf_hash ;
    p_hashtable->pf_comp = pf_comp ;
    p_hashtable->load_factor = load_factor ;
    p_hashtable->threshold = min(initial_capacity*load_factor, UINT_MAX - 8+1) ;
    p_hashtable->nb_elements = 0;
}

/**
 * \fn hashtable_free_vector_kv(unsigned int index, const void* p_kv)
 * \brief free a pointer to hash_entry, callback used by hashtable_free_vector_entries
 *
 * \param index index of (not used)
 * \param p_kv pointer to hash_entry to be free
 */
void
hashtable_free_vector_kv(unsigned int index, const void* p_kv) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    free((void*)p_kv);
#pragma GCC diagnostic pop
}

/**
 * \fn hashtable_free_vector_entries(unsigned int index, const void* pv_vector_of_values)
 * \brief free all vector elements if allocated , callback used by hashtable_free
 *
 * \param index index of (not used)
 * \param pv_vector_of_values hashtable contains hashtable entries
 */
void
hashtable_free_vector_entries(unsigned int index, const void* pv_vector_of_values) {
    if ( pv_vector_of_values != NULL ) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
        const ps_vector p_array_of_values = (const ps_vector)pv_vector_of_values;
#pragma GCC diagnostic pop
        vector_for_each(p_array_of_values, hashtable_free_vector_kv);
        vector_free(p_array_of_values);
        free(p_array_of_values);
    }
}

/**
 * \fn hashtable_free(ps_hashtable p_hashtable)
 * \brief free hashtable
 *
 * \param p_hashtable pointer to hashtable
 */
void
hashtable_free(ps_hashtable p_hashtable) {
    vector_for_each_capacity(&(p_hashtable->v_entries),hashtable_free_vector_entries);
    vector_free(&(p_hashtable->v_entries));
}

/**
 * \fn hashtable_rehash(ps_hashtable p_hashtable, unsigned int new_capacity)
 * \brief rehash hashtable with new capacity
 *
 * \param p_hashtable pointer to hashtable
 * \param new_capacity the new capacity
 */
void
hashtable_rehash(ps_hashtable p_hashtable, unsigned int new_capacity) {
    s_hashtable new_hashtable ;

    hashtable_init_hash_func_load_factor(&new_hashtable,
                                         new_capacity,
                                         p_hashtable->pf_hash,
                                         p_hashtable->load_factor,
                                         p_hashtable->pf_comp) ;

    for(unsigned int i=0;i<p_hashtable->v_entries.capacity; i++) {
        ps_vector p_array_of_values = (ps_vector)hashtable_vector_element_at(&(p_hashtable->v_entries), i) ;
        if ( p_array_of_values != NULL ) {
            for(unsigned int j=0; j<p_array_of_values->nb_elements; j++) {
                ps_hash_entry p_hash_entry = vector_element_at(p_array_of_values, j);
                hashtable_put(&new_hashtable, p_hash_entry->pv_key, p_hash_entry->key_size, p_hash_entry->pv_value);
            }
        }
    }

    hashtable_free( p_hashtable ) ;
    p_hashtable->threshold = new_hashtable.threshold ;
    p_hashtable->load_factor = new_hashtable.load_factor ;
    p_hashtable->pf_hash = new_hashtable.pf_hash ;
    p_hashtable->pf_comp = new_hashtable.pf_comp ;
    p_hashtable->nb_elements = new_hashtable.nb_elements ;
    
    p_hashtable->v_entries.capacity = new_hashtable.v_entries.capacity ;
    p_hashtable->v_entries.nb_elements = new_hashtable.v_entries.nb_elements ;
    p_hashtable->v_entries.array_of_pv_data = new_hashtable.v_entries.array_of_pv_data ;
}

/**
 * \fn hashtable_put(ps_hashtable p_hashtable, void* pv_key, size_t key_size, void* pv_value)
 * \brief put one element pv_value associated with the key pv_key, rehash if nb_elements is great than threshold 
 *
 * \param p_hashtable pointer to hashtable
 * \param pv_key key
 * \param key_size sizeof(key)
 * \param pv_value value
 */
void
hashtable_put(ps_hashtable p_hashtable, void* pv_key, size_t key_size, void* pv_value) {
    if ( p_hashtable->pf_comp != NULL ) {
        unsigned int ui_hash = p_hashtable->pf_hash(pv_key, key_size) ;
        unsigned int ui_hash_index = ui_hash % p_hashtable->v_entries.capacity ;
        void* pv_vector_values = hashtable_vector_element_at(&(p_hashtable->v_entries), ui_hash_index) ;
        ps_vector p_array_of_values = NULL;
    
        if ( pv_vector_values == NULL ) {
            p_array_of_values = calloc(sizeof(s_vector), 1);
            vector_init(p_array_of_values, 10);
            ps_hash_entry p_hash_entry = calloc(sizeof(s_hash_entry),1);
            p_hash_entry->pv_key = pv_key ;
            p_hash_entry->key_size = key_size ;
            p_hash_entry->pv_value = pv_value ;        
            vector_add_element(p_array_of_values, p_hash_entry);
            hashtable_vector_set_element_at(&(p_hashtable->v_entries), p_array_of_values, ui_hash_index);
            p_hashtable->nb_elements++;
        } else {
            p_array_of_values = (ps_vector)pv_vector_values;
            ps_hash_entry p_hash_entry = calloc(sizeof(s_hash_entry),1);
            p_hash_entry->pv_key = pv_key ;
            p_hash_entry->key_size = key_size ;
            p_hash_entry->pv_value = pv_value ;
            long index_of_existing_element = hashtable_vector_index_of(p_array_of_values, p_hash_entry, p_hashtable->pf_comp);
            if ( index_of_existing_element >= 0 ) {
                ps_hash_entry old_hash_entry = vector_element_at(p_array_of_values, index_of_existing_element);
                if ( old_hash_entry != NULL ) {
                    free(old_hash_entry);
                }
                vector_set_element_at(p_array_of_values, p_hash_entry, index_of_existing_element);
            } else {
                vector_add_element(p_array_of_values, p_hash_entry);
                p_hashtable->nb_elements++;
            }
        }

        if ( p_hashtable->nb_elements >= p_hashtable->threshold ) {
            unsigned int new_capacity = ((p_hashtable->v_entries.capacity) << 1) + 1 ;
            printf("rehash is needed nb_elements(%u) threshold(%u) old_capacity(%u) new_capacity(%u)\n",
                   p_hashtable->nb_elements,
                   p_hashtable->threshold,
                   p_hashtable->v_entries.capacity,
                   new_capacity);
            hashtable_rehash(p_hashtable, new_capacity);
        }
    }
}

/**
 * \fn hashtable_get(ps_hashtable p_hashtable, void* pv_key, size_t key_size)
 * \brief returns the data associated with the key
 *
 * \param p_hashtable pointer to hashtable
 * \param pv_key key
 * \param key_size sizeof(key) used by hash function
 * \return value associated with the key, NULL if not found
 */
void*
hashtable_get(ps_hashtable p_hashtable, void* pv_key, size_t key_size) {
    if ( p_hashtable->pf_comp != NULL ) {
        unsigned int ui_hash = p_hashtable->pf_hash(pv_key, key_size) ;
        unsigned int ui_hash_index = ui_hash % p_hashtable->v_entries.capacity ;
        ps_vector p_array_of_values = (ps_vector)hashtable_vector_element_at(&(p_hashtable->v_entries), ui_hash_index) ;
        if ( p_array_of_values != NULL ) {
            s_hash_entry hash_entry ;
            hash_entry.pv_key = pv_key ;
            hash_entry.key_size = key_size ;
            hash_entry.pv_value = NULL ;
            long index_of_existing_element = hashtable_vector_index_of(p_array_of_values, &hash_entry, p_hashtable->pf_comp);
            if ( index_of_existing_element >= 0 ) {
                ps_hash_entry p_hash_entry = vector_element_at(p_array_of_values, index_of_existing_element);
                return p_hash_entry->pv_value ;
            }            
        }
    }
    return NULL ;
}

/**
 * \fn hashtable_keys(ps_hashtable p_hashtable, ps_vector p_vector_keys)
 * \brief returns a vector of all keys
 *
 * \param p_hashtable pointer to hashtable
 * \param p_vector_keys vector that receive keys
 */
void
hashtable_keys(ps_hashtable p_hashtable, ps_vector p_vector_keys) {
    vector_init(p_vector_keys, p_hashtable->nb_elements);
    for(unsigned int i=0;i<p_hashtable->v_entries.capacity; i++) {
        ps_vector p_array_of_values = (ps_vector)hashtable_vector_element_at(&(p_hashtable->v_entries), i) ;
        if ( p_array_of_values != NULL ) {
            for(unsigned int j=0; j<p_array_of_values->nb_elements; j++) {
                ps_hash_entry p_hash_entry = vector_element_at(p_array_of_values, j);
                vector_add_element(p_vector_keys, p_hash_entry->pv_key) ;
            }
        }
    }
}

/**
 * \fn hashtable_values(ps_hashtable p_hashtable, ps_vector p_vector_values)
 * \brief returns a vector of all values
 *
 * \param p_hashtable pointer to hashtable
 * \param p_vector_values vector that receive values
 */
void
hashtable_values(ps_hashtable p_hashtable, ps_vector p_vector_values) {
    vector_init(p_vector_values, p_hashtable->nb_elements);
    for(unsigned int i=0;i<p_hashtable->v_entries.capacity; i++) {
        ps_vector p_array_of_values = (ps_vector)hashtable_vector_element_at(&(p_hashtable->v_entries), i) ;
        if ( p_array_of_values != NULL ) {
            for(unsigned int j=0; j<p_array_of_values->nb_elements; j++) {
                ps_hash_entry p_hash_entry = vector_element_at(p_array_of_values, j);
                vector_add_element(p_vector_values, p_hash_entry->pv_value) ;
            }
        }
    }
}

/**
 * \fn hashtable_remove_key(ps_hashtable p_hashtable, void* pv_key, size_t key_size)
 * \brief remove entry associated with key
 *
 * \param p_hashtable pointer to hashtable
 * \param pv_key key
 * \param key_size sizeof(key) used by hash function
 */
void
hashtable_remove_key(ps_hashtable p_hashtable, void* pv_key, size_t key_size) {
    if ( p_hashtable->pf_comp != NULL ) {
        unsigned int ui_hash = p_hashtable->pf_hash(pv_key, key_size) ;
        unsigned int ui_hash_index = ui_hash % p_hashtable->v_entries.capacity ;
        ps_vector p_array_of_values = (ps_vector)hashtable_vector_element_at(&(p_hashtable->v_entries), ui_hash_index) ;
        if ( p_array_of_values != NULL ) {
            if ( p_array_of_values->nb_elements > 1 ) {
                s_hash_entry hash_entry ;
                hash_entry.pv_key = pv_key ;
                hash_entry.key_size = key_size ;
                hash_entry.pv_value = NULL ;
                long index_of_existing_element = hashtable_vector_index_of(p_array_of_values, &hash_entry, p_hashtable->pf_comp);
                if ( index_of_existing_element >= 0 ) {
                    ps_hash_entry p_hash_entry = vector_element_at(p_array_of_values, index_of_existing_element);
                    free(p_hash_entry);
                    vector_remove_element_at(p_array_of_values, index_of_existing_element) ;
                    p_hashtable->nb_elements--;
                }
            } else {
                ps_hash_entry p_hash_entry = vector_element_at(p_array_of_values, 0);
                free(p_hash_entry);
                p_hashtable->nb_elements--;
                vector_free(p_array_of_values);
                free(p_array_of_values);
                hashtable_vector_set_element_at(&(p_hashtable->v_entries), NULL, ui_hash_index) ;
            }
        }
    }    
}

/**
 * \fn hashtable_vector_element_at(ps_vector p_vector, unsigned int at)
 * \brief override vector_element_at to not use nb_elements bounds
 *
 * \param p_vector pointer to vector
 * \param at position
 */
void*
hashtable_vector_element_at(ps_vector p_vector, unsigned int at) {
    if ( p_vector != NULL &&
         p_vector->array_of_pv_data != NULL ) {
        return p_vector->array_of_pv_data[at];
    }
    return NULL;
}

/**
 * \fn hashtable_vector_set_element_at(ps_vector p_vector, void* pv_data, unsigned int at)
 * \brief override vector_set_element_at to not use nb_elements bounds
 *
 * \param p_vector pointer to vector
 * \param pv_data data to set
 * \param at position
 */
void
hashtable_vector_set_element_at(ps_vector p_vector, void* pv_data, unsigned int at) {
    if ( p_vector != NULL &&
         p_vector->array_of_pv_data != NULL ) {
        p_vector->array_of_pv_data[at] = pv_data;
    }
}

/**
 * \fn hashtable_vector_index_of(ps_vector p_vector, void* pv_data, p_func_compare_key pf_func)
 * \brief override vector_index_of to not use nb_elements bounds
 *
 * \param p_vector pointer to vector
 * \param pv_data data to set
 * \param pf_func callback to compare two values
 */
long
hashtable_vector_index_of(ps_vector p_vector, void* pv_data, p_func_compare_key pf_func) {
    if ( p_vector != NULL &&
         p_vector->array_of_pv_data != NULL ) {
        long i=0 ;
        while ( i<p_vector->nb_elements &&
                0 == pf_func(p_vector->array_of_pv_data[i], pv_data) ) {
            i++;
        }
        if ( i < p_vector->nb_elements ) {
            return i;
        }
    }
    return -1;
}

/**
 * \fn hashtable_debug_dump_vector_kv(unsigned int index, const void* p_kv)
 * \brief debug function to print a kv with key(string) and value(string)
 *
 * \param index index not use
 * \param p_kv pointer to hash_entry
 */
void
hashtable_debug_dump_vector_kv(unsigned int index, const void* p_kv) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    const ps_hash_entry p_key_value = (const ps_hash_entry)p_kv;
#pragma GCC diagnostic pop
    printf("{%s:%ld,%s} ",(char*)p_key_value->pv_key, p_key_value->key_size, (char*)p_key_value->pv_value);
}

/**
 * \fn hashtable_debug_dump_vector_entries(unsigned int index, const void* pv_vector_of_values)
 * \brief debug function to print a kv with key(string) and value(string)
 *
 * \param index index not use
 * \param pv_vector_of_values values
 */
void
hashtable_debug_dump_vector_entries(unsigned int index, const void* pv_vector_of_values) {
    if ( pv_vector_of_values != NULL ) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
        const ps_vector p_array_of_values = (const ps_vector)pv_vector_of_values;
#pragma GCC diagnostic pop
        printf("\t%u:[%u]:",index,p_array_of_values->nb_elements);
        vector_for_each(p_array_of_values, hashtable_debug_dump_vector_kv);
        printf("\n");
    }
}

/**
 * \fn hashtable_debug(ps_hashtable p_hashtable)
 * \brief debug function to print a kv with key(string) and value(string)
 *
 * \param p_hashtable pointer to hashtable
 */
void
hashtable_debug(ps_hashtable p_hashtable) {
    printf("hashtable\n");
    printf("\tnb_elements : %u\n",p_hashtable->nb_elements);
    vector_for_each_capacity(&(p_hashtable->v_entries),hashtable_debug_dump_vector_entries);
}

