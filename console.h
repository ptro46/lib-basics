
/**
 * \file console.h
 * \brief function to interact with console outputs
 * \author Patrice Trognon
 * \version 1.0
 * \date 14 aout 2022
 */
#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <stdarg.h>
#include <stdlib.h>

#define FG_BLACK        0x00000001
#define FG_RED          0x00000002
#define FG_GREEN        0x00000004
#define FG_YELLOW       0x00000008
#define FG_BLUE         0x00000010
#define FG_MAGENTA      0x00000020
#define FG_CYAN         0x00000040
#define FG_WHITE        0x00000080

#define BG_BLACK        0x00000100
#define BG_RED          0x00000200
#define BG_GREEN        0x00000400
#define BG_YELLOW       0x00000800
#define BG_BLUE         0x00001000
#define BG_MAGENTA      0x00002000
#define BG_CYAN         0x00004000
#define BG_WHITE        0x00008000

#define RESET           0x00010000
#define BOLD            0x00020000
#define UNDERLINE       0x00040000
#define INVERSE         0x00080000

#define BOLD_OFF        0x00100000
#define UNDERLINE_OFF   0x00200000
#define INVERSE_OFF     0x00400000

void color_print(unsigned int color, const char* fmt, ...);
void color_set(unsigned int color);
void color_reset(void);


#endif /* __BUFFER_H__ */
