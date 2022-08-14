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

#define FG_BLACK        0x0001
#define FG_RED          0x0002
#define FG_GREEN        0x0003
#define FG_YELLOW       0x0004
#define FG_BLUE         0x0005
#define FG_MAGENTA      0x0006
#define FG_CYAN         0x0007
#define FG_WHITE        0x0008

#define BG_BLACK        0x0010
#define BG_RED          0x0020
#define BG_GREEN        0x0030
#define BG_YELLOW       0x0040
#define BG_BLUE         0x0050
#define BG_MAGENTA      0x0060
#define BG_CYAN         0x0070
#define BG_WHITE        0x0080

#define RESET           0x0100
#define BOLD            0x0200
#define UNDERLINE       0x0300
#define INVERSE         0x0400

#define BOLD_OFF        0x0200
#define UNDERLINE_OFF   0x0300
#define INVERSE_OFF     0x0400

void color_print(unsigned int color, const char* fmt, ...);
void color_set(unsigned int color);
void color_reset(void);


#endif /* __BUFFER_H__ */
