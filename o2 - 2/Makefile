# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -g 
LDFLAGS=
LDLIBS=  -lSDL2 -lm -lSDL2_image 

#-lhunspell

SRC = main.c treatment.c detection.c bitmap.c queue.c network/NeuralNetwork.c matrix.c learning.c ocr.c network/xortools.c 

#network/learning.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: main

main: ${OBJ}

-include ${DEP}

clean:
	${RM} *.o
	${RM} *.d
	${RM} display
	${RM} main

# END
