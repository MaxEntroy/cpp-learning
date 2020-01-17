CXX= g++ -std=c++11
CXXFLAGS= -g -Wall -Wextra

AR= ar rcu
RANLIB= ranlib
RM= rm -rf

CAL_A= libcal.a
CAL_O= cal.o

# Targets start here
a: $(CAL_A)

$(CAL_A): $(CAL_O)
	$(AR) $@ $(CAL_O)
	$(RANLIB) $@

echo:
	@echo "CXX= $(CXX)"
	@echo "CXXFLAGS= $(CXXFLAGS)"
	@echo "AR= $(AR)"
	@echo "RANLIB= $(RANLIB)"
	@echo "RM= $(RM)"

clean:
	$(RM) $(CAL_A) $(CAL_O)


.PHONY: a echo clean

cal.o: cal.cc cal.h
