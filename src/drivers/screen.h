#ifndef INOS_SCREEN_H
#define INOS_SCREEN_H

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
// Attribute byte for our default colour scheme .
#define WHITE_ON_BLACK 0x0f
#define RED_ON_WHITE 0xf4
// Screen device I/O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

void print(char* message);
void print_at(char* message, int col, int row);
void clear_screen();
void println(char *message);

#endif
