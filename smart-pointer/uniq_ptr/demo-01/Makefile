CXX= g++ -std=c++14
CXXFLAGS= -g -Wall -Wextra $(MYCXXFLAGS)
LDFLAGS= $(MYLDFLAGS)
LIBS= $(MYLIBS)

MYCXXFLAGS=
MYLDFLAGS=
MYLIBS=

RM= rm -rf

MAIN_T= main
MAIN_O= main.o

# Targets start here

t: $(MAIN_T)

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


.PHONY: t echo clean

main.o: main.cc
