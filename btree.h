/**
 * \file btree.h
 * \brief binary search tree (BST)
 * \author Patrice Trognon
 * \version 1.0
 * \date 30 mars 2022
 */

#ifndef __BTREE_H__
#define __BTREE_H__

#include "b_types.h"

/**
 * \brief forward declaration
 */
typedef struct vector *ps_vector ;

/**
 * \brief forward declaration
 */
typedef struct list *ps_list ;

/**
 * \brief forward declaration
 */
typedef struct buffer *ps_buffer ;


/**
 * \fn (*p_func_btree_compare_key)(const void *pv_key1, const void* pv_key2)
 * \brief callback used to compare two keys
 *
 * \param pv_key1 pointer to first key
 * \param pv_key2 pointer to second key
 * \return <0 if key1<key2, 0 if key1==key2, >0 if key1>key2
 */
typedef int            (*p_func_btree_compare_key)(const void *pv_key1, const void* pv_key2);

/**
 * \fn (*p_func_btree_for_each)(const void *pv_key, const void* pv_value)
 * \brief callback used for each btree element (key , value)
 * this callback is used by btree_foreach_infix, btree_foreach_prefix, btree_foreach_postfix
 *
 * \param pv_key pointer to key element
 * \param pv_value pointer to value element
 */
typedef void           (*p_func_btree_for_each)(const void *pv_key, const void* pv_value);

/**
 * \fn (*p_func_btree_for_each_with_parameters)(const void *pv_key, const void* pv_value, const void* pv_param1, void* pv_param2)
 * \brief callback used for each btree element (key , value), and two parameters
 * this callback is used by btree_foreach_infix_with_parameter, btree_foreach_prefix_with_parameter, btree_foreach_postfix_with_parameter
 *
 * \param pv_key pointer to key element
 * \param pv_value pointer to value element
 * \param pv_param1 pointer to first parameter
 * \param pv_param2 pointer to second parameter
 */
typedef void           (*p_func_btree_for_each_with_parameters)(const void *pv_key, const void* pv_value, const void* pv_param1, void* pv_param2);


/**
 * \struct kv
 * \brief one hash entry, contains key, sizeof(key) and value
 */
struct kv {
    void*                pv_key;        /*!< key pointer */
    void*                pv_value;      /*!< value pointer */
} ;

/**
 * \typedef s_kv
 * \brief one kv
 */
typedef struct kv s_kv ;

/**
 * \typedef ps_kv
 * \brief pointer to one s_kv
 */
typedef struct kv *ps_kv ;


/**
 * \struct tree_node
 * \brief one tree entry, contains key, sizeof(key) and value
 */
struct tree_node {
    void*                pv_key;        /*!< key pointer */
    void*                pv_value;      /*!< value pointer */
    struct tree_node*    p_node_parent; /*!< pointer to parent tree_node */
    struct tree_node*    p_node_left;   /*!< pointer to left child tree_node */
    struct tree_node*    p_node_right;  /*!< pointer to right child tree_node */
} ;

/**
 * \typedef s_tree_node
 * \brief one tree node
 */
typedef struct tree_node s_tree_node ;

/**
 * \typedef ps_tree_node
 * \brief pointer to one s_tree_node
 */
typedef struct tree_node *ps_tree_node ;

/**
 * \struct btree
 * \brief search btree
 */
struct btree {
    ps_tree_node             p_node_root;   /*!< btree root */
    unsigned int             nb_elements;   /*!< btree elements count */
    unsigned int             tree_depth;    /*!< btree depth */
    p_func_btree_compare_key pf_comp;       /*!< key compare func */
} ;

/**
 * \typedef s_btree
 * \brief one btree
 */
typedef struct btree s_btree ;

/**
 * \typedef ps_btree
 * \brief pointer to one s_btree
 */
typedef struct btree *ps_btree ;

void    btree_init(ps_btree p_tree, p_func_btree_compare_key pf_comp) ;
void    btree_free(ps_btree p_tree) ;
void    btree_put(ps_btree p_tree, void* pv_key, void* pv_value);
void*   btree_get(ps_btree p_tree, void* pv_key);
void    btree_keys(ps_btree p_tree, ps_vector p_vector_keys);
void    btree_values(ps_btree p_tree, ps_vector p_vector_values);
void    btree_remove_key(ps_btree p_tree, void* pv_key);

void    btree_foreach_infix(ps_btree p_tree, p_func_btree_for_each pf_func);
void    btree_foreach_prefix(ps_btree p_tree, p_func_btree_for_each pf_func);
void    btree_foreach_postfix(ps_btree p_tree, p_func_btree_for_each pf_func);

void    btree_foreach_infix_with_parameter(ps_btree p_tree, p_func_btree_for_each_with_parameters pf_func, const void* pv_param1, void* pv_param2);
void    btree_foreach_prefix_with_parameter(ps_btree p_tree, p_func_btree_for_each_with_parameters pf_func, const void* pv_param1, void* pv_param2);
void    btree_foreach_postfix_with_parameter(ps_btree p_tree, p_func_btree_for_each_with_parameters pf_func, const void* pv_param1, void* pv_param2);

void    btree_rebuild(ps_btree p_tree_old, ps_btree p_tree_new) ;
/*
 * used for debug
 */

/**
 * \fn (*p_func_key_to_string)(const void *pv_key, ps_buffer p_buffer)
 * \brief callback used dump pv_key to string (used for debug)
 *
 * \param pv_key pointer key
 * \param p_buffer pointer to struct buffer
 */
typedef void            (*p_func_key_to_string)(const void *pv_key, ps_buffer p_buffer);
typedef void            (*p_func_key_to_string_psz)(const void *pv_key, char* p_buffer);

/**
 * \fn (*p_func_value_to_string)(const void *pv_value, ps_buffer p_buffer)
 * \brief callback used dump pv_key to string (used for debug)
 *
 * \param pv_value pointer value
 * \param p_buffer pointer to struct buffer
 */
typedef void            (*p_func_value_to_string)(const void *pv_value, ps_buffer p_buffer);
typedef void            (*p_func_value_to_string_psz)(const void *pv_value, char* p_buffer);

void    btree_node_to_dot(ps_tree_node             p_node,
                          ps_buffer                p_buffer_nodes,
                          ps_buffer                p_buffer_edges,
                          p_func_key_to_string     pf_key_string,
                          p_func_value_to_string   pf_value_string);

void    btree_to_dot(ps_btree                 p_tree,
                     const char*              dot_filename,
                     p_func_key_to_string     pf_key_string,
                     p_func_value_to_string   pf_value_string) ;

void    btree_check_integrity(ps_btree                     p_tree,
                              ps_tree_node                 p_node,
                              p_func_key_to_string_psz     pf_key_string,
                              p_func_value_to_string_psz   pf_value_string);

#endif /* __BTREE_H__ */
