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

MYCFLAGS=
MYLDFLAGS=
MYLIBS=

ALL_A= libmyio.a
ALL_O= numberio.o strio.o

# Targets start here
$(ALL_A): $(ALL_O) 
	$(AR) $@ $(ALL_O)
	$(RANLIB) $@

o: $(ALL_O)

a: $(ALL_A)

clean:
	$(RM) $(ALL_A) $(ALL_O)

echo:
	@echo "CC= $(CC)"
	@echo "CFLAGS= $(CFLAGS)"
	@echo "LDFLAGS= $(SYSLDFLAGS)"
	@echo "LIBS= $(LIBS)"
	@echo "AR= $(AR)"
	@echo "RANLIB= $(RANLIB)"
	@echo "RM= $(RM)"

.PHONY: o a clean echo

numberio.o: numberio.c
strio.o: strio.c
