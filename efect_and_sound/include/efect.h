#ifndef _EFECT_H_
#define _EFECT_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/*
static int get_width(void) {
	FILE *F = popen("tput cols", "r");
	char ln[5];
	fgets(ln, 5, F);
	pclose(F);
	return atoi(ln);
}
*/ // get device width

#define ROW (10)
#define COL (60)
#define MILLISECOND (400000)

uint8_t  my_rand(uint8_t, uint8_t);
void     set(uint8_t[][COL]);
void     print(const uint8_t[][COL]);
void*    play_efect(void*);

#endif /* efect.h */
