#ifndef _EFECT_H_
#define _EFECT_H_

#include <stdint.h>
#include <stddef.h>

#define MILLISECOND (400000)

uint8_t  my_rand(uint8_t, uint8_t);
void     set(uint8_t **, size_t, size_t);
void     print(uint8_t **, size_t, size_t, uint8_t);
void*    play_efect(void*);

#endif /* efect.h */
