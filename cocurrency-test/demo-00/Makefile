CXX= g++ -std=c++11
CXXFLAGS= -g -Wall $(MYCXXFLAGS)
LDFLAGS= $(MYLDFLAGS)
LIBS= $(MYLIBS)

MYCXXFLAGS=
MYLDFLAGS=
MYLIBS= -pthread

RM= rm -rf

MAIN_T= main
MAIN_O= main.o

# Targets star here

t: $(MAIN_T)

$(MAIN_T): $(MAIN_O)
	$(CXX) -o $@ $(LDFLAGS) $(MAIN_O) $(LIBS)

clean:
	$(RM) $(MAIN_T) $(MAIN_O)

.PHONY: clean

main.o: main.cc
