# Makefile for building myio
CC= gcc -std=gnu99
CFLAGS= -Wall -Wextra
LDFLAGS= $(MYLDFLAGS)
LIBS= $(MYLIBS)

MYLDFLAGS=
MYLIBS=

AR= ar rcu
RANLIB= ranlib
RM= rm -f


MYIO_A= libmyio.a
BASE_O=  numberio.o strio.o

# Target starts here.
a: $(MYIO_A)

$(MYIO_A): $(BASE_O)
	$(AR) $@ $(BASE_O)
	$(RANLIB) $@

echo:
	@echo "CC= $(CC)"
	@echo "CFLAGS= $(CFLAGS)"
	@echo "LDFLAGS= $(LDFLAGS)"
	@echo "LIBS= $(LIBS)"
	@echo "AR= $(AR)"
	@echo "RANLIB= $(RANLIB)"
	@echo "RM= $(RM)"

clean:
	$(RM) $(MYIO_A) $(BASE_O)

.PHONY: a echo clean

numberio.o: numberio.c numberio.h
strio.o: strio.c strio.h
