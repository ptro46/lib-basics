#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tests.h"

void     test_buffer(void) {
    char         s1[] = "012345678" ;
    char         s2[] = "90123456789" ;
    ps_buffer    p_buf;
    s_buffer     buf1;
    s_buffer     buf2;
    s_buffer     buf3;

    p_buf = buffer_alloc(10);
    buffer_dump( p_buf ) ;
    
    buffer_append(p_buf, s1, strlen(s1));
    buffer_dump( p_buf ) ;

    buffer_append(p_buf, s2, strlen(s2));
    buffer_dump( p_buf ) ;

    buffer_init(&buf1, 10);
    buffer_dump( &buf1 ) ;

    buffer_init(&buf2, 10);
    buffer_dump( &buf2 ) ;

    buffer_init(&buf3, 10);
    buffer_dump( &buf3 ) ;

    buffer_append_f(&buf1, "%s",s1);
    buffer_dump( &buf1 ) ;

    buffer_append_f(&buf2, "%s",s2);
    buffer_dump( &buf2 ) ;

    buffer_append_f(&buf3, "%s",s1);
    buffer_dump( &buf3 ) ;

    buffer_append_f(&buf3, "%s",s2);
    buffer_dump( &buf3 ) ;

    buffer_append_buffer(p_buf, &buf1);
    buffer_dump( p_buf ) ;
    
    buffer_free(p_buf);
    buffer_free(&buf1);
    buffer_free(&buf2);
    buffer_free(&buf3);
    free(p_buf);
}
