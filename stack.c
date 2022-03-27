/**
 * \file stack.c
 * \brief handling a LIFO Stack
 * \author Patrice Trognon
 * \version 1.0
 * \date 30 mars 2022
 */
#include <stdlib.h>

#include "stack.h"
#include "list.h"
#include "vector.h"

/**
 * \fn stack_init(ps_stack_lifo p_stack, unsigned int initial_capacity)
 * \brief init one stack
 *
 * \param p_stack pointer to the struct s_stack
 * \param initial_capacity stack capacity
 */
void
stack_init(ps_stack_lifo p_stack, unsigned int initial_capacity) {
    vector_init(&(p_stack->stack), initial_capacity);
}

/**
 * \fn stack_free(ps_stack_lifo p_stack)
 * \brief free a stack, don't free data
 *
 * \param p_stack pointer to the struct s_stack to free
 */
void
stack_free(ps_stack_lifo p_stack) {
    vector_free(&(p_stack->stack));
}

/**
 * \fn stack_to_list(ps_stack_lifo p_stack, ps_list p_list)
 * \brief convert stack to list
 *
 * \param p_stack pointer to the struct s_stack to copy from
 * \param p_list pointer to the struct s_list to copy to
 */
void
stack_to_list(ps_stack_lifo p_stack, ps_list p_list) {
    vector_to_list(&(p_stack->stack), p_list);
}

/**
 * \fn stack_to_vector(ps_stack_lifo p_stack, ps_vector p_vector)
 * \brief convert stack to vector
 *
 * \param p_stack pointer to the struct s_stack to copy from
 * \param p_vector pointer to the struct s_vector to copy to
 */
void
stack_to_vector(ps_stack_lifo p_stack, ps_vector p_vector) {
    vector_copy(&(p_stack->stack), p_vector);
}


/**
 * \fn stack_lifo_push(ps_stack_lifo p_stack, void* pv_data)
 * \brief push one element to stack
 *
 * \param p_stack pointer to the struct s_stack to copy from
 * \param pv_data element to push
 */
void
stack_lifo_push(ps_stack_lifo p_stack, void* pv_data) {
    vector_add_element(&(p_stack->stack), pv_data);
}

/**
 * \fn stack_lifo_pop(ps_stack_lifo p_stack)
 * \brief pop one element from stack
 *
 * \param p_stack pointer to the struct s_stack to copy from
 * \return pop element
 */
void*
stack_lifo_pop(ps_stack_lifo p_stack) {
    return p_stack->stack.array_of_pv_data[--(p_stack->stack.nb_elements)];
}

/**
 * \fn stack_lifo_swap(ps_stack_lifo p_stack)
 * \brief swap two last elements in stack
 *
 * \param p_stack pointer to the struct s_stack to copy from
 */
void
stack_lifo_swap(ps_stack_lifo p_stack) {
    if ( p_stack->stack.nb_elements >= 2 ) {
        int index_last = p_stack->stack.nb_elements-1 ;
        int index_prev = index_last-1;
        void* pv_data = p_stack->stack.array_of_pv_data[ index_last ] ;
        p_stack->stack.array_of_pv_data[ index_last ] = p_stack->stack.array_of_pv_data[ index_prev ] ;
        p_stack->stack.array_of_pv_data[ index_prev ] = pv_data ;
    }
}

/**
 * \fn stack_lifo_dup(ps_stack_lifo p_stack)
 * \brief duplicate last elements in stack
 *
 * \param p_stack pointer to the struct s_stack to copy from
 */
void
stack_lifo_dup(ps_stack_lifo p_stack) {
    if ( p_stack->stack.nb_elements > 0 ) {
        int index_last = p_stack->stack.nb_elements-1 ;
        void* pv_data = p_stack->stack.array_of_pv_data[ index_last ] ;
        vector_add_element(&(p_stack->stack), pv_data);
    }
}

/**
 * \fn stack_lifo_dup_n(ps_stack_lifo p_stack, int n)
 * \brief duplicate n last elements in stack
 * \todo code
 *
 * \param p_stack pointer to the struct s_stack to copy from
 * \param n number of elements to duplicate
 */
void
stack_lifo_dup_n(ps_stack_lifo p_stack, int n) {
}

/**
 * \fn stack_lifo_drop_n(ps_stack_lifo p_stack, int n)
 * \brief remove n last elements in stack
 * \todo code
 *
 * \param p_stack pointer to the struct s_stack to copy from
 * \param n number of elements to remove
 */
void
stack_lifo_drop_n(ps_stack_lifo p_stack, int n) {
}

/**
 * \fn stack_for_each(ps_stack_lifo p_stack, p_func_stack_for_each_callback pf_func)
 * \brief for each element call pf_func
 *
 * \param p_stack pointer to the struct s_stack
 * \param pf_func callback used for each element
 */
void
stack_for_each(ps_stack_lifo p_stack, p_func_stack_for_each_callback pf_func) {
    vector_for_each(&(p_stack->stack), pf_func);
}

/**
 * \fn stack_for_each_with_parameters(ps_stack_lifo p_stack, p_func_stack_for_each_with_param_callback pf_func, const void* pv_param1, const void* pv_param2)
 * \brief for each element call pf_func, the two parameters are passed to the callback
 *
 * \param p_stack pointer to the struct s_stack
 * \param pf_func callback used for each element
 * \param pv_param1 first parameter pass to callback 
 * \param pv_param2 second parameter pass to callback 
 */
void
stack_for_each_with_parameters(ps_stack_lifo p_stack, p_func_stack_for_each_with_param_callback pf_func, const void* pv_param1, const void* pv_param2) {
    vector_for_each_with_parameters(&(p_stack->stack), pf_func, pv_param1, pv_param2);
}
