#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tests.h"

void    test_list_data_sorted(void) {
    s_data_cell    cells[] = {
        { 5 , "123456" } ,
        { 8 , "12345" } ,
        { 6 , "123456789" } ,
        { 9 , "password" } ,
        { 2 , "iloveyou" } ,
        { 10 , "princess" } ,
        { 1 , "1234567" } ,
        { 4 , "rockyou" } ,
        { 3 , "12345678" } ,
        { 7 , "abc123" }
    } ;

    s_list    list_of_cells;

    list_init(&list_of_cells, true, list_data_cell_compare);

    int nb_elems = sizeof(cells) / sizeof(s_data_cell) ;
    for(int i=0;i<nb_elems;i++) {
        list_add(&list_of_cells, &cells[i]);
        // fprintf(stderr,"\n");
        // debug_list(&list_of_strings);
    }
    printf("list_for_each_with_limit 20/10\n");
    list_for_each_with_limit(&list_of_cells, list_data_cell_dump_with_index, 40);

    list_free(&list_of_cells);
}

void    test_list_copy(void) {
    s_data_cell    cells[] = {
        { 5 , "123456" } ,
        { 8 , "12345" } ,
        { 6 , "123456789" } ,
        { 9 , "password" } ,
        { 2 , "iloveyou" } ,
        { 10 , "princess" } ,
        { 1 , "1234567" } ,
        { 4 , "rockyou" } ,
        { 3 , "12345678" } ,
        { 7 , "abc123" }
    } ;

    s_list    list_of_cells;
    s_list    l_copy ;
    s_vector  to_vector;

    list_init(&list_of_cells, true, list_data_cell_compare);

    int nb_elems = sizeof(cells) / sizeof(s_data_cell) ;
    for(int i=0;i<nb_elems;i++) {
        list_add(&list_of_cells, &cells[i]);
        // fprintf(stderr,"\n");
        // debug_list(&list_of_strings);
    }

    list_copy(&list_of_cells, &l_copy) ;

    list_to_vector(&list_of_cells, &to_vector);

    printf("list_for_each list_of_cell\n");
    list_for_each_with_limit(&list_of_cells, list_data_cell_dump_with_index, 40);

    printf("list_for_each list_copy\n");
    list_for_each_with_limit(&l_copy, list_data_cell_dump_with_index, 40);

    printf("vector_for_each to_vector\n");
    vector_for_each(&to_vector, vector_cell_dump);

    list_free(&list_of_cells);
    list_free(&l_copy);
    vector_free(&to_vector);
}

void    test_list_sorted(void) {
    char*    words[] = {
        "123456",        /* 00 */
        "12345",         /* 01 */
        "123456789",     /* 02 */
        "password",      /* 03 */
        "iloveyou",      /* 04 */
        "princess",      /* 05 */
        "1234567",       /* 06 */
        "rockyou",       /* 07 */
        "12345678",      /* 08 */
        "abc123",        /* 09 */
        "nicole",        /* 10 */ // remove_at 10
        "daniel",        /* 11 */
        "babygirl",      /* 12 */
        "monkey",        /* 13 */
        "lovely",        /* 14 */
        "jessica",       /* 15 */
        "654321",        /* 16 */
        "michael",       /* 17 */
        "ashley",        /* 18 */
        "qwerty",        /* 19 */
        "111111",        /* 20 */
        "iloveu",        /* 21 */
        "000000",        /* 22 */
        "michelle",      /* 23 */
        "tigger",        /* 24 */
        "sunshine",      /* 25 */
        "chocolate",     /* 26 */
        "password1",     /* 27 */
        "soccer",        /* 28 */
        "anthony"        /* 29 */
    };
    s_list    list_of_strings;

    list_init(&list_of_strings, true, list_string_compare);

    int nb_elems = sizeof(words) / sizeof(char*) ;
    for(int i=0;i<nb_elems;i++) {
        list_add(&list_of_strings, words[i]);
        fprintf(stderr,"\n");
        debug_list(&list_of_strings);
    }
    printf("list_for_each_with_limit 20/10\n");
    list_for_each_with_limit(&list_of_strings, list_string_dump_with_index, 40);

    list_free(&list_of_strings);
}



