CC                 = gcc
CFLAGS             = -lpulse -lpulse-simple -lmad -lpthread --pedantic-errors
PATH_HEADER_C      = src/efect.c
PATH_HEADER_H      = src/song.c
PATH_MAIN_C        = main.c

all:
	${CC} ${CFLAGS} ${PATH_MAIN_C} ${PATH_HEADER_C} ${PATH_HEADER_H}
