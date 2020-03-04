CC= gcc -std=c99
CFLAGS= -Wall -Wextra -g $(MYCFLAGS)
LDFLAGS= $(MYLDFLAGS)
LIBS= $(MYLIBS)

MYCFLAGS=
MYLDFLAGS=
MYLIBS=

AR= ar rcu
RANLIB= ranlib
RM= rm -rf

MAIN_A= libmain.a
BASE_O= cal.o

MAIN_T= main
MAIN_O= main.o

# Targets start here
a: $(MAIN_A)

t: $(MAIN_T)

$(MAIN_A): $(BASE_O)
	$(AR) $@ $(BASE_O)
	$(RANLIB) $@

$(MAIN_T): $(MAIN_O) $(MAIN_A)
	$(CC) -o $@ $(LDFLAGS) $(MAIN_O) $(MAIN_A) $(LIBS)

echo:
	@echo "CC= $(CC)"
	@echo "CFLAGS= $(CFLAGS)"
	@echo "LDFLAGS= $(LDFLAGS)"
	@echo "LIBS= $(LIBS)"
	@echo "AR= $(AR)"
	@echo "RANLIB= $(RANLIB)"
	@echo "RM= $(RM)"

clean:
	$(RM) $(MAIN_A) $(BASE_O) $(MAIN_T) $(MAIN_O)

.PHONY: a t echo clean

main.o: main.c
cal.o: cal.c
