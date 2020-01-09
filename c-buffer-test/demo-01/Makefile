CC= gcc -std=gnu99
CFLAGS= -Wall -Wextra

RM= rm -f

BUFFER_T= buffer
BUFFER_O= buffer.o

# Targets start here
t: $(BUFFER_T)

$(BUFFER_T): $(BUFFER_O)
	$(CC) -o $@ $(BUFFER_O)

echo:
	@echo "CC= $(CC)"
	@echo "CFLAGS= $(CFLAGS)"
	@echo "RM= $(RM)"

clean:
	$(RM) $(BUFFER_T) $(BUFFER_O)

.PHONY: t echo clean

buffer.o: buffer.c
