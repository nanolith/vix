.PHONY: ALL clean
SOURCEFILES=$(wildcard *.cpp)
OBJFILES=$(SOURCEFILES:.cpp=.o)
LIBFILE=libvix.a
CXXFLAGS+=-I ../include --coverage -stdlib=libc++

ALL: $(LIBFILE)
	echo $(OBJFILES)

$(LIBFILE): $(OBJFILES)
	ar -rcs $(LIBFILE) $(OBJFILES)

clean:
	rm -f $(LIBFILE)
	rm -f $(OBJFILES)
	rm -f *.gcda *.gcno
