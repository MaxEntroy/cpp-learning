TARGET:=main
OBJS:=main.cc

CXXFLAGS:=-g -Wall -std=c++11

$(TARGET):$(OBJS)
	$(CXX) -o $@ $(OBJS) $(CXXFLAGS)

clean:
	rm -rf $(TARGET)
