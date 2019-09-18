INC_DIR:=./inc
SRC_DIR:=./src
EXE_DIR:=./bin

TMATH_DIR:=./thirdparty/tmath

TARGET:=$(EXE_DIR)/main
OBJS:= $(wildcard $(SRC_DIR)/*.cc)

CC:=g++
CFLAGS:=-g -Wall -std=c++11

LDFLAGS:= -L$(TMATH_DIR)/lib -Wl,-rpath=$(TMATH_DIR)/lib
LIBS:=-ltmath

$(TARGET):$(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS) $(LDFLAGS) $(LIBS)

clean:
	rm -rf $(TARGET)
