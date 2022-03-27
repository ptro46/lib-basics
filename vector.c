/**
 * \file vector.c
 * \brief handling a vector, array of elements
 * \author Patrice Trognon
 * \version 1.0
 * \date 30 mars 2022
 */

#include <stdlib.h>
#include "vector.h"
#include "list.h"


/**
 * \fn vector_init(ps_vector p_vector, unsigned int initial_capacity)
 * \brief init one vector
 *
 * \param p_vector pointer to the struct s_vector
 * \param initial_capacity vector capacity
 */
void
vector_init(ps_vector p_vector, unsigned int initial_capacity) {
    if ( p_vector != NULL ) {
        p_vector->capacity = initial_capacity ;
        p_vector->nb_elements = 0 ;
        p_vector->array_of_pv_data = calloc(initial_capacity, sizeof(void*));
    }
}

/**
 * \fn vector_free(ps_vector p_vector)
 * \brief free a vector, don't free data
 *
 * \param p_vector pointer to the struct s_vector to free
 */
void
vector_free(ps_vector p_vector) {
    if ( p_vector != NULL &&
         p_vector->array_of_pv_data != NULL ) {
        free(p_vector->array_of_pv_data);
        p_vector->array_of_pv_data = NULL ;
        p_vector->nb_elements = 0 ;        
    }
}

/**
 * \fn vector_copy(ps_vector p_vector, ps_vector p_vector_to)
 * \brief clone vector to new vector with data copy
 *
 * \param p_vector pointer to the struct s_vector to copy from
 * \param p_vector_to pointer to the struct s_vector to copy to
 */
void
vector_copy(ps_vector p_vector, ps_vector p_vector_to) {
    vector_init(p_vector_to, p_vector->capacity);
    for(unsigned int i=0; i<p_vector->nb_elements; i++) {
        vector_add_element(p_vector_to, p_vector->array_of_pv_data[i]);
    }
}

/**
 * \fn vector_to_list(ps_vector p_vector, ps_list p_list)
 * \brief convert vector to list
 *
 * \param p_vector pointer to the struct s_vector to copy from
 * \param p_list pointer to the struct s_list to copy to
 */
void
vector_to_list(ps_vector p_vector, ps_list p_list) {
    list_init(p_list, false, NULL);
    for(unsigned int i=0; i<p_vector->nb_elements; i++) {
        list_add(p_list, p_vector->array_of_pv_data[i]);
    }
}

/**
 * \fn vector_add_element(ps_vector p_vector, void* pv_data)
 * \brief add one element, if mandatory expand vector capacity
 *
 * \param p_vector pointer to the struct s_vector
 * \param pv_data pointer to the data to add
 */
void
vector_add_element(ps_vector p_vector, void* pv_data) {
    if ( p_vector != NULL ) {
        if ( p_vector->nb_elements == p_vector->capacity ) {
            p_vector->capacity = p_vector->capacity + p_vector->capacity/2 ;
            p_vector->array_of_pv_data = realloc(p_vector->array_of_pv_data, p_vector->capacity * sizeof(void*));
        }
        p_vector->array_of_pv_data[p_vector->nb_elements] = pv_data ;
        p_vector->nb_elements++;
        
    }
}

/**
 * \fn vector_set_element_at(ps_vector p_vector, void* pv_data, unsigned int at)
 * \brief set element at index
 *
 * \param p_vector pointer to the struct s_vector
 * \param pv_data pointer to the data to set
 * \param at index to set
 */
void
vector_set_element_at(ps_vector p_vector, void* pv_data, unsigned int at) {
    if ( p_vector != NULL &&
         p_vector->array_of_pv_data != NULL &&
         at < p_vector->nb_elements ) {
        p_vector->array_of_pv_data[at] = pv_data;
    }
}

/**
 * \fn vector_insert_element_at(ps_vector p_vector, void* pv_data, unsigned int at)
 * \brief insert element at index, if mandatory expand vector capacity
 *
 * \param p_vector pointer to the struct s_vector
 * \param pv_data pointer to the data to add
 * \param at index to set
 */
void
vector_insert_element_at(ps_vector p_vector, void* pv_data, unsigned int at) {
    if ( p_vector != NULL &&
         p_vector->array_of_pv_data != NULL &&
         at < p_vector->nb_elements ) {
        if ( at == p_vector->nb_elements ) {
            // add at last position
            vector_add_element(p_vector, pv_data);
            return ;
        }
        // realloc if mandatory
        if ( p_vector->nb_elements+1 == p_vector->capacity ) {
            p_vector->capacity = p_vector->capacity + p_vector->capacity/2 ;
            p_vector->array_of_pv_data = realloc(p_vector->array_of_pv_data, p_vector->capacity * sizeof(void*));
        }

        // shift elements
        unsigned int i = p_vector->nb_elements ;
        while ( i >= at ) {
            p_vector->array_of_pv_data[i+1]=p_vector->array_of_pv_data[i];
            i--;
        }
        p_vector->nb_elements++;
        p_vector->array_of_pv_data[at] = pv_data ;
    }
}

/**
 * \fn vector_remove_element_at(ps_vector p_vector, unsigned int at)
 * \brief remove element at index
 *
 * \param p_vector pointer to the struct s_vector
 * \param at index to set
 */
