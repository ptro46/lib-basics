/**
 * \file list.c
 * \brief handling a doubly linked list
 * \author Patrice Trognon
 * \version 1.0
 * \date 30 mars 2022
 */

#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "vector.h"

/**
 * \fn list_init(ps_list p_list, bool is_sorted, p_func_list_compare pf_compare)
 * \brief init one list
 *
 * \param p_list pointer to the struct s_list to initialize
 * \param is_sorted if true list is sorted with pf_compare callback
 * \param pf_compare callback to compare to list elements, used if sorted
 */
void
list_init(ps_list                 p_list ,
          bool                    is_sorted,
          p_func_list_compare     pf_compare) {
    if ( p_list != NULL ) {
        p_list->p_first = NULL ;
        p_list->p_last = NULL ;
        p_list->is_sorted = is_sorted ;
        p_list->count=0;
        p_list->pf_compare = pf_compare ;        
    }
}


/**
 * \fn list_free(ps_list p_list)
 * \brief free a list and all nodes, don't free data
 *
 * \param p_list pointer to the struct s_list to free
 */
void
list_free(ps_list p_list) {
    if ( p_list != NULL ) {
        ps_list_data p_current = p_list->p_first ;
        ps_list_data p_prev = NULL ;
        while ( p_current != NULL ) {
            p_prev = p_current ;
            p_current = p_current->p_next ;
            free(p_prev);
        }
    }
}

/**
 * \fn list_copy(ps_list p_list, ps_list p_list_to)
 * \brief clone list to new list with data copy
 *
 * \param p_list pointer to the struct s_list to copy from
 * \param p_list_to pointer to the struct s_list to copy to
 */
void
list_copy(ps_list p_list, ps_list p_list_to) {
    list_init(p_list_to, p_list->is_sorted, p_list->pf_compare);
    ps_list_data p_current = p_list->p_first ;
    while ( p_current != NULL ) {
        list_add(p_list_to, p_current->pv_data);
        p_current = p_current->p_next;
    }   
}

/**
 * \fn list_to_vector(ps_list p_list, ps_vector p_vector)
 * \brief convert list to vector
 *
 * \param p_list pointer to the struct s_list to copy from
 * \param p_vector pointer to the struct s_vector to copy to
 */
void
list_to_vector(ps_list p_list, ps_vector p_vector) {
    ps_list_data p_current = p_list->p_first ;
    vector_init(p_vector, p_list->count);
    while ( p_current != NULL ) {
        vector_add_element(p_vector, p_current->pv_data) ;
        p_current = p_current->p_next;
    }
}

/**
 * \fn list_add(ps_list p_list, void* pv_data)
 * \brief add one element, return elements count
 *
 * \param p_list pointer to the struct s_list
 * \param pv_data pointer to the data to add
 * \return list elements count
 */
