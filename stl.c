#include "stl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

#include <vector.h>

void    read_stl(const char* filename, ps_stl p_stl) {
    FILE* h = NULL ;
    
    h = fopen(filename,"rb");
    if ( h != NULL ) {
        fread(p_stl->header.header, sizeof(char), STL_BINARY_HEADER_SIZE, h);
        p_stl->header.header[STL_BINARY_HEADER_SIZE] = '\0' ;

        fread(&(p_stl->number_of_triangles), sizeof(uint32_t), 1, h);
        vector_init(&(p_stl->vector_of_triangles), p_stl->number_of_triangles);
        for(uint32_t i=0; i<p_stl->number_of_triangles; i++) {
            ps_stl_triangle p_triangle = calloc(1, sizeof(s_stl_triangle));
            fread(p_triangle, SIZEOF_TRIANGLE, 1, h);
            vector_add_element(&(p_stl->vector_of_triangles), p_triangle);
        }
        fclose(h);
    }
}

void    free_stl(ps_stl p_stl) {
    vector_free(&p_stl->vector_of_triangles);
}

void    dump_stl(ps_stl p_stl) {
    printf("header : [%s]\n",p_stl->header.header);
    printf("number of triangles : %d\n",p_stl->number_of_triangles);
    for(uint32_t i=0; i<p_stl->number_of_triangles; i++) {
        printf("triangle %d\n",i);
        ps_stl_triangle p_triangle = vector_element_at(&(p_stl->vector_of_triangles), i);
        printf("    [%f,%f,%f]\n",p_triangle->p1.x,p_triangle->p1.y,p_triangle->p1.z);
        printf("    [%f,%f,%f]\n",p_triangle->p2.x,p_triangle->p2.y,p_triangle->p2.z);
        printf("    [%f,%f,%f]\n",p_triangle->p3.x,p_triangle->p3.y,p_triangle->p3.z);
    }
}

void    export_to_stl_text(ps_stl p_stl, const char *filename) {
    FILE* h = NULL ;

    printf("export to %s\n",filename);
    h = fopen(filename,"w");
    if ( h != NULL ) {
        fprintf(h,"solid Export from stl-2-polyhedron\n");
        for(uint32_t i=0; i<p_stl->number_of_triangles; i++) {
            ps_stl_triangle p_triangle = vector_element_at(&(p_stl->vector_of_triangles), i);
            fprintf(h,"facet normal %f %f %f\n",p_triangle->normal_vector.x,p_triangle->normal_vector.y,p_triangle->normal_vector.z);
            fprintf(h,"outer loop\n");
            fprintf(h,"vertex %f %f %f\n",p_triangle->p1.x,p_triangle->p1.y,p_triangle->p1.z);
            fprintf(h,"vertex %f %f %f\n",p_triangle->p2.x,p_triangle->p2.y,p_triangle->p2.z);
            fprintf(h,"vertex %f %f %f\n",p_triangle->p3.x,p_triangle->p3.y,p_triangle->p3.z);
            fprintf(h,"endloop\n");
            fprintf(h,"endfacet\n");
        }
        fprintf(h,"endsolid Export from stl-2-polyhedron\n");        
        fclose(h);
    }    
}

void    export_to_openscad_polyhedron(ps_stl p_stl, const char *filename) {
    FILE* h = NULL ;
    
    printf("export to %s\n",filename);
    h = fopen(filename,"w");
    if ( h != NULL ) {
        fprintf(h,"$fn=100;\n");
        fprintf(h,"\n");
        fprintf(h,"points = [ \n");
        for(uint32_t i=0; i<p_stl->number_of_triangles; i++) {
            ps_stl_triangle p_triangle = vector_element_at(&(p_stl->vector_of_triangles), i);
            fprintf(h,"          [%f,%f,%f],[%f,%f,%f],[%f,%f,%f]",p_triangle->p1.x,p_triangle->p1.y,p_triangle->p1.z,
                   p_triangle->p2.x,p_triangle->p2.y,p_triangle->p2.z,
                   p_triangle->p3.x,p_triangle->p3.y,p_triangle->p3.z);
            if ( i < p_stl->number_of_triangles-1 ) {
                fprintf(h,",\n");
            } else {
                fprintf(h,"\n");
            }
        }    
        fprintf(h,"         ];\n");
        fprintf(h,"\n");
        fprintf(h,"faces = [ \n");
        for(uint32_t i=0; i<p_stl->number_of_triangles*3; i+=3) {
            fprintf(h,"         [%d,%d,%d]",i,i+1,i+2);
            if ( i < (3*p_stl->number_of_triangles-3) ) {
                fprintf(h,",\n");
            } else {
                fprintf(h,"\n");
            }
        }
        fprintf(h,"        ]; \n");
        fprintf(h,"\n");
        fprintf(h,"polyhedron(points, faces);\n");
        fclose(h);
    }
}

void    export_to_stl_binary(ps_stl p_stl, const char *filename) {
    FILE* h = NULL ;
    h = fopen(filename,"wb");
    if ( h != NULL ) {
        fwrite(p_stl->header.header, sizeof(char), STL_BINARY_HEADER_SIZE, h);
        fwrite(&(p_stl->number_of_triangles), sizeof(uint32_t), 1, h);
        for(uint32_t i=0; i<p_stl->number_of_triangles; i++) {
            ps_stl_triangle p_triangle = vector_element_at(&(p_stl->vector_of_triangles), i);
            fwrite(p_triangle, SIZEOF_TRIANGLE, 1, h);
        }        
        fclose(h);
    }
}

void    stl_add(ps_stl p_stl_1, ps_stl p_stl_2, ps_stl p_stl_to) {
    
}
