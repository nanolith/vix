.PHONY: ALL clean
SOURCEFILES=$(wildcard *.cpp)
OBJFILES=$(SOURCEFILES:.cpp=.o)
LIBFILE=../src/libvix.a
TESTBIN=vixtest
CXXFLAGS+=-I ../include
LDFLAGS+=-L../src -lvix

ALL: $(TESTBIN)
	./$(TESTBIN)

$(TESTBIN): $(OBJFILES)
	$(CXX) -o $(TESTBIN) $(CXXFLAGS) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(TESTBIN)
	rm -f $(OBJFILES)