void    test_list_bounds(void) {
    char*    words[] = {
        "123456",        /* 00 */
        "12345",         /* 01 */
        "123456789",     /* 02 */
        "password",      /* 03 */
        "iloveyou",      /* 04 */
        "princess",      /* 05 */
        "1234567",       /* 06 */
        "rockyou",       /* 07 */
        "12345678",      /* 08 */
        "abc123",        /* 09 */
        "nicole"         /* 10 */ // remove_at 10
    } ;

    s_list    list_of_strings;

    list_init(&list_of_strings, false, NULL);

    int nb_elems = sizeof(words) / sizeof(char*) ;
    for(int i=0;i<nb_elems;i++) {
        list_add(&list_of_strings, words[i]);
    }

    printf("list_for_each\n");
    list_for_each(&list_of_strings, list_string_dump);

    printf("list_for_each_with_limit 20/10\n");
    list_for_each_with_limit(&list_of_strings, list_string_dump_with_index, 20);

    printf("list_get_at 20\n");
    char* psz = (char*)list_get_at(&list_of_strings, 20);
    if ( psz != NULL ) {
        printf("\t%s\n",psz);
    } else {
        printf("\tnot found\n");
    }

    printf("list_get_element soccer\n");
    psz = list_get_element(&list_of_strings, "soccer", list_string_compare);
    if ( psz != NULL ) {
        printf("\t%s\n",psz);
    } else {
        printf("\tnot found\n");
    }

    printf("list_remove_element monkey\n");
    list_remove_element(&list_of_strings, "monkey", list_string_compare);
    list_for_each(&list_of_strings, list_string_dump);

    printf("list_remove_at 20\n");
    list_remove_at(&list_of_strings, 20);
    list_for_each(&list_of_strings, list_string_dump);

    list_free(&list_of_strings);
}

void    test_list_remove_bounds_1(void) {
    char*    words[] = {
        "password",      /* 00 */
        "rockyou",       /* 01 */
        "nicole"         /* 02 */
    } ;

    s_list    list_of_strings;

    list_init(&list_of_strings, false, NULL);

    int nb_elems = sizeof(words) / sizeof(char*) ;
    for(int i=0;i<nb_elems;i++) {
        list_add(&list_of_strings, words[i]);
    }

    printf("list_for_each\n");
    list_for_each(&list_of_strings, list_string_dump);

    printf("list_remove_element nicole\n");
    list_remove_element(&list_of_strings, "nicole", list_string_compare);
    list_for_each(&list_of_strings, list_string_dump);

    printf("list_remove_element password\n");
    list_remove_element(&list_of_strings, "password", list_string_compare);
    list_for_each(&list_of_strings, list_string_dump);

    printf("list_remove_element rockyou\n");
    list_remove_element(&list_of_strings, "rockyou", list_string_compare);
    list_for_each(&list_of_strings, list_string_dump);

    list_free(&list_of_strings);
}

void    test_list_remove_bounds_2(void) {
    char*    words[] = {
        "password",      /* 00 */
        "rockyou",       /* 01 */
        "nicole"         /* 02 */
    } ;

    s_list    list_of_strings;

    list_init(&list_of_strings, false, NULL);

    int nb_elems = sizeof(words) / sizeof(char*) ;
    for(int i=0;i<nb_elems;i++) {
        list_add(&list_of_strings, words[i]);
    }

    printf("list_for_each\n");
    list_for_each(&list_of_strings, list_string_dump);

    printf("list_remove_element nicole\n");
    list_remove_element(&list_of_strings, "nicole", list_string_compare);
    list_for_each(&list_of_strings, list_string_dump);

    printf("list_remove_element rockyou\n");
    list_remove_element(&list_of_strings, "rockyou", list_string_compare);
    list_for_each(&list_of_strings, list_string_dump);

    printf("list_remove_element password\n");
    list_remove_element(&list_of_strings, "password", list_string_compare);
    list_for_each(&list_of_strings, list_string_dump);

    list_free(&list_of_strings);
}

