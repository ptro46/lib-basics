/**
 * \file btree.c
 * \brief binary search tree (BST)
 * \author Patrice Trognon
 * \version 1.0
 * \date 30 mars 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include "btree.h"
#include "list.h"
#include "vector.h"
#include "buffer.h"

/*
struct tree_node {
    void*                pv_key;
    void*                pv_value;
    struct tree_node*    p_node_parent;
    struct tree_node*    p_node_left;
    struct tree_node*    p_node_right;
} ;

struct btree {
    ps_tree_node             p_node_root;
    unsigned int             nb_elements;
    unsigned int             tree_depth;
    p_func_btree_compare_key pf_comp;
} ;
*/

static ps_tree_node node_alloc_init(ps_tree_node p_parent, void* pv_key, void* pv_value);
static ps_tree_node btree_search_parent(ps_btree p_tree, ps_tree_node p_node, void* pv_key) ;
static ps_tree_node btree_search_key(ps_btree p_tree, ps_tree_node p_node, void* pv_key) ;
static ps_tree_node btree_search_greater(ps_btree p_tree, ps_tree_node p_node) ;

static void btree_node_free(ps_tree_node p_node);

static void    btree_node_foreach_infix(ps_btree p_tree, ps_tree_node p_node, p_func_btree_for_each pf_func);
static void    btree_node_foreach_prefix(ps_btree p_tree, ps_tree_node p_node, p_func_btree_for_each pf_func);
static void    btree_node_foreach_postfix(ps_btree p_tree, ps_tree_node p_node, p_func_btree_for_each pf_func);


static void    btree_node_foreach_infix_with_parameter(ps_btree                                 p_tree,
                                                       ps_tree_node                             p_node,
                                                       p_func_btree_for_each_with_parameters    pf_func,
                                                       const void*                              pv_param1,
                                                       void*                                    pv_param2);

static void    btree_node_foreach_prefix_with_parameter(ps_btree                                p_tree,
                                                        ps_tree_node                            p_node,
                                                        p_func_btree_for_each_with_parameters   pf_func,
                                                        const void*                             pv_param1,
                                                        void*                                   pv_param2);

static void    btree_node_foreach_postfix_with_parameter(ps_btree                               p_tree,
                                                         ps_tree_node                           p_node,
                                                         p_func_btree_for_each_with_parameters  pf_func,
                                                         const void*                            pv_param1,
                                                         void*                                  pv_param2);

static void    callback_for_each_with_parameters_rebuilt_vector(const void* pv_key, const void* pv_value, const void* pv_param1, void* pv_param2);
static void    callback_for_each_vector_free(unsigned int index, const void* pv_value);

static void    btree_rebuild_with_pivot(ps_btree p_tree, ps_vector p_vector_of_kv, int index_min, int index_max) ;

