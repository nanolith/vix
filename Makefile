.PHONY: ALL src-build test-build clean src-clean test-clean

ALL: src-build test-build

src-build:
	(cd src && $(MAKE))

test-build:
	(cd test && $(MAKE))

clean: src-clean test-clean

src-clean:
	(cd src && $(MAKE) clean)

test-clean:
	(cd test && $(MAKE) clean)
