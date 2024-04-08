CXX= g++ -std=c++17

AR= ar rcu
RANLIB= ranlib
RM= rm -rf

MYSUM_A= libmysum.a
MYSUM_O= mysum.o

a: $(MYSUM_A)

$(MYSUM_A): $(MYSUM_O)
	$(AR) $@ $(MYSUM_O)
	$(RANLIB) $@

clean:
	$(RM) $(MYSUM_A) $(MYSUM_O)