int
list_add(ps_list   p_list,
         void*     pv_data) {
    if ( p_list != NULL ) {
        if ( p_list->is_sorted == false ) {
            if ( p_list->p_first == NULL ) {
                p_list->p_first = calloc(1, sizeof(s_list_data)) ;
                p_list->p_first->pv_data = pv_data ;
                p_list->p_last = p_list->p_first ;
            } else {
                ps_list_data p_current = calloc(1, sizeof(s_list_data)) ;
                p_current->pv_data = pv_data ;
                p_current->p_prev = p_list->p_last ;
                p_list->p_last->p_next = p_current ;
                p_list->p_last = p_current ;
            }      
            p_list->count++;
        } else {
            if ( p_list->pf_compare != NULL ) {
                if ( p_list->p_first == NULL ) {
                    p_list->p_first = calloc(1, sizeof(s_list_data)) ;
                    p_list->p_first->pv_data = pv_data ;
                    p_list->p_last = p_list->p_first ;
                } else {
                    if ( p_list->pf_compare(pv_data, p_list->p_first->pv_data) < 0 ) {
                        // insert before first
                        ps_list_data p_new = calloc(1, sizeof(s_list_data)) ;
                        p_new->pv_data = pv_data ;
                        p_new->p_next = p_list->p_first ;
                        p_list->p_first->p_prev = p_new ;
                        p_new->p_prev = NULL ;
                        p_list->p_first = p_new ;
                    } else if ( p_list->pf_compare(pv_data, p_list->p_last->pv_data) > 0 ) {
                        // insert after last
                        ps_list_data p_new = calloc(1, sizeof(s_list_data)) ;
                        p_new->pv_data = pv_data ;
                        p_new->p_prev = p_list->p_last;
                        p_new->p_next = NULL ;
                        p_list->p_last->p_next = p_new ;
                        p_list->p_last = p_new ;
                    } else {
                        // search insert cellule
                        ps_list_data p_current = p_list->p_first;
                        unsigned int index = 0 ;
                        while ( p_list->pf_compare(pv_data, p_current->pv_data) >= 0 &&
                                index < p_list->count ) {
                            p_current = p_current->p_next ;
                            index++;
                        }
                        // insert before p_current
                        ps_list_data p_new = calloc(1, sizeof(s_list_data)) ;
                        p_new->pv_data = pv_data ;
                        p_new->p_next = p_current ;
                        p_new->p_prev = p_current->p_prev ;
                        p_new->p_prev->p_next = p_new ;
                        p_current->p_prev = p_new ;
                    }
                }      
                p_list->count++;
            }
        }
        return p_list->count;
    }
    return 0;
}


/**
 * \fn list_remove_at(ps_list p_list, unsigned int index)
 * \brief remove one element at index, return elements count
 *
 * \param p_list pointer to the struct s_list
 * \param index elements index to remove
 * \return list elements count
 */
int
list_remove_at(ps_list         p_list,
               unsigned int    index) {    
    if ( p_list != NULL ) {
        if ( index < p_list->count ) {
            unsigned int count=0;
            ps_list_data p_current = p_list->p_first ;
            while ( p_current != NULL && count < index ) {
                p_current = p_current->p_next;
                count++;
            }
            if ( count == index && p_current != NULL ) {
                ps_list_data p_prev = p_current->p_prev ;
                ps_list_data p_next = p_current->p_next ;
                p_prev->p_next = p_next ;
                p_next->p_prev = p_prev ;
                free(p_current);
                p_list->count--;
            }
        }
    }
    return p_list->count;
}

/**
 * \fn list_remove_element(ps_list p_list, void* pv_data, p_func_list_compare pf_compare)
 * \brief remove one element, return elements count, pf_compare can be null if set by list_init
 *
 * \param p_list pointer to the struct s_list
 * \param pv_data element to remove
 * \param pf_compare callback to compare two elements, used to find element to be removed
 * \return list elements count
 */
int
list_remove_element(ps_list              p_list,
                    void*                pv_data,
                    p_func_list_compare  pf_compare) {
    p_func_list_compare pf_c = NULL ;
    if ( pf_compare != NULL ) {
        pf_c = pf_compare ;
    } else if ( p_list->pf_compare != NULL ) {
        pf_c = p_list->pf_compare ;
    } else {
        if ( p_list != NULL ) {
            return p_list->count;
        }
        return 0;
    }

    if ( p_list != NULL ) {
        ps_list_data p_current = p_list->p_first ;
        while ( p_current != NULL &&
                0 != pf_c(p_current->pv_data, pv_data) ) {
            p_current = p_current->p_next;
        }
        if ( p_current != NULL ) {
            ps_list_data p_prev = p_current->p_prev ;
            ps_list_data p_next = p_current->p_next ;
            p_prev->p_next = p_next ;
            p_next->p_prev = p_prev ;
            free(p_current);
            p_list->count--;
        }
    }
    return p_list->count;
}

/**
 * \fn list_for_each(ps_list p_list, p_func_list_for_each_callback pf_func)
 * \brief for each element call pf_func
 *
 * \param p_list pointer to the struct s_list
 * \param pf_func callback used for each element
 */
