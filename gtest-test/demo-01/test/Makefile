CXX= g++ -std=c++11
CXXFLAGS= -g -Wall -Wextra $(MYCXXFLAGS)
LDFLAGS= $(MYLDFLAGS)
LIBS= $(MYLIBS)

STATIC_ROOT= ..

MYCXXFLAGS= -I$(STATIC_ROOT)
MYLDFLAGS= -L$(STATIC_ROOT)/src
MYLIBS= -lcal -lgtest -lpthread

RM= rm -f

CAL_TEST_T= cal_test
CAL_TEST_O= cal_test.o

# Targets start here

t: $(CAL_TEST_T)

$(CAL_TEST_T): $(CAL_TEST_O)
	$(CXX) -o $@ $(LDFLAGS) $(CAL_TEST_O) $(LIBS)

echo:
	@echo "CXX= $(CXX)"
	@echo "CXXFLAGS= $(CFLAGS)"
	@echo "LDFLAGS= $(LDFLAGS)"
	@echo "LIBS= $(LIBS)"
	@echo "RM= $(RM)"

clean:
	$(RM) $(CAL_TEST_T) $(CAL_TEST_O)


.PHONY: cal_test clean

cal_test.o: cal_test.cc