void    test_list_remove_bounds_3(void) {
    char*    words[] = {
        "password",      /* 00 */
        "rockyou",       /* 01 */
        "nicole"         /* 02 */
    } ;

    s_list    list_of_strings;

    list_init(&list_of_strings, false, NULL);

    int nb_elems = sizeof(words) / sizeof(char*) ;
    for(int i=0;i<nb_elems;i++) {
        list_add(&list_of_strings, words[i]);
    }

    printf("list_for_each\n");
    list_for_each(&list_of_strings, list_string_dump);

    printf("list_remove_element rockyou\n");
    list_remove_element(&list_of_strings, "rockyou", list_string_compare);
    list_for_each(&list_of_strings, list_string_dump);

    printf("list_remove_element nicole\n");
    list_remove_element(&list_of_strings, "nicole", list_string_compare);
    list_for_each(&list_of_strings, list_string_dump);

    printf("list_remove_element password\n");
    list_remove_element(&list_of_strings, "password", list_string_compare);
    list_for_each(&list_of_strings, list_string_dump);

    list_free(&list_of_strings);
}

void    test_list_remove_bounds_4(void) {
    char*    words[] = {
        "password",      /* 00 */
        "rockyou",       /* 01 */
        "nicole"         /* 02 */
    } ;

    s_list    list_of_strings;

    list_init(&list_of_strings, false, NULL);

    int nb_elems = sizeof(words) / sizeof(char*) ;
    for(int i=0;i<nb_elems;i++) {
        list_add(&list_of_strings, words[i]);
    }

    printf("list_for_each\n");
    list_for_each(&list_of_strings, list_string_dump);

    printf("list_remove_element rockyou\n");
    list_remove_element(&list_of_strings, "rockyou", list_string_compare);
    list_for_each(&list_of_strings, list_string_dump);

    printf("list_remove_element password\n");
    list_remove_element(&list_of_strings, "password", list_string_compare);
    list_for_each(&list_of_strings, list_string_dump);
    
    printf("list_remove_element nicole\n");
    list_remove_element(&list_of_strings, "nicole", list_string_compare);
    list_for_each(&list_of_strings, list_string_dump);

    list_free(&list_of_strings);
}

void    test_list_remove_bounds_5(void) {
    char*    words[] = {
        "password",      /* 00 */
        "rockyou",       /* 01 */
        "nicole"         /* 02 */
    } ;

    s_list    list_of_strings;

    list_init(&list_of_strings, false, NULL);

    int nb_elems = sizeof(words) / sizeof(char*) ;
    for(int i=0;i<nb_elems;i++) {
        list_add(&list_of_strings, words[i]);
    }

    printf("list_for_each\n");
    list_for_each(&list_of_strings, list_string_dump);

    printf("list_remove_element password\n");
    list_remove_element(&list_of_strings, "password", list_string_compare);
    list_for_each(&list_of_strings, list_string_dump);

    printf("list_remove_element rockyou\n");
    list_remove_element(&list_of_strings, "rockyou", list_string_compare);
    list_for_each(&list_of_strings, list_string_dump);
    
    printf("list_remove_element nicole\n");
    list_remove_element(&list_of_strings, "nicole", list_string_compare);
    list_for_each(&list_of_strings, list_string_dump);

    list_free(&list_of_strings);
}

void    test_list_remove_bounds_6(void) {
    char*    words[] = {
        "password",      /* 00 */
        "rockyou",       /* 01 */
        "nicole"         /* 02 */
    } ;

    s_list    list_of_strings;

    list_init(&list_of_strings, false, NULL);

    int nb_elems = sizeof(words) / sizeof(char*) ;
    for(int i=0;i<nb_elems;i++) {
        list_add(&list_of_strings, words[i]);
    }

    printf("list_for_each\n");
    list_for_each(&list_of_strings, list_string_dump);

    printf("list_remove_element password\n");
    list_remove_element(&list_of_strings, "password", list_string_compare);
    list_for_each(&list_of_strings, list_string_dump);

    printf("list_remove_element nicole\n");
    list_remove_element(&list_of_strings, "nicole", list_string_compare);
    list_for_each(&list_of_strings, list_string_dump);

    printf("list_remove_element rockyou\n");
    list_remove_element(&list_of_strings, "rockyou", list_string_compare);
    list_for_each(&list_of_strings, list_string_dump);    

    list_free(&list_of_strings);
}

