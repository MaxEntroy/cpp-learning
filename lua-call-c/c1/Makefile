OBJS:=main.c
TARGET:=main

CC:=gcc -std=gnu99
CFLAGS:=-g -Wall
LDFLAGS:=-L./thirdparty -Wl,-rpath=./thirdparty -llua -ldl -lm

$(TARGET):$(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf $(TARGET)
