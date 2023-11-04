/**
 * \file list.h
 * \brief handling a doubly linked list
 * \author Patrice Trognon
 * \version 1.0
 * \date 30 mars 2022
 */

#ifndef __LIST_H__
#define __LIST_H__

#include "b_types.h"
#include "buffer.h"

/**
 * \brief forward declaration
 */
typedef struct vector *ps_vector ;

/**
 * \fn (*p_func_list_for_each_callback)(const void* pv_data)
 * \brief callback used for each list element
 * this callback is used by list_for_each
 *
 * \param pv_data pointer to data element
 */
typedef void    (*p_func_list_for_each_callback)(const void*);

/**
 * \fn (*p_func_list_for_each_index_callback)(int index, const void* pv_data)
 * \brief callback used for each list element and its index
 * this callback is used by list_for_each_with_limit
 *
 * \param index index value
 * \param pv_data pointer to data element
 */
typedef void    (*p_func_list_for_each_index_callback)(int,const void*);

/**
 * \fn (*p_func_list_for_each_with_param_callback)(const void* pv_data, const void* pv_param1, const void* pv_param2)
 * \brief callback used for each list element, the two pointers passed as parameters are passed back to the callback
 * this callback is used by list_for_each_with_parameters
 *
 * \param pv_data pointer to data element
 * \param pv_param1 pointer to first parameter
 * \param pv_param2 pointer to second parameter
 */
typedef void    (*p_func_list_for_each_with_param_callback)(const void*, const void*, const void*);

/**
 * \fn (*p_func_list_for_each_index_with_param_callback)(int index,const void* pv_data, const void* pv_param1, const void* pv_param2)
 * \brief callback used for each list element and its index, the two pointers passed as parameters are passed back to the callback
 * this callback is used by list_for_each_with_limit_and_parameters
 *
 * \param index index value
 * \param pv_data pointer to data element
 * \param pv_param1 pointer to first parameter
 * \param pv_param2 pointer to second parameter
 */
typedef void    (*p_func_list_for_each_index_with_param_callback)(int,const void*, const void*, const void*);

/**
 * \fn (*p_func_list_compare)(const void* pv_data1, const void* pv_data2)
 * \brief callback used to compare two elements
 * this callback is used by list_add if its init as sorted
 *
 * \param pv_data1 pointer to first element
 * \param pv_data2 pointer to second element
 * \return <0 if less than, 0 if equal, >0 if greater than
 */
typedef int     (*p_func_list_compare)(const void*, const void*);

/**
 * \struct list_data
 * \brief one list element
 */
struct list_data {
    void*               pv_data ;   /*!< cell list data */
    struct list_data*   p_prev ;    /*!< pointer to next cell */
    struct list_data*   p_next ;    /*!< pointer to previous cell */
} ;

/**
 * \typedef s_list_data
 * \brief one list element
 */
typedef struct list_data s_list_data ;

/**
 * \typedef ps_list_data
 * \brief pointer to one list element
 */
typedef struct list_data *ps_list_data ;

/**
 * \struct list
 * \brief list header
 */
struct list {
    ps_list_data    p_first ;       /*!< pointer to first cell  */
    ps_list_data    p_last ;        /*!< pointer to last cell */
    bool            is_sorted;      /*!< true if list is sorted */
    unsigned int    count;          /*!< number of elements */

    p_func_list_compare    pf_compare; /*!< pointer compare callback  */
} ;

/**
 * \typedef s_list
 * \brief list
 */
typedef struct list s_list ;

/**
 * \typedef ps_list
 * \brief pointer to one list
 */
typedef struct list *ps_list ;

void   list_init(ps_list                 p_list ,
                 bool                    is_sorted,
                 p_func_list_compare     pf_compare) ;

void   list_free(ps_list p_list);

void   list_copy(ps_list p_list, ps_list p_list_to);
void   list_to_vector(ps_list p_list, ps_vector p_vector);

int    list_add(ps_list   p_list,
                void*     pv_data);

void   internal_remove_element(ps_list         p_list,
                               ps_list_data    p_current) ;

int    list_remove_at(ps_list         p_list,
                      unsigned int    index);
int    list_remove_element(ps_list              p_list,
                           void*                pv_data,
                           p_func_list_compare  pf_compare);

void   list_for_each(ps_list                          p_list,
                     p_func_list_for_each_callback    pf_func);
void   list_for_each_with_limit(ps_list                              p_list,
                                p_func_list_for_each_index_callback  pf_func,
                                unsigned int                         limit);

void   list_for_each_with_parameters(ps_list                                  p_list,
                                     p_func_list_for_each_with_param_callback pf_func,
                                     const void*                              pv_param1,
                                     const void*                              pv_param2);
void   list_for_each_with_limit_and_parameters(ps_list                                         p_list,
                                               p_func_list_for_each_index_with_param_callback  pf_func,
                                               unsigned int                                    limit,
                                               const void*                                     pv_param1,
                                               const void*                                     pv_param2);

void*  list_get_at(ps_list         p_list,
                   unsigned int    index);
void*  list_get_element(ps_list              p_list,
                        void*                pv_data,
                        p_func_list_compare  pf_compare);

ps_list_data    list_get_first(ps_list   p_list);
ps_list_data    list_get_last(ps_list    p_list);
ps_list_data    list_get_next(ps_list    p_list, ps_list_data   p_current);
ps_list_data    list_get_prev(ps_list    p_list, ps_list_data   p_current);

void   file_buffer_lines_to_list(ps_buffer p_buf_in, ps_list p_list);

#endif /* __LIST_H__ */
