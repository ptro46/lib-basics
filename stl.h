#ifndef __STL_H__
#define __STL_H__

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

#include <vector.h>

#define STL_BINARY_HEADER_SIZE     80
#define SIZEOF_TRIANGLE            50

struct stl_header {
    char     header[STL_BINARY_HEADER_SIZE + 1] ;
} ;
typedef struct stl_header     s_stl_header ;
typedef struct stl_header*    ps_stl_header ;

struct stl_3d_point {
    float    x;
    float    y;
    float    z;
} ;
typedef struct stl_3d_point     s_stl_3d_point ;
typedef struct stl_3d_point*    ps_stl_3d_point;

struct stl_triangle {
    s_stl_3d_point    normal_vector;
    s_stl_3d_point    p1 ;
    s_stl_3d_point    p2 ;
    s_stl_3d_point    p3 ;
    uint16_t        control_word;
} ;
typedef struct stl_triangle     s_stl_triangle ;
typedef struct stl_triangle*    ps_stl_triangle;

struct stl {
    s_stl_header    header;
    uint32_t        number_of_triangles ;
    s_vector        vector_of_triangles ;
} ;
typedef struct stl     s_stl  ;
typedef struct stl*    ps_stl ;


void    read_stl(const char* filename, ps_stl p_stl);
void    dump_stl(ps_stl p_stl);
void    export_to_stl_text(ps_stl p_stl, const char *filename);
void    export_to_openscad_polyhedron(ps_stl p_stl, const char *filename);

void    export_to_stl_binary(ps_stl p_stl, const char *filename);
void    stl_add(ps_stl p_stl_1, ps_stl p_stl_2, ps_stl p_stl_to);

#endif /* __STL_H__ */
