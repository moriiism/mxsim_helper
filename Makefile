ALL = src
TEST = test
SUBDIR = include  src  doc  test  

.PHONY: all test clean cleaner

all:
	for dir in $(ALL); do \
	(cd $$dir; ${MAKE} all); \
	done

test: all
	for dir in $(TEST); do \
	(cd $$dir; ${MAKE} all); \
	done

clean:
	for dir in $(SUBDIR); do \
	(cd $$dir; ${MAKE} clean); \
	done

cleaner:
	-rm -f *~
	for dir in $(SUBDIR); do \
	(cd $$dir; ${MAKE} cleaner); \
	done
