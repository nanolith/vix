.PHONY: ALL clean
SOURCEFILES=$(wildcard *.cpp)
OBJFILES=$(SOURCEFILES:.cpp=.o)
LIBFILE=libvix.a
CXXFLAGS+=-I ../include --coverage

ALL: $(LIBFILE)
	echo $(OBJFILES)

$(LIBFILE): $(OBJFILES)
	ar -rcs $(LIBFILE) $(OBJFILES)

clean:
	rm -f $(LIBFILE)
	rm -f $(OBJFILES)
