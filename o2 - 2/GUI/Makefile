# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags --libs gtk+-3.0` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -g
LDFLAGS=
LDLIBS=  -lSDL2 -lm -lSDL2_image `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

#-lhunspell

all: GUI

SRC = GUI.c treatmentGUI.c ../network/NeuralNetwork.c ../matrix.c ../treatment.c ../network/xortools.c ../detection.c ../bitmap.c ../ocr.c ../queue.c

#network/learning.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}



GUI: ${OBJ}

-include ${DEP}

clean:
	${RM} *.o
	${RM} *.d
	${RM} display
	${RM} main

# END
