# gobject
GOBJECT_INC = -pthread # not exactly an include but it belongs in CFLAGS
GOBJECT_LIB = -pthread -lgobject-2.0 -lgthread-2.0 -lrt
# glib
GLIB_INC = -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include
GLIB_LIB = -lglib-2.0
# gdk-pixbuf
GDK_PIXBUFINC = -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libpng14
GDK_PIXBUFLIB = -lgdk_pixbuf-2.0 -lpng14 -lm
# libgpod
GPODINC = -I/usr/include/gpod-1.0
GPODLIB = -lgpod
# taglib_c
TAGCINC = -I/usr/include/taglib
TAGCLIB = -ltag_c -ltag

INCS = ${TAGCINC} ${GPODINC} ${GOBJECT_INC} ${GLIB_INC} ${GDK_PIXBUFINC}
LIBS = ${TAGCLIB} ${GPODLIB} ${GOBJECT_LIB} ${GLIB_LIB} ${GDK_PIXBUFLIB}

CFLAGS  += -std=c99 -pedantic -Wall -Wstrict-prototypes ${INCS}
LDFLAGS += -s ${LIBS}
CC = cc

all: options cpod

options:
	@echo cpod build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

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
	@echo cleaning
	@rm cpod.o db.o cpod