void
list_for_each(ps_list                          p_list,
              p_func_list_for_each_callback    pf_func) {
    if ( p_list != NULL ) {
        ps_list_data p_current = p_list->p_first ;
        while ( p_current != NULL ) {
            pf_func( p_current->pv_data);
            p_current = p_current->p_next;
        }
    }
}

/**
 * \fn list_for_each_with_limit(ps_list p_list, p_func_list_for_each_index_callback pf_func, unsigned int limit)
 * \brief for each element until limit call pf_func
 *
 * \param p_list pointer to the struct s_list
 * \param pf_func callback used for each element
 * \param limit for each stop at limit
 */
void
list_for_each_with_limit(ps_list                              p_list,
                         p_func_list_for_each_index_callback  pf_func,
                         unsigned int                         limit) {
    if ( p_list != NULL && limit > 0 ) {
        unsigned int count=0;
        ps_list_data p_current = p_list->p_first ;
        while ( p_current != NULL && count < limit ) {
            pf_func(count, p_current->pv_data);
            p_current = p_current->p_next;
            count++;
        }
    }
}

/**
 * \fn list_for_each_with_parameters(ps_list p_list, p_func_list_for_each_with_param_callback pf_func, const void* pv_param1, const void* pv_param2)
 * \brief for each element call pf_func, the two parameters are passed to the callback
 *
 * \param p_list pointer to the struct s_list
 * \param pf_func callback used for each element
 * \param pv_param1 first parameter pass to callback 
 * \param pv_param2 second parameter pass to callback 
 */
void
list_for_each_with_parameters(ps_list                                  p_list,
                              p_func_list_for_each_with_param_callback pf_func,
                              const void*                              pv_param1,
                              const void*                              pv_param2) {
    if ( p_list != NULL ) {
        ps_list_data p_current = p_list->p_first ;
        while ( p_current != NULL ) {
            pf_func( p_current->pv_data, pv_param1, pv_param2);
            p_current = p_current->p_next;
        }
    }
}

/**
 * \fn list_for_each_with_limit_and_parameters(ps_list p_list, p_func_list_for_each_index_with_param_callback pf_func, unsigned int limit, const void* pv_param1, const void* pv_param2)
 * \brief for each element until limit call pf_func, the two parameters are passed to the callback
 *
 * \param p_list pointer to the struct s_list
 * \param pf_func callback used for each element
 * \param limit for each stop at limit
 * \param pv_param1 first parameter pass to callback 
 * \param pv_param2 second parameter pass to callback 
 */
void
list_for_each_with_limit_and_parameters(ps_list                                         p_list,
                                        p_func_list_for_each_index_with_param_callback  pf_func,
                                        unsigned int                                    limit,
                                        const void*                                     pv_param1,
                                        const void*                                     pv_param2) {
    if ( p_list != NULL && limit > 0 ) {
        unsigned int count=0;
        ps_list_data p_current = p_list->p_first ;
        while ( p_current != NULL && count < limit ) {
            pf_func(count, p_current->pv_data, pv_param1, pv_param2);
            p_current = p_current->p_next;
            count++;
        }
    }
}

/**
 * \fn list_get_at(ps_list p_list, unsigned int index)
 * \brief get one element at index, return element
 *
 * \param p_list pointer to the struct s_list
 * \param index index of element to get
 * \return pointer to data found at index, NULL if not
 */
void*
list_get_at(ps_list         p_list,
            unsigned int    index) {
    if ( p_list != NULL ) {
        if ( index < p_list->count ) {
            unsigned int count=0;
            ps_list_data p_current = p_list->p_first ;
            while ( p_current != NULL && count < index ) {
                p_current = p_current->p_next;
                count++;
            }
            if ( count == index && p_current != NULL ) {
                return p_current->pv_data ;
            }
        }
    }
    return NULL;
}

