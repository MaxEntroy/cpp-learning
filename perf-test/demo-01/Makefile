CXX= g++ -std=c++11
CXXFLAGS= -O3 -g -Wall -Wextra $(MYCXXFLAGS)
LDFLAGS= $(MYLDFLAGS)
LIBS= $(MYLIBS)

YCXXFLAGS=
MYLDFLAGS=
MYLIBS= -ltcmalloc_and_profiler

RM= rm -f

DEMO_T= demo
DEMO_O= demo.o

# Targets start here

t: $(DEMO_T)

$(DEMO_T): $(DEMO_O)
	$(CXX) -o $@ $(LDFLAGS) $(DEMO_O) $(LIBS)

echo:
	@echo "CXX= $(CXX)"
	@echo "CXXFLAGS= $(CFLAGS)"
	@echo "LDFLAGS= $(LDFLAGS)"
	@echo "LIBS= $(LIBS)"
	@echo "RM= $(RM)"

clean:
	$(RM) $(DEMO_T) $(DEMO_O)


.PHONY: t clean

demo.o: demo.cc
