include ../Makefile.in

INCLUDE := $(MXSIM_HELPER_INC) 
LDLIBS  := $(MXSIM_HELPER_LIB) $(LIB)

TARGET := test_hist1d  test_hist2d  test_binary_search

all: $(TARGET)

test_hist1d: test_hist1d.o
	$(CXXN) $@.o ${LDLIBS} -o $@

test_hist2d: test_hist2d.o
	$(CXXN) $@.o ${LDLIBS} -o $@

test_binary_search: test_binary_search.o
	$(CXXN) $@.o ${LDLIBS} -o $@

.SUFFIXES:
.SUFFIXES: .o .c .f .F .cc

.c.o:
	$(CCN) -c $<

.F.o: 
	$(FCN) -c $<

.f.o:
	$(FCN) -c $<

.cc.o:
	${CXXN} -c $<


.PHONY: clean cleaner
clean:
	-rm -f *.o

cleaner: clean
	-rm -f ${TARGET} *% *~ core
