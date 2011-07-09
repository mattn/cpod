# libgpod and taglib_c
CFLAGS = `pkg-config --cflags libgpod-1.0 taglib_c`
LIBS = `pkg-config --libs libgpod-1.0 taglib_c`

CFLAGS  += -std=c99 -pedantic -Wall -Wstrict-prototypes ${INCS}
LDFLAGS += -s ${LIBS}
CC = cc

all: cpod

cpod: cpod.o db.o
	@echo "CC -o cpod cpod.o db.o"
	@${CC} ${LDFLAGS} -o cpod cpod.o db.o

cpod.o: cpod.c cpod.h db.h
	@echo "CC -c cpod.c"
	@${CC} ${CFLAGS} -c cpod.c

db.o: db.c db.h
	@echo "CC -c db.c"
	@${CC} ${CFLAGS} -c db.c

clean: cpod.o db.o cpod
	@echo "cleaning"
	@rm cpod.o db.o cpod
