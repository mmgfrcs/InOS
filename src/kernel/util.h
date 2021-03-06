#ifndef INOS_UTIL_H
#define INOS_UTIL_H

#include "../cpu/x86/types.h"

void mcopy(char* source, char* dest, int no_bytes);
void mset(u8 *dest, u8 val, u32 len);
void itoa(int n, char str[]);
void strrev(char s[]);
int strlen(char s[]);
#endif