void
vector_remove_element_at(ps_vector p_vector, unsigned int at) {
    if ( p_vector != NULL &&
         p_vector->array_of_pv_data != NULL &&
         at < p_vector->nb_elements ) {
        if ( at == p_vector->nb_elements ) {
            p_vector->array_of_pv_data[at] = NULL ;
        } else {            
            // shift elements
            for(unsigned int i=at; i<p_vector->nb_elements; i++) {
                p_vector->array_of_pv_data[i] = p_vector->array_of_pv_data[i+1];
            }
        }
        p_vector->nb_elements--;
    }
}

/**
 * \fn vector_remove_element(ps_vector p_vector, void* pv_data, p_func_vector_compare pf_func)
 * \brief remove element, find it by compare callback
 *
 * \param p_vector pointer to the struct s_vector
 * \param pv_data pointer to the data to add
 * \param pf_func callback to compare two elements
 */
void
vector_remove_element(ps_vector p_vector, void* pv_data, p_func_vector_compare pf_func) {
    if ( p_vector != NULL &&
         p_vector->array_of_pv_data != NULL ) {
        int at = vector_index_of(p_vector, pv_data, pf_func) ;
        if ( at >= 0 ) {
            vector_remove_element_at(p_vector, at) ;
        }
    }
}

/**
 * \fn vector_element_at(ps_vector p_vector, unsigned int at)
 * \brief get element at index
 *
 * \param p_vector pointer to the struct s_vector
 * \param at index to set
 * \return pointer to element
 */
void*
vector_element_at(ps_vector p_vector, unsigned int at) {
    if ( p_vector != NULL &&
         p_vector->array_of_pv_data != NULL &&
         at < p_vector->nb_elements ) {
        return p_vector->array_of_pv_data[at];
    }
    return NULL;
}

/**
 * \fn vector_index_of(ps_vector p_vector, void* pv_data, p_func_vector_compare pf_func)
 * \brief get element index, find it by compare callback
 *
 * \param p_vector pointer to the struct s_vector
 * \param pv_data pointer to the data to add
 * \param pf_func callback to compare two elements
 * \return index of found element, or -1 if not found
 */
long
vector_index_of(ps_vector p_vector, void* pv_data, p_func_vector_compare pf_func) {
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
 * \fn vector_for_each(ps_vector p_vector, p_func_vector_for_each_callback pf_func)
 * \brief for each element call pf_func, loop on the nb_elements
 *
 * \param p_vector pointer to the struct s_vector
 * \param pf_func callback used for each element
 */
void
vector_for_each(ps_vector p_vector, p_func_vector_for_each_callback pf_func) {
    if ( p_vector != NULL &&
         p_vector->array_of_pv_data != NULL ) {
        for(unsigned int i=0; i<p_vector->nb_elements; i++) {
            pf_func(i, p_vector->array_of_pv_data[i] ) ;
        }
    }
}

/**
 * \fn vector_for_each_capacity(ps_vector p_vector, p_func_vector_for_each_callback pf_func)
 * \brief for each element call pf_func, loop on the capacity, callback is used is element is not null (used by hashtable)
 *
 * \param p_vector pointer to the struct s_vector
 * \param pf_func callback used for each element
 */
void
vector_for_each_capacity(ps_vector p_vector, p_func_vector_for_each_callback pf_func) {
    if ( p_vector != NULL &&
         p_vector->array_of_pv_data != NULL ) {
        for(unsigned int i=0; i<p_vector->capacity; i++) {
            pf_func(i, p_vector->array_of_pv_data[i] ) ;
        }
    }
}

/**
 * \fn vector_for_each_with_parameters(ps_vector p_vector, p_func_vector_for_each_with_param_callback pf_func, const void* pv_param1, const void* pv_param2)
 * \brief for each element call pf_func, loop on the nb_elements, the two parameters are passed to the callback
 *
 * \param p_vector pointer to the struct s_vector
 * \param pf_func callback used for each element
 * \param pv_param1 first parameter pass to callback 
 * \param pv_param2 second parameter pass to callback 
 */
void
vector_for_each_with_parameters(ps_vector p_vector, p_func_vector_for_each_with_param_callback pf_func, const void* pv_param1, const void* pv_param2) {
    if ( p_vector != NULL &&
         p_vector->array_of_pv_data != NULL ) {
        for(unsigned int i=0; i<p_vector->nb_elements; i++) {
            pf_func(i, p_vector->array_of_pv_data[i], pv_param1, pv_param2 ) ;
        }
    }
}

/**
 * \fn vector_for_each_capacity_with_parameters(ps_vector p_vector, p_func_vector_for_each_with_param_callback pf_func, const void* pv_param1, const void* pv_param2)
 * \brief for each element call pf_func, loop on the capacity, callback is used is element is not null (used by hashtable), the two parameters are passed to the callback
 *
 * \param p_vector pointer to the struct s_vector
 * \param pf_func callback used for each element
 * \param pv_param1 first parameter pass to callback 
 * \param pv_param2 second parameter pass to callback 
 */
void
vector_for_each_capacity_with_parameters(ps_vector p_vector, p_func_vector_for_each_with_param_callback pf_func, const void* pv_param1, const void* pv_param2) {
    if ( p_vector != NULL &&
         p_vector->array_of_pv_data != NULL ) {
        for(unsigned int i=0; i<p_vector->capacity; i++) {
            pf_func(i, p_vector->array_of_pv_data[i], pv_param1, pv_param2 ) ;
        }
    }
}