void    btree_node_to_dot(ps_tree_node             p_node,
                          ps_buffer                p_buffer_nodes,
                          ps_buffer                p_buffer_edges,
                          p_func_key_to_string     pf_key_string,
                          p_func_value_to_string   pf_value_string) {
    s_buffer buf_node_key ;

    s_buffer buf_left_node_key ;
    s_buffer buf_right_node_key ;

    buffer_init(&buf_node_key, 128);
    buffer_init(&buf_left_node_key, 128);
    buffer_init(&buf_right_node_key, 128);
    
    buffer_append_f(&buf_node_key,"\"");
    pf_key_string(p_node->pv_key, &buf_node_key);
    buffer_append_f(&buf_node_key," %p\"",p_node->pv_key);

    if ( p_node->p_node_left != NULL ) {
        buffer_append_f(&buf_left_node_key,"\"");
        pf_key_string(p_node->p_node_left->pv_key, &buf_left_node_key);
        buffer_append_f(&buf_left_node_key," %p\"",p_node->p_node_left->pv_key);        
    } else {
        buffer_append_f(&buf_left_node_key,"\"null\"");
    }

    if ( p_node->p_node_right != NULL ) {
        buffer_append_f(&buf_right_node_key,"\"");
        pf_key_string(p_node->p_node_right->pv_key, &buf_right_node_key);
        buffer_append_f(&buf_right_node_key," %p\"",p_node->p_node_right->pv_key);        
    } else {
        buffer_append_f(&buf_right_node_key,"\"null\"");
    }

    buffer_append_buffer(p_buffer_nodes, &buf_node_key);
    buffer_append_f(p_buffer_nodes," [fontname=\"Helvetica\" color=\"violetred4\" peripheries=\"1\" fontsize=\"10\" label=<");
    pf_key_string(p_node->pv_key, p_buffer_nodes);
    buffer_append_f(p_buffer_nodes,">];\n");
    
/*
    buffer_append_f(p_buffer_nodes,"<<TABLE BORDER=\"0\" bgcolor=\"grey80\"><TR><TD COLSPAN=\"2\" bgcolor=\"grey52\">");
    buffer_append_buffer(p_buffer_nodes, &buf_node_key);
    buffer_append_f(p_buffer_nodes,"</TD></TR><TR><TD bgcolor=\"grey52\" align=\"left\">");
    pf_key_string(p_node->pv_key, p_buffer_nodes);
    buffer_append_f(p_buffer_nodes,"</TD><TD bgcolor=\"grey52\" align=\"right\">");
    pf_value_string(p_node->pv_value, p_buffer_nodes);
    buffer_append_f(p_buffer_nodes,"</TD></TR><TR><TD align=\"left\">");
    buffer_append_buffer(p_buffer_nodes, &buf_left_node_key);
    buffer_append_f(p_buffer_nodes,"</TD><TD align=\"right\">");
    buffer_append_buffer(p_buffer_nodes, &buf_right_node_key);
    buffer_append_f(p_buffer_nodes,"</TD></TR>");
    buffer_append_f(p_buffer_nodes,"</TABLE>>];\n");
*/  
    if ( p_node->p_node_left != NULL ) {
        buffer_append_buffer(p_buffer_edges, &buf_node_key);
        buffer_append_f(p_buffer_edges," -> ");
        buffer_append_buffer(p_buffer_edges, &buf_left_node_key);
        buffer_append_f(p_buffer_edges," [color=\"blue\" fontsize=\"6\" labelcolor=\"blue\" fontcolor=\"blue\" arrowhead=\"normal\" label=\"left\"]\n");

        btree_node_to_dot( p_node->p_node_left, p_buffer_nodes, p_buffer_edges, pf_key_string, pf_value_string);
    }
    if ( p_node->p_node_right != NULL ) {
        buffer_append_buffer(p_buffer_edges, &buf_node_key);
        buffer_append_f(p_buffer_edges," -> ");
        buffer_append_buffer(p_buffer_edges, &buf_right_node_key);
        buffer_append_f(p_buffer_edges," [color=\"red\" fontsize=\"6\" labelcolor=\"red\" fontcolor=\"red\" arrowhead=\"normal\" label=\"right\"]\n");

        btree_node_to_dot( p_node->p_node_right, p_buffer_nodes, p_buffer_edges, pf_key_string, pf_value_string);
    }    

    buffer_free(&buf_node_key);
    buffer_free(&buf_left_node_key);
    buffer_free(&buf_right_node_key);
}

void    btree_to_dot(ps_btree                 p_tree,
                     const char*              dot_filename,
                     p_func_key_to_string     pf_key_string,
                     p_func_value_to_string   pf_value_string) {
    s_buffer buffer_nodes ;
    s_buffer buffer_edges ;

    buffer_init(&buffer_nodes, 5*1024);
    buffer_init(&buffer_edges, 5*1024);

    if ( p_tree != NULL ) {
        if ( p_tree->p_node_root != NULL ) {
            btree_node_to_dot( p_tree->p_node_root, &buffer_nodes, &buffer_edges, pf_key_string, pf_value_string);
        }
    }

    

    FILE* h = fopen(dot_filename,"wt");
    fprintf(h,"digraph \"BST\" {\n");
//    fprintf(h,"node [shape=plaintext];\n");
    fprintf(h,"%s\n",buffer_stringify(&buffer_nodes));
    fprintf(h,"%s\n",buffer_stringify(&buffer_edges));
    fprintf(h,"}\n");
    fclose(h);
    
    buffer_free(&buffer_edges);
    buffer_free(&buffer_nodes);
}

void
btree_init(ps_btree p_tree, p_func_btree_compare_key pf_comp) {
    if ( p_tree != NULL ) {
        p_tree->p_node_root = NULL ;
        p_tree->nb_elements = 0 ;
        p_tree->tree_depth = 0 ;
        p_tree->pf_comp = pf_comp ;
    }
}

