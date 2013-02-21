.PHONY: ALL src-build test-build clean src-clean test-clean

CXXFLAGS+= -std=c++11
export CXXFLAGS

ALL: src-build test-build

src-build:
	(cd src && $(MAKE))

test-build: src-build
	(cd test && $(MAKE))

clean: src-clean test-clean

src-clean:
	(cd src && $(MAKE) clean)

test-clean:
	(cd test && $(MAKE) clean)
