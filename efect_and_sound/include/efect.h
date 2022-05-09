#ifndef _EFECT_H_
#define _EFECT_H_

#include <stdint.h>
#include <stddef.h>

#define MILLISECOND (400000)
#define NORMAL           "\x1B[0m"
#define GRAY             "\x1B[30m"
#define BLUE             "\x1B[34m"
#define MAGENTA          "\x1B[35m"
#define CYAN             "\x1B[36m"
#define YELLOW           "\x1B[33m"
#define WHITE            "\x1B[37m"
#define GREEN            "\x1B[32m"
#define RED              "\x1B[31m"

uint8_t  my_rand(uint8_t, uint8_t);
void     set(uint8_t **, size_t, size_t);
void     print(uint8_t **, size_t, size_t, uint8_t);
void*    play_efect(void*);

#endif /* efect.h */