void
btree_free(ps_btree p_tree) {
    if ( p_tree != NULL && p_tree->p_node_root != NULL ) {
        btree_node_free(p_tree->p_node_root);
    }
}

void
btree_put(ps_btree p_tree, void* pv_key, void* pv_value) {
    if ( p_tree != NULL ) {
        if ( p_tree->p_node_root == NULL ) {
            // if no root node alloc and set it
            p_tree->p_node_root = node_alloc_init(NULL, pv_key, pv_value);
            p_tree->nb_elements++;
        } else {
            // if root node search parent node to insert
            ps_tree_node p_parent = btree_search_parent(p_tree, p_tree->p_node_root, pv_key) ;
            int i_cmp = p_tree->pf_comp(pv_key, p_parent->pv_key) ;
            if ( i_cmp < 0 ) {
                // if less than add left node
                p_parent->p_node_left = node_alloc_init(p_parent, pv_key, pv_value);
                p_tree->nb_elements++;
            } else if ( i_cmp > 0 ) {
                // if great than add left node
                p_parent->p_node_right = node_alloc_init(p_parent, pv_key, pv_value);
                p_tree->nb_elements++;
            } else {
                // if equal than replace value
                p_parent->pv_value = pv_value ;
            }
        }
    }
}

void*
btree_get(ps_btree p_tree, void* pv_key) {
    if ( p_tree != NULL && p_tree->p_node_root != NULL ) {
        ps_tree_node p_node_found = btree_search_key(p_tree, p_tree->p_node_root, pv_key) ;
        if ( p_node_found != NULL ) {
            return p_node_found->pv_value;
        }
    }
    return NULL ;
}

void
btree_keys(ps_btree p_tree, ps_vector p_vector_keys) {
    if ( p_tree != NULL ) {
    }
}

void
btree_values(ps_btree p_tree, ps_vector p_vector_values) {
    if ( p_tree != NULL ) {
    }
}

static ps_tree_node
btree_search_greater(ps_btree p_tree, ps_tree_node p_node) {
    if ( p_node->p_node_right != NULL ) {
        return btree_search_greater(p_tree, p_node->p_node_right);
    }
    return p_node ;
}

#include "tests.h"

