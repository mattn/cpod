# libgpod and taglib_c
CFLAGS = `pkg-config --cflags libgpod-1.0 taglib_c`
LIBS = `pkg-config --libs libgpod-1.0 taglib_c`

CFLAGS  += -g -std=c99 -pedantic -Wall -Wstrict-prototypes ${INCS}
LDFLAGS += ${LIBS}
CC = cc

all: cpod

cpod: cpod.o db.o transfer.o util.o
	@echo "CC -o cpod cpod.o db.o"
	@${CC} ${LDFLAGS} -o cpod cpod.o db.o

cpod.o: cpod.c cpod.h db.h
	@echo "CC -c cpod.c"
	@${CC} ${CFLAGS} -c cpod.c

db.o: db.c db.h
	@echo "CC -c db.c"
	@${CC} ${CFLAGS} -c db.c

util.o: util.c util.h
	@echo "CC -c util.c"
	@${CC} ${CFLAGS} -c util.c

transfer.o: transfer.c transfer.h
	@echo "CC -c util.c"
	@${CC} ${CFLAGS} -c transfer.c


clean:
	@echo "cleaning"
	@rm *.o cpod
