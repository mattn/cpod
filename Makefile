# libgpod and taglib_c
CFLAGS = `pkg-config --cflags libgpod-1.0 taglib_c`
LIBS = `pkg-config --libs libgpod-1.0 taglib_c`

CFLAGS  += -g -std=c99 -Wall -Wstrict-prototypes ${INCS}
LDFLAGS += ${LIBS}
CC = clang

all: cpod-cp cpod-ls

cpod-ls: cpod-ls.o db.o util.o
	@echo "CC -o cpod-ls"
	@${CC} ${LDFLAGS} -o cpod-ls cpod-ls.o db.o util.o

cpod-ls.o: cpod-ls.c db.h util.h
	@echo "CC -c cpod-ls.c"
	@${CC} ${CFLAGS} -c cpod-ls.c

cpod-cp: cpod-cp.o db.o util.o
	@echo "CC -o cpod-cp"
	@${CC} ${LDFLAGS} -o cpod-cp cpod-cp.o db.o util.o

cpod-cp.o: cpod-cp.c db.h util.h
	@echo "CC -c cpod-cp.c"
	@${CC} ${CFLAGS} -c cpod-cp.c

db.o: db.c db.h
	@echo "CC -c db.c"
	@${CC} ${CFLAGS} -c db.c

util.o: util.c util.h
	@echo "CC -c util.c"
	@${CC} ${CFLAGS} -c util.c

clean:
	@echo "cleaning"
	@rm *.o cpod-cp