void
btree_remove_key(ps_btree p_tree, void* pv_key) {
    if ( p_tree != NULL && p_tree->p_node_root != NULL ) {
        ps_tree_node p_node_found = btree_search_key(p_tree, p_tree->p_node_root, pv_key) ;
        if ( p_node_found != NULL ) {
            if ( p_node_found->p_node_left == NULL && p_node_found->p_node_right == NULL ) {
                // no childs --> set parent pointer left or right to null, free node
                if ( p_node_found == p_node_found->p_node_parent->p_node_left ) {
//                    printf("node to delete %d parent left\n",((ps_h_int)p_node_found->pv_key)->idx);
                    p_node_found->p_node_parent->p_node_left = NULL ;
                }
                if ( p_node_found == p_node_found->p_node_parent->p_node_right ) {
//                    printf("node to delete %d parent right\n",((ps_h_int)p_node_found->pv_key)->idx);
                    p_node_found->p_node_parent->p_node_right = NULL ;
                }
                p_tree->nb_elements++;
                free(p_node_found);
            }
            else if ( p_node_found->p_node_left == NULL && p_node_found->p_node_right != NULL ) {                
                // one child right --> parent->right set to node->right, free node
                if ( p_node_found->p_node_parent->p_node_left == p_node_found ) {
                    // one child left --> parent->left set to node->left, free node
//                    printf("node to delete %d one child right, parent left\n",((ps_h_int)p_node_found->pv_key)->idx);
                    p_node_found->p_node_parent->p_node_left = p_node_found->p_node_right ;    
                    p_node_found->p_node_right->p_node_parent = p_node_found->p_node_parent;
                } else if ( p_node_found->p_node_parent->p_node_right == p_node_found ) {
                    // one child left --> parent->right set to node->left, free node
//                    printf("node to delete %d one child right, parent right\n",((ps_h_int)p_node_found->pv_key)->idx);
                    p_node_found->p_node_parent->p_node_right = p_node_found->p_node_right ;    
                    p_node_found->p_node_right->p_node_parent = p_node_found->p_node_parent;
                }                               
                p_tree->nb_elements++;
                free(p_node_found);                
            }
            else if ( p_node_found->p_node_left != NULL && p_node_found->p_node_right == NULL ) {
                if ( p_node_found->p_node_parent->p_node_left == p_node_found ) {
                    // one child left --> parent->left set to node->left, free node
//                    printf("node to delete %d one child left, parent left\n",((ps_h_int)p_node_found->pv_key)->idx);
                    p_node_found->p_node_parent->p_node_left = p_node_found->p_node_left ;
                    p_node_found->p_node_left->p_node_parent = p_node_found->p_node_parent;
                } else if ( p_node_found->p_node_parent->p_node_right == p_node_found ) {
                    // one child left --> parent->right set to node->left, free node
//                    printf("node to delete %d one child left, parent right\n",((ps_h_int)p_node_found->pv_key)->idx);
                    p_node_found->p_node_parent->p_node_right = p_node_found->p_node_left ;    
                    p_node_found->p_node_left->p_node_parent = p_node_found->p_node_parent;
                }               
                p_tree->nb_elements++;
                free(p_node_found);
            }
            else if ( p_node_found->p_node_left != NULL && p_node_found->p_node_right != NULL ) {
                ps_tree_node p_node_parent = p_node_found->p_node_parent;
                ps_tree_node p_node_up = btree_search_greater(p_tree, p_node_found->p_node_left);

                // printf("node to delete:%d (parent:%d), replaced_by:%d \n",
                //        ((ps_h_int)p_node_found->pv_key)->idx,
                //        ((ps_h_int)p_node_parent->pv_key)->idx,
                //        ((ps_h_int)p_node_up->pv_key)->idx);

                if ( p_node_up->p_node_left == NULL && p_node_up->p_node_right == NULL ) {
                    // greater node dont have childs
                    if ( p_node_parent->p_node_left == p_node_found ) {
                        p_node_parent->p_node_left = p_node_up ;
                    } else if ( p_node_parent->p_node_right == p_node_found ) {
                        p_node_parent->p_node_right = p_node_up ;
                    }

                    p_node_up->p_node_left = p_node_found->p_node_left ;
                    if ( p_node_found->p_node_left != NULL ) {
                        p_node_found->p_node_left->p_node_parent = p_node_up ;
                    }
                    
                    p_node_up->p_node_right = p_node_found->p_node_right ;
                    if ( p_node_found->p_node_right != NULL ) {
                        p_node_found->p_node_right->p_node_parent = p_node_up ;
                    }
                    
                    if ( p_node_up->p_node_parent->p_node_left == p_node_up ) {
                        p_node_up->p_node_parent->p_node_left = NULL ;
                    } else if ( p_node_up->p_node_parent->p_node_right == p_node_up ) {
                        p_node_up->p_node_parent->p_node_right = NULL ;
                    }
                    p_node_up->p_node_parent = p_node_parent ;
                    p_tree->nb_elements++;
                    free(p_node_found);
                } else {
                    // greater node have one left child (can not have right child because is already greater)
                    if ( p_node_parent->p_node_left == p_node_found ) {
                        p_node_parent->p_node_left = p_node_up ;
                    } else if ( p_node_parent->p_node_right == p_node_found ) {
                        p_node_parent->p_node_right = p_node_up ;
                    }
                    if ( p_node_up->p_node_parent->p_node_left == p_node_up ) {
                        p_node_up->p_node_parent->p_node_left = p_node_up->p_node_left;
                    } else if ( p_node_up->p_node_parent->p_node_right == p_node_up ) {
                        p_node_up->p_node_parent->p_node_right = p_node_up->p_node_left;
                    }
                    p_node_up->p_node_left->p_node_parent = p_node_up->p_node_parent ;
                    p_node_up->p_node_left = p_node_found->p_node_left ;
                    if ( p_node_found->p_node_left != NULL ) {
                        p_node_found->p_node_left->p_node_parent = p_node_up ;
                    }

                    p_node_up->p_node_right = p_node_found->p_node_right ;
                    if ( p_node_found->p_node_right != NULL ) {
                        p_node_found->p_node_right->p_node_parent = p_node_up ;
                    }

                    p_node_up->p_node_parent = p_node_parent ;
                    p_tree->nb_elements++;
                    free(p_node_found);
                }
                
                // printf("node to delete %d\n",((ps_h_int)p_node_found->pv_key)->idx);
                // printf("node greater   %d\n",((ps_h_int)p_greater_node->pv_key)->idx);

            }
        }
    }
}

