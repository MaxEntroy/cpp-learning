CXX= g++ -std=c++11
CXXFLAGS= -g -Wall -Wextra $(MYCXXFLAGS)
LDFLAGS= $(MYLDFLAGS)
LIBS= $(MYLIBS)

MYCXXFLAGS=
MYLDFLAGS=
MYLIBS=

AR= ar rcu
RANLIB= ranlib
RM= rm -rf

MAIN_A=
BASE_O=

MAIN_T= main
MAIN_O= main.o

# Targets start here
a: $(MAIN_A)

t: $(MAIN_T)

$(MAIN_A): $(BASE_O)
	$(AR) $@ $(BASE_O)
	$(RANLIB) $@

$(MAIN_T): $(MAIN_O)
	$(CXX) -o $@ $(LDFLAGS) $(MAIN_O) $(LIBS)

echo:
	@echo "CXX= $(CXX)"
	@echo "CXXFLAGS= $(CXXFLAGS)"
	@echo "LDFLAGS= $(LDFLAGS)"
	@echo "LIBS= $(LIBS)"
	@echo "AR= $(AR)"
	@echo "RANLIB= $(RANLIB)"
	@echo "RM= $(RM)"

clean:
	$(RM) $(MAIN_A) $(BASE_O) $(MAIN_T) $(MAIN_O)

.PHONY: a t echo clean

main.o: main.cc derived.h
