# Simple OCR Makefile

CC = gcc
CPPFLAGS= 
CFLAGS= -Wall -Werror -Wextra -std=c99 
LDFLAGS=
LDLIBS=  -lm

# Place in SRC all the files we want to build separated by a space
SRC= main.c 
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all: xor

main : main.o

clean:
	${RM} ${OBJ} # remove object files
	${RM} ${DEP} # remove dependency files
	${RM} main # remove main program


# include dependency files
-include ${DEP}

# END
