/**
 * \file hashtable.h
 * \brief handling of a hashtable structure
 * \author Patrice Trognon
 * \version 1.0
 * \date 30 mars 2022
 */
#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include <sys/types.h>
#include <string.h>

#include "vector.h"

/**
 * \fn (*p_func_hash)(void* pv_data, size_t size)
 * \brief callback used to hash a key
 * this callback is used by hashtable_put, hashtable_get, rehash
 *
 * \param pv_data pointer to key
 * \param size sizeof(key)
 * \return hash value
 */
typedef unsigned int    (*p_func_hash)(void* pv_data, size_t size);

/**
 * \fn (*p_func_compare_key)(const void *pv_key1, const void* pv_key2)
 * \brief callback used to compare two keys
 *
 * \param pv_key1 pointer to first key
 * \param pv_key2 pointer to second key
 * \return true(1) if equal
 */
typedef bool            (*p_func_compare_key)(const void *pv_key1, const void* pv_key2);

/**
 * \struct hash_entry
 * \brief one hash entry, contains key, sizeof(key) and value
 */
struct hash_entry {
    void*    pv_key;    /*!< key pointer */
    size_t   key_size;  /*!< sizeof(key) */
    void*    pv_value;  /*!< value pointer */
} ;

/**
 * \typedef s_hash_entry
 * \brief one hash entry
 */
typedef struct hash_entry s_hash_entry ;

/**
 * \typedef ps_hash_entry
 * \brief pointer to one s_hash_entry
 */
typedef struct hash_entry *ps_hash_entry ;

/**
 * \struct hashtable
 * \brief default load_factor is 0.75, the threshold is the value of min(initial_capacity * load_factor, UINT_MAX - 8+1)
 */
struct hashtable {
    s_vector             v_entries;     /*!< contains a vector of hash_entry at hash index */
    unsigned int         threshold;     /*!< hashtable threshold */
    float                load_factor;   /*!< hashtable load_factor, used to estimate threshold */
    p_func_hash          pf_hash;       /*!< hash_function, default impl if not override */
    p_func_compare_key   pf_comp;       /*!< function to compare 2 keys */
    unsigned int         nb_elements;   /*!< hashtable elements count*/
} ;

/**
 * \typedef s_hashtable
 * \brief one hashtable
 */
typedef struct hashtable s_hashtable ;

/**
 * \typedef ps_hashtable
 * \brief pointer to one s_hashtable
 */
typedef struct hashtable *ps_hashtable ;

void    hashtable_init(ps_hashtable p_hashtable,
                       unsigned int initial_capacity,
                       p_func_compare_key pf_comp);
void    hashtable_init_hash_func(ps_hashtable p_hashtable,
                                 unsigned int initial_capacity,
                                 p_func_hash pf_hash,
                                 p_func_compare_key pf_comp);
void    hashtable_init_hash_func_load_factor(ps_hashtable p_hashtable,
                                             unsigned int initial_capacity,
                                             p_func_hash pf_hash,
                                             float load_factor,
                                             p_func_compare_key pf_comp);

void    hashtable_free(ps_hashtable p_hashtable);

void    hashtable_rehash(ps_hashtable p_hashtable, unsigned int new_capacity);
void    hashtable_put(ps_hashtable p_hashtable, void* pv_key, size_t key_size, void* pv_value);
void*   hashtable_get(ps_hashtable p_hashtable, void* pv_key, size_t key_size);
void    hashtable_keys(ps_hashtable p_hashtable, ps_vector p_vector_keys);
void    hashtable_values(ps_hashtable p_hashtable, ps_vector p_vector_values);
void    hashtable_remove_key(ps_hashtable p_hashtable, void* pv_key, size_t key_size);

void    hashtable_debug(ps_hashtable p_hashtable) ;


/***
 * 
 override some vector function to disable nb_elements bounds verification
 */
void*    hashtable_vector_element_at(ps_vector p_vector, unsigned int at) ;
void     hashtable_vector_set_element_at(ps_vector p_vector, void* pv_data, unsigned int at);
long     hashtable_vector_index_of(ps_vector p_vector, void* pv_data, p_func_compare_key pf_func);
#endif /* __HASHTABLE_H__ */