void
btree_foreach_infix(ps_btree p_tree, p_func_btree_for_each pf_func) {
    if ( p_tree != NULL && p_tree->p_node_root != NULL ) {
        btree_node_foreach_infix(p_tree, p_tree->p_node_root, pf_func);
    }
}

void
btree_foreach_prefix(ps_btree p_tree, p_func_btree_for_each pf_func) {
    if ( p_tree != NULL && p_tree->p_node_root != NULL ) {
        btree_node_foreach_prefix(p_tree, p_tree->p_node_root, pf_func);
    }
}

void
btree_foreach_postfix(ps_btree p_tree, p_func_btree_for_each pf_func) {
    if ( p_tree != NULL && p_tree->p_node_root != NULL ) {
        btree_node_foreach_postfix(p_tree, p_tree->p_node_root, pf_func);
    }
}

void
btree_foreach_infix_with_parameter(ps_btree p_tree, p_func_btree_for_each_with_parameters pf_func, const void* pv_param1, void* pv_param2) {
    if ( p_tree != NULL && p_tree->p_node_root != NULL ) {
        btree_node_foreach_infix_with_parameter(p_tree, p_tree->p_node_root, pf_func, pv_param1, pv_param2);
    }
}

void
btree_foreach_prefix_with_parameter(ps_btree p_tree, p_func_btree_for_each_with_parameters pf_func, const void* pv_param1, void* pv_param2) {
    if ( p_tree != NULL && p_tree->p_node_root != NULL ) {
        btree_node_foreach_prefix_with_parameter(p_tree, p_tree->p_node_root, pf_func, pv_param1, pv_param2);
    }
}

void
btree_foreach_postfix_with_parameter(ps_btree p_tree, p_func_btree_for_each_with_parameters pf_func, const void* pv_param1, void* pv_param2) {
    if ( p_tree != NULL && p_tree->p_node_root != NULL ) {
        btree_node_foreach_postfix_with_parameter(p_tree, p_tree->p_node_root, pf_func, pv_param1, pv_param2);
    }
}

static void
callback_for_each_with_parameters_rebuilt_vector(const void* pv_key, const void* pv_value, const void* pv_param1, void* pv_param2) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    ps_vector p_vector = (ps_vector)pv_param2;
    ps_kv p_kv = calloc(1,sizeof(s_kv));
    p_kv->pv_key = (void*)pv_key ;
    p_kv->pv_value = (void*)pv_value ;
#pragma GCC diagnostic pop
    vector_add_element(p_vector, p_kv);
}

static void
callback_for_each_vector_free(unsigned int index, const void* pv_value) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    ps_kv p_kv = (ps_kv)pv_value;
#pragma GCC diagnostic pop
    free(p_kv);
}

void
btree_rebuild(ps_btree p_tree_old, ps_btree p_tree_new) {
    s_vector        v_of_kv ;
    
    vector_init(&v_of_kv, p_tree_old->nb_elements);
    btree_foreach_infix_with_parameter(p_tree_old, callback_for_each_with_parameters_rebuilt_vector, NULL, &v_of_kv);
    btree_rebuild_with_pivot(p_tree_new, &v_of_kv, 0, v_of_kv.nb_elements-1);
    vector_for_each(&v_of_kv, callback_for_each_vector_free);
    vector_free(&v_of_kv);
}

static void
btree_rebuild_with_pivot(ps_btree p_tree, ps_vector p_vector_of_kv, int index_min, int index_max) {
    ps_kv p_kv ;
    int sample_size = index_max - index_min + 1 ;
    int pivot = 0 ;

    if ( sample_size == 1 ) {
        p_kv = vector_element_at(p_vector_of_kv, index_min);
        btree_put(p_tree, p_kv->pv_key, p_kv->pv_value);
        
    } else if ( sample_size == 2 ) {
        p_kv = vector_element_at(p_vector_of_kv, index_max);
        btree_put(p_tree, p_kv->pv_key, p_kv->pv_value);

        p_kv = vector_element_at(p_vector_of_kv, index_min);
        btree_put(p_tree, p_kv->pv_key, p_kv->pv_value);
        
    } else {
        pivot = (int)sample_size / 2 ;

        p_kv = vector_element_at(p_vector_of_kv, index_min + pivot);
        btree_put(p_tree, p_kv->pv_key, p_kv->pv_value);

        btree_rebuild_with_pivot(p_tree, p_vector_of_kv, index_min, index_min + pivot - 1);
        btree_rebuild_with_pivot(p_tree, p_vector_of_kv, index_min + pivot + 1, index_max);       
    }    
}

