TARGET = main
HEADFILE = particle.h rnd.h SB.h v2d.h particleSystem.h

WORKDIR = %cd%

CC = gcc.exe
LD = gcc.exe
WINDRES = windres.exe

INC = -I$(MINGW_DEV_LIB)\include
CFLAGS = -O2 -Wall -std=c99 -m64

LIB = -L$(MINGW_DEV_LIB)\lib
LDFLAGS = -O2 -s -m64 -lmingw32 -lsdl3 -mwindows

${TARGET}: ${TARGET}.o
	${CC} ${TARGET}.o ${LIB} ${LDFLAGS} -o ${TARGET}

${TARGET}.o: ${TARGET}.c ${HEADFILE}
		${CC} -c ${TARGET}.c ${CFLAGS} ${INC}

clean: 
	cmd /c del /f *.o
