.PHONY: ALL clean
SOURCEFILES=$(wildcard *.cpp)
OBJFILES=$(SOURCEFILES:.cpp=.o)
LIBFILE=../src/libvix.a
TESTBIN=vixtest
CXXFLAGS+=--coverage -stdlib=libc++ -I ../include
LDFLAGS+=-L../src -lvix -lstdc++

ALL: $(TESTBIN) coverage-report
	lcov -b ../src --directory ../src --zerocounters
	(cd ../src && ../test/$(TESTBIN))
	lcov -b ../src --directory ../src --capture --output-file coverage-report/libvix.info
	lcov --remove coverage-report/libvix.info "/usr/*" -o coverage-report/libvix.info
	genhtml --no-branch-coverage -o coverage-report coverage-report/libvix.info

$(TESTBIN): $(OBJFILES) 
	$(CXX) -o $(TESTBIN) $(CXXFLAGS) $(OBJFILES) $(LDFLAGS)

coverage-report:
	mkdir coverage-report

clean:
	rm -f $(TESTBIN)
	rm -f $(OBJFILES)
	rm -rf coverage-report