void     test_list(void) {
    char*    words[] = {
        "123456",        /* 00 */
        "12345",         /* 01 */
        "123456789",     /* 02 */
        "password",      /* 03 */
        "iloveyou",      /* 04 */
        "princess",      /* 05 */
        "1234567",       /* 06 */
        "rockyou",       /* 07 */
        "12345678",      /* 08 */
        "abc123",        /* 09 */
        "nicole",        /* 10 */ // remove_at 10
        "daniel",        /* 11 */
        "babygirl",      /* 12 */
        "monkey",        /* 13 */
        "lovely",        /* 14 */
        "jessica",       /* 15 */
        "654321",        /* 16 */
        "michael",       /* 17 */
        "ashley",        /* 18 */
        "qwerty",        /* 19 */
        "111111",        /* 20 */
        "iloveu",        /* 21 */
        "000000",        /* 22 */
        "michelle",      /* 23 */
        "tigger",        /* 24 */
        "sunshine",      /* 25 */
        "chocolate",     /* 26 */
        "password1",     /* 27 */
        "soccer",        /* 28 */
        "anthony"        /* 29 */
    };

    s_list    list_of_strings;

    list_init(&list_of_strings, false, NULL);

    int nb_elems = sizeof(words) / sizeof(char*) ;
    for(int i=0;i<nb_elems;i++) {
        list_add(&list_of_strings, words[i]);
    }

    printf("list_for_each\n");
    list_for_each(&list_of_strings, list_string_dump);

    printf("list_for_each_with_limit\n");
    list_for_each_with_limit(&list_of_strings, list_string_dump_with_index, 10);

    printf("list_get_at 10\n");
    char* psz = (char*)list_get_at(&list_of_strings, 10);
    if ( psz != NULL ) {
        printf("\t%s\n",psz);
    }

    printf("list_get_element soccer\n");
    psz = list_get_element(&list_of_strings, "soccer", list_string_compare);
    if ( psz != NULL ) {
        printf("\t%s\n",psz);
    }

    printf("list_remove_element monkey\n");
    list_remove_element(&list_of_strings, "monkey", list_string_compare);
    list_for_each(&list_of_strings, list_string_dump);

    printf("list_remove_at\n");
    list_remove_at(&list_of_strings, 10);
    list_for_each(&list_of_strings, list_string_dump);

    list_free(&list_of_strings);
}

void     list_buffer_free(const void* pv_data) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    free((void*)pv_data);
#pragma GCC diagnostic pop
}

void     list_buffer_dump(const void* pv_data) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    const ps_buffer p_buffer = (const ps_buffer)pv_data;
#pragma GCC diagnostic pop
    printf("\t[%.*s]\n",(int)p_buffer->offset, (char*)p_buffer->data);
}

void    test_list_read_lines(void) {
    char* line1 = "tag1:file1,file1,file3\n";
    char* line2 = "tag2:file4,file5,file5\n";
    char* line3 = "tag3:file7,file7\n";
    char* line4 = "tag4:file9\n";
    char* line5 = "tag5:file10,file11\n";
    char* line6 = "tag6:file12,file13,file14\n";
    char* line7 = "tag7:lastline";

    s_list list_lines;
    s_buffer buf_file;

    printf("test_list_read_lines\n");

    list_init(&list_lines,false,NULL);
    buffer_init(&buf_file, 1024);

    buffer_append(&buf_file, line1, strlen(line1));
    buffer_append(&buf_file, line2, strlen(line2));
    buffer_append(&buf_file, line3, strlen(line3));
    buffer_append(&buf_file, line4, strlen(line4));
    buffer_append(&buf_file, line5, strlen(line5));
    buffer_append(&buf_file, line6, strlen(line6));
    buffer_append(&buf_file, line7, strlen(line7));

    file_buffer_lines_to_list(&buf_file, &list_lines);
    list_for_each(&list_lines, list_buffer_dump);
    
    list_for_each(&list_lines, list_buffer_free);
    buffer_free(&buf_file);
    list_free(&list_lines);
}
