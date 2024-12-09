CC       := gcc
CFLAGS   := -Wall
SRC      := ./src
INCLUDE  := ./include
OBJFILES := main.o navire.o quai.o port.o utils.o lettre.o textureLoader.o
TARGET   := main

all : ${TARGET} clean

${TARGET}: ${OBJFILES}
	${CC} ${CFLAGS} ${OBJFILES} -o ${TARGET} ./GfxLib/libisentlib.a -lm -lglut -lGL -lX11

main.o : ${SRC}/main.c
	${CC} ${CFLAGS} -c ${SRC}/main.c

navire.o : ${SRC}/main.c
	${CC} ${CFLAGS} -c ${SRC}/navire.c

quai.o : ${SRC}/main.c
	${CC} ${CFLAGS} -c ${SRC}/quai.c

port.o : ${SRC}/main.c
	${CC} ${CFLAGS} -c ${SRC}/port.c

utils.o : ${SRC}/main.c
	${CC} ${CFLAGS} -c ${SRC}/utils.c

lettre.o : ${SRC}/main.c
	${CC} ${CFLAGS} -c ${SRC}/lettre.c

textureLoader.o : ${SRC}/main.c
	${CC} ${CFLAGS} -c ${SRC}/textureLoader.c

clean :
	rm -f *~ *.o