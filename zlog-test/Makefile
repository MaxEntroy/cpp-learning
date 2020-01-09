CC= gcc -std=gnu99
CFLAGS= -Wall -Wextra $(MYCFLAGS)
LDFLAGS= $(MYLDFLAGS)
LIBS= $(MYLIBS)

RM= rm -f

ROOT= /usr/local/thirdparty/zlog-1.2

MYCFLAGS= -I$(ROOT)/include
MYLDFLAGS= -L$(ROOT)/lib -Wl,-rpath=$(ROOT)/lib
MYLIBS= -lzlog -lpthread

MAIN_T= main
MAIN_O= main.o

# Targets start here
t: $(MAIN_T)

$(MAIN_T): $(MAIN_O)
	$(CC) -o $@ $(LDFLAGS) $(MAIN_O) $(LIBS)


echo:
	@echo "CC= $(CC)"
	@echo "CFLAGS= $(CFLAGS)"
	@echo "LDFLAGS= $(LDFLAGS)"
	@echo "LIBS= $(LIBS)"
	@echo "RM= $(RM)"

clean:
	$(RM) $(MAIN_T) $(MAIN_O)

.PHONY: t echo clean

main.o: main.c
