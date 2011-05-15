gpodflags = `pkg-config --cflags libgpod-1.0`
tagflags = `pkg-config --cflags taglib_c`
gpodlib= `pkg-config --libs libgpod-1.0`
taglib = `pkg-config --libs taglib_c`
libflags = $(gpodlib) $(taglib)
incflags = $(gpodflags) $(tagflags)
CFLAGS = -Wall -Wstrict-prototypes
CC = gcc

cpod : cpod.o db.o
	@echo linking: cpod.c -> cpod
	@$(CC) $(CFLAGS) $(libflags) -o cpod cpod.o db.o

cpod.o : cpod.c cpod.h db.h
	@echo compiling: cpod.c -> cpod.o
	@$(CC) $(CFLAGS) $(incflags) -c cpod.c

db.o : db.c db.h
	@echo compiling: db.c -> db.o
	@$(CC) $(CFLAGS) $(incflags) -c db.c

clean:
	@echo "cleaning..."
	@rm cpod.o db.o cpod
	@echo "done."