void    btree_check_integrity(ps_btree                     p_tree,
                              ps_tree_node                 p_node,
                              p_func_key_to_string_psz     pf_key_string,
                              p_func_value_to_string_psz   pf_value_string) {
    char    buf_to_print[128];
    char    buf_tmp[64];    
    
    l_strlcpy(buf_to_print, "node k:", sizeof(buf_to_print));
    
    if ( p_node->pv_key != NULL ) {
        // err 1
        memset(buf_tmp, 0, sizeof(buf_tmp));
        pf_key_string(p_node->pv_key, buf_tmp);
        l_strlcat(buf_to_print, buf_tmp, sizeof(buf_to_print));
    } else {
        l_strlcat(buf_to_print, "error:null", sizeof(buf_to_print));
    }
    
    l_strlcat(buf_to_print, " v:", sizeof(buf_to_print));
    if ( p_node->pv_value != NULL ) {
        // err 2
        memset(buf_tmp, 0, sizeof(buf_tmp));
        pf_value_string(p_node->pv_value, buf_tmp);
        l_strlcat(buf_to_print, buf_tmp, sizeof(buf_to_print));
    } else {
        l_strlcat(buf_to_print, "error:null", sizeof(buf_to_print));
    }

    l_strlcat(buf_to_print, " parent:", sizeof(buf_to_print));    
    if ( p_node->p_node_parent != NULL ) {
        if ( p_node->p_node_parent->p_node_left == p_node ) {
            l_strlcat(buf_to_print, "left ", sizeof(buf_to_print));            
        } else if ( p_node->p_node_parent->p_node_right == p_node ) {
            l_strlcat(buf_to_print, "right ", sizeof(buf_to_print));            
        } else {
            // err 3
            l_strlcat(buf_to_print, "error:link ", sizeof(buf_to_print));            
        }
    } else {
        if ( p_node != p_tree->p_node_root ) {
            // err 4
            l_strlcat(buf_to_print, "error:null ", sizeof(buf_to_print));
        } else {
            l_strlcat(buf_to_print, "root ", sizeof(buf_to_print));            
        }
    }

    printf("%s\n",buf_to_print);
    
    if ( p_node->p_node_left != NULL ) {
        btree_check_integrity(p_tree, p_node->p_node_left, pf_key_string, pf_value_string);
    }

    if ( p_node->p_node_right != NULL ) {
        btree_check_integrity(p_tree, p_node->p_node_right, pf_key_string, pf_value_string);
    }    
}

/* 
 * static utilities
 */
static ps_tree_node
node_alloc_init(ps_tree_node p_parent, void* pv_key, void* pv_value) {
    ps_tree_node p_new_node = NULL ;
    p_new_node = calloc(1,sizeof(s_tree_node)) ;
    p_new_node->p_node_parent = p_parent;
    p_new_node->pv_key = pv_key ;
    p_new_node->pv_value = pv_value ;
    return p_new_node ;
}

static ps_tree_node
btree_search_parent(ps_btree p_tree, ps_tree_node p_node, void* pv_key) {
    int i_cmp = p_tree->pf_comp(pv_key, p_node->pv_key) ;
    if ( i_cmp < 0 ) {
        if ( p_node->p_node_left == NULL ) {
            return p_node ;
        }
        return btree_search_parent(p_tree, p_node->p_node_left, pv_key) ;
    } else if ( i_cmp > 0 ) {
        if ( p_node->p_node_right == NULL ) {
            return p_node ;
        }
        return btree_search_parent(p_tree, p_node->p_node_right, pv_key) ;
    } else {
        return p_node ;
    }
}

