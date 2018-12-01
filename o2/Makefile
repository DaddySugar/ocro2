# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` `pkg-config --cflags --libs gtk+-3.0` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -g -O2
LDFLAGS=
LDLIBS=  -lSDL2 -lm 

SRC = main.c treatment.c detection.c bitmap.c queue.c network/network.c network/xortools.c network/learning.c GUI/GUI.c GUI/treatmentGUI.c
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
