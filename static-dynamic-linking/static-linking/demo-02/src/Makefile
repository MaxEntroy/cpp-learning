ROOT= ..

CC= gcc -std=gnu99
CFLAGS= -Wall -Wextra $(SYSCFLAGS) $(MYCFLAGS)
LDFLAGS= $(SYSLDFLAGS) $(MYLDFLAGS)
LIBS= $(SYSLIBS) $(MYLIBS)

AR= ar rcu
RANLIB= ranlib
RM= rm -f

SYSCFLAGS=
SYSLDFLAGS=
SYSLIBS=

MYCFLAGS= -I$(ROOT)/thirdparty/myio
MYLDFLAGS= -L$(ROOT)/thirdparty/myio/lib
MYLIBS=-lmyio

# End of user setting.
MAIN_A= libmain.a
BASE_O= student.o

MAIN_T= main
MAIN_O= main.o

# Targets start here
t: $(MAIN_T)

$(MAIN_A): $(BASE_O)
	$(AR) -o $@ $(BASE_O)
	$(RANLIB) $@

$(MAIN_T): $(MAIN_O) $(MAIN_A)
	$(CC) -o $@ $(MAIN_O) $(MAIN_A) $(LIBS)

clean:
	$(RM) $(MAIN_T) $(MAIN_A) $(MAIN_O) $(BASE_O)

.PHONY: clean t

main.o: main.c student.h
student.o: student.c student.h