/**
 * \fn list_get_element(ps_list p_list, void* pv_data, p_func_list_compare pf_compare)
 * \brief get one element, return elements count or null if not found, pf_compare can be null if set by list_init
 *
 * \param p_list pointer to the struct s_list
 * \param pv_data data to find
 * \param pf_compare callback used to compare two elements
 * \return pointer to data found , NULL if not
 */
void*
list_get_element(ps_list              p_list,
                 void*                pv_data,
                 p_func_list_compare  pf_compare) {
    p_func_list_compare pf_c = NULL ;
    if ( pf_compare != NULL ) {
        pf_c = pf_compare ;
    } else if ( p_list->pf_compare != NULL ) {
        pf_c = p_list->pf_compare ;
    } else {
        return NULL;
    }
    
    if ( p_list != NULL ) {
        ps_list_data p_current = p_list->p_first ;
        while ( p_current != NULL &&
                0 != pf_c(p_current->pv_data, pv_data) ) {
            p_current = p_current->p_next;
        }
        if ( p_current != NULL ) {
            return p_current->pv_data;
        }
    }
    return NULL ;
}

/**
 * \fn list_get_first(ps_list   p_list)
 * \brief get first cell
 *
 * \param p_list pointer to the struct s_list
 * \return pointer to struct s_list_data at first position , NULL if not
 */
ps_list_data
list_get_first(ps_list   p_list) {
    if ( p_list != NULL ) {
        return p_list->p_first ;
    }
    return NULL ;
}

/**
 * \fn list_get_last(ps_list   p_list)
 * \brief get last cell
 *
 * \param p_list pointer to the struct s_list
 * \return pointer to struct s_list_data at last position , NULL if not
 */
ps_list_data
list_get_last(ps_list    p_list) {
    if ( p_list != NULL ) {
        return p_list->p_last ;
    }
    return NULL ;
}

/**
 * \fn list_get_next(ps_list p_list, ps_list_data p_current)
 * \brief get next cell
 *
 * \param p_list pointer to the struct s_list
 * \param p_current pointer to current struct s_list_data
 * \return pointer to struct s_list_data at next position , NULL if not
 */
ps_list_data
list_get_next(ps_list        p_list,
              ps_list_data   p_current) {
    if ( p_list != NULL ) {
        return p_current->p_next;
    }    
    return NULL ;
}

/**
 * \fn list_get_prev(ps_list p_list, ps_list_data p_current)
 * \brief get previous cell
 *
 * \param p_list pointer to the struct s_list
 * \param p_current pointer to current struct s_list_data
 * \return pointer to struct s_list_data at previous position , NULL if not
 */
ps_list_data
list_get_prev(ps_list        p_list,
              ps_list_data   p_current) {
    if ( p_list != NULL ) {
        return p_current->p_prev;
    }    
    return NULL ;
}

/**
 * \fn file_buffer_lines_to_list(ps_buffer p_buf_in, ps_list p_list)
 * \brief return each buffer line in list element of ps_buffer
 *
 * \param ps_buffer p_buf_in pointer to input buffer
 * \param p_list pointer to the struct s_list
 */
void
file_buffer_lines_to_list(ps_buffer p_buf_in, ps_list p_list) {
    s_buffer buf_wotk ;
    char*    pstr;

    buffer_init(&buf_wotk, p_buf_in->offset+1);
    buffer_append_buffer(&buf_wotk, p_buf_in);
    pstr = buffer_stringify(&buf_wotk);
    char* p_str = strdup(pstr);
    char* p_to_free = p_str ;
    char* p_token = NULL ;
    p_token = strsep(&p_str, "\n");
    while( p_token != NULL ) {
        size_t size_of_line = strlen(p_token) ;
        ps_buffer p_buf_line = calloc(1,sizeof(s_buffer));
        buffer_init(p_buf_line, size_of_line);
        buffer_append(p_buf_line, p_token, size_of_line);
        list_add(p_list, p_buf_line);
        p_token = strsep(&p_str, "\n");
    }
    free(p_to_free);
    buffer_free(&buf_wotk);
    
}
