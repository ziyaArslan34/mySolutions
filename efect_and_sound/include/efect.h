#ifndef _EFECT_H_
#define _EFECT_H_

#define COL ((64/2) - 12)
#define ROW 10

#include <stdint.h>

uint8_t  my_rand(uint8_t, uint8_t);
void     set(uint8_t[][COL]);
void     print(const uint8_t[][COL]);
void*    play_efect(void*);

#endif /* efect.h */
