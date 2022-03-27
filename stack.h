/**
 * \file stack.h
 * \brief handling a LIFO Stack
 * \author Patrice Trognon
 * \version 1.0
 * \date 30 mars 2022
 */

#ifndef __STACK_H__
#define __STACK_H__

#include "b_types.h"
#include "vector.h"

/**
 * \brief forward declaration
 */
typedef struct list *ps_list ;

/**
 * \fn (*p_func_stack_for_each_callback)(unsigned int index, const void* pv_data)
 * \brief callback used for each stack element
 * this callback is used by statck_for_each
 *
 * \param index index in stack
 * \param pv_data pointer to data element
 */
typedef void   (*p_func_stack_for_each_callback)(unsigned int, const void*);

/**
 * \fn (*p_func_stack_for_each_with_param_callback)(unsigned int index, const void* pv_data, const void* pv_param1, const void* pv_param2)
 * \brief callback used for each stack element, the two pointers passed as parameters are passed back to the callback
 * this callback is used by stack_for_each_with_parameters
 *
 * \param index index in stack
 * \param pv_data pointer to data element
 * \param pv_param1 pointer to first parameter
 * \param pv_param2 pointer to second parameter
 */
typedef void   (*p_func_stack_for_each_with_param_callback)(unsigned int, const void*, const void*, const void*);

/**
 * \struct LIFO stack
 * \brief stack structure, a stack is a vector with push and pop
 */
struct stack_lifo {
    s_vector    stack;            /*!< a stack is a vector with push and pop */
} ;

/**
 * \typedef s_stack_lifo
 * \brief s_stack_lifo
 */
typedef struct stack_lifo s_stack_lifo ;

/**
 * \typedef ps_stack_lifo
 * \brief pointer to one s_stack_lifo
 */
typedef struct stack_lifo *ps_stack_lifo ;

void    stack_init(ps_stack_lifo p_stack, unsigned int initial_capacity) ;
void    stack_free(ps_stack_lifo p_stack);

void    stack_to_list(ps_stack_lifo p_stack, ps_list p_list);
void    stack_to_vector(ps_stack_lifo p_stack, ps_vector p_vector);

void    stack_lifo_push(ps_stack_lifo p_stack, void* pv_data);
void*   stack_lifo_pop(ps_stack_lifo p_stack);

void    stack_lifo_swap(ps_stack_lifo p_stack) ;
void    stack_lifo_dup(ps_stack_lifo p_stack) ;
void    stack_lifo_dup_n(ps_stack_lifo p_stack, int n) ;
void    stack_lifo_drop_n(ps_stack_lifo p_stack, int n) ;

void    stack_for_each(ps_stack_lifo p_stack, p_func_stack_for_each_callback pf_func);
void    stack_for_each_with_parameters(ps_stack_lifo p_stack, p_func_stack_for_each_with_param_callback pf_func, const void* pv_param1, const void* pv_param2);

#endif /* __STACK_H__ */
