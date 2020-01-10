CC= gcc -std=gnu99
CFLAGS= -Wall -Wextra $(MYCFLAGS)
LDFLAGS= $(MYLDFLAGS)
LIBS= $(MYLIBS)

DYNAMIC_ROOT= /usr/local/thirdparty/zlog-1.2
STATIC_ROOT= .

MYCFLAGS= -I$(DYNAMIC_ROOT)/include
MYLDFLAGS= -L$(DYNAMIC_ROOT)/lib -Wl,-rpath=$(DYNAMIC_ROOT)/lib
MYLIBS= -lzlog -lpthread

AR= ar rcu
RANLIB= ranlib
RM= rm -f

MAIN_A= libmain.a
BASE_O= log.o

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

main.o: main.c log.h
log.o: log.c log.h
