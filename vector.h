/**
 * \file vector.h
 * \brief handling a vector, a vector is a array of 
 * \author Patrice Trognon
 * \version 1.0
 * \date 30 mars 2022
 */
#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "b_types.h"

/**
 * \brief forward declaration
 */
typedef struct list *ps_list ;

/**
 * \fn (*p_func_vector_for_each_callback)(unsigned int index, const void* pv_data)
 * \brief callback used for each vector element
 * this callback is used by vector_for_each and vector_for_each_capacity
 *
 * \param index index in vector
 * \param pv_data pointer to data element
 */
typedef void   (*p_func_vector_for_each_callback)(unsigned int, const void*);

/**
 * \fn (*p_func_vector_for_each_with_param_callback)(unsigned int index, const void* pv_data, const void* pv_param1, const void* pv_param2)
 * \brief callback used for each vector element, the two pointers passed as parameters are passed back to the callback
 * this callback is used by vector_for_each_with_parameters and vector_for_each_capacity_with_parameters
 *
 * \param index index in vector
 * \param pv_data pointer to data element
 * \param pv_param1 pointer to first parameter
 * \param pv_param2 pointer to second parameter
 */
typedef void   (*p_func_vector_for_each_with_param_callback)(unsigned int, const void*, const void*, const void*);

/**
 * \fn (*p_func_vector_compare)(const void* pv_data1, const void* pv_data2)
 * \brief callback used to compare two elements
 * this callback is used by vector_remove_element ans vector_index_of
 *
 * \param pv_data1 pointer to first element
 * \param pv_data2 pointer to second element
 * \return 0 if equal
 */
typedef int    (*p_func_vector_compare)(const void*, const void*);

/**
 * \struct vector
 * \brief vector structure
 */
struct vector {
    unsigned int    capacity;            /*!< vector capacity */
    void**          array_of_pv_data;    /*!< vector array of data */
    unsigned int    nb_elements;         /*!< vector number of elements */
} ;

/**
 * \typedef s_vector
 * \brief vector
 */
typedef struct vector s_vector ;

/**
 * \typedef ps_vector
 * \brief pointer to one s_vector
 */
typedef struct vector *ps_vector ;

void            vector_init(ps_vector p_vector, unsigned int initial_capacity);
void            vector_free(ps_vector p_vector);

void            vector_copy(ps_vector p_vector, ps_vector p_vector_to);
void            vector_to_list(ps_vector p_vector, ps_list p_list);

void            vector_add_element(ps_vector p_vector, void* pv_data);
void            vector_set_element_at(ps_vector p_vector, void* pv_data, unsigned int at);
void            vector_insert_element_at(ps_vector p_vector, void* pv_data, unsigned int at);

void            vector_remove_element_at(ps_vector p_vector, unsigned int at);
void            vector_remove_element(ps_vector p_vector, void* pv_data, p_func_vector_compare pf_func);

void*           vector_element_at(ps_vector p_vector, unsigned int at);
long            vector_index_of(ps_vector p_vector, void* pv_data, p_func_vector_compare pf_func);

void            vector_for_each(ps_vector p_vector, p_func_vector_for_each_callback pf_func);
void            vector_for_each_capacity(ps_vector p_vector, p_func_vector_for_each_callback pf_func);

void            vector_for_each_with_parameters(ps_vector p_vector, p_func_vector_for_each_with_param_callback pf_func, const void* pv_param1, const void* pv_param2);
void            vector_for_each_capacity_with_parameters(ps_vector p_vector, p_func_vector_for_each_with_param_callback pf_func, const void* pv_param1, const void* pv_param2);

#endif /* __VECTOR_H__ */
