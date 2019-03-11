# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -std=c99 -O3
LDFLAGS=
LDLIBS=  -lSDL2 -lm

SRC = main.c network.c 
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: main

main: ${OBJ}

-include ${DEP}

clean:
	${RM} *.o
	${RM} *.d
	${RM} display
	${RM} grayscale

# END
