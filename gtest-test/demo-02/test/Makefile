CXX= g++ -std=c++11
CXXFLAGS= -g -Wall -Wextra $(MYCXXFLAGS)
LDFLAGS= $(MYLDFLAGS)
LIBS= $(MYLIBS)

STATIC_ROOT= ..

MYCXXFLAGS= -I$(STATIC_ROOT)
MYLDFLAGS=
MYLIBS= -lgtest_main -lgtest -lpthread

RM= rm -f

QUE_TEST_T= que_test
QUE_TEST_O= que_test.o

# Targets start here

t: $(QUE_TEST_T)

$(QUE_TEST_T): $(QUE_TEST_O)
	$(CXX) -o $@ $(LDFLAGS) $(QUE_TEST_O) $(LIBS)

echo:
	@echo "CXX= $(CXX)"
	@echo "CXXFLAGS= $(CFLAGS)"
	@echo "LDFLAGS= $(LDFLAGS)"
	@echo "LIBS= $(LIBS)"
	@echo "RM= $(RM)"

clean:
	$(RM) $(QUE_TEST_T) $(QUE_TEST_O)


.PHONY: que_test clean

que_test.o: que_test.cc