static ps_tree_node
btree_search_key(ps_btree p_tree, ps_tree_node p_node, void* pv_key) {
    int i_cmp = p_tree->pf_comp(pv_key, p_node->pv_key) ;

    if ( i_cmp < 0 && p_node->p_node_left != NULL ) {
        return btree_search_key(p_tree, p_node->p_node_left, pv_key) ;
        
    } else if ( i_cmp > 0 && p_node->p_node_right != NULL ) {
        return btree_search_key(p_tree, p_node->p_node_right, pv_key) ;

    } else if ( i_cmp == 0 ) {
        return p_node ;
    }
    return NULL ;
    
}

static void
btree_node_free(ps_tree_node p_node) {
    if ( p_node->p_node_left != NULL ) {
        btree_node_free(p_node->p_node_left);
    }

    if ( p_node->p_node_right != NULL ) {
        btree_node_free(p_node->p_node_right);
    }

    free(p_node);
}

static void
btree_node_foreach_infix(ps_btree p_tree, ps_tree_node p_node, p_func_btree_for_each pf_func) {
    if ( p_node == NULL ) {
        return ;
    }
    btree_node_foreach_infix(p_tree, p_node->p_node_left, pf_func);
    pf_func(p_node->pv_key, p_node->pv_value);
    btree_node_foreach_infix(p_tree, p_node->p_node_right, pf_func);
}

static void
btree_node_foreach_prefix(ps_btree p_tree, ps_tree_node p_node, p_func_btree_for_each pf_func) {
    if ( p_node == NULL ) {
        return ;
    }
    pf_func(p_node->pv_key, p_node->pv_value);
    btree_node_foreach_prefix(p_tree, p_node->p_node_left, pf_func);
    btree_node_foreach_prefix(p_tree, p_node->p_node_right, pf_func);
}

static void
btree_node_foreach_postfix(ps_btree p_tree, ps_tree_node p_node, p_func_btree_for_each pf_func) {
    if ( p_node == NULL ) {
        return ;
    }
    btree_node_foreach_postfix(p_tree, p_node->p_node_right, pf_func);
    pf_func(p_node->pv_key, p_node->pv_value);
    btree_node_foreach_postfix(p_tree, p_node->p_node_left, pf_func);
}

static void    btree_node_foreach_infix_with_parameter(ps_btree                                 p_tree,
                                                       ps_tree_node                             p_node,
                                                       p_func_btree_for_each_with_parameters    pf_func,
                                                       const void*                              pv_param1,
                                                       void*                                    pv_param2) {
    if ( p_node == NULL ) {
        return ;
    }
    btree_node_foreach_infix_with_parameter(p_tree, p_node->p_node_left, pf_func, pv_param1, pv_param2);
    pf_func(p_node->pv_key, p_node->pv_value, pv_param1, pv_param2);
    btree_node_foreach_infix_with_parameter(p_tree, p_node->p_node_right, pf_func, pv_param1, pv_param2);
}

static void    btree_node_foreach_prefix_with_parameter(ps_btree                                p_tree,
                                                        ps_tree_node                            p_node,
                                                        p_func_btree_for_each_with_parameters   pf_func,
                                                        const void*                             pv_param1,
                                                        void*                                   pv_param2) {
    if ( p_node == NULL ) {
        return ;
    }
    pf_func(p_node->pv_key, p_node->pv_value, pv_param1, pv_param2);
    btree_node_foreach_prefix_with_parameter(p_tree, p_node->p_node_left, pf_func, pv_param1, pv_param2);
    btree_node_foreach_prefix_with_parameter(p_tree, p_node->p_node_right, pf_func, pv_param1, pv_param2);
}

static void    btree_node_foreach_postfix_with_parameter(ps_btree                               p_tree,
                                                         ps_tree_node                           p_node,
                                                         p_func_btree_for_each_with_parameters  pf_func,
                                                         const void*                            pv_param1,
                                                         void*                                  pv_param2) {
    if ( p_node == NULL ) {
        return ;
    }
    btree_node_foreach_postfix_with_parameter(p_tree, p_node->p_node_right, pf_func, pv_param1, pv_param2);
    pf_func(p_node->pv_key, p_node->pv_value, pv_param1, pv_param2);
    btree_node_foreach_postfix_with_parameter(p_tree, p_node->p_node_left, pf_func, pv_param1, pv_param2);
}
