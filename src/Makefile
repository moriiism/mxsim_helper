include ../Makefile.in

INCLUDE := $(MXSIM_HELPER_INC) $(GSL_INC)

TARGET := libmxsim_helper.a

OBJ := base.o  iolib.o  rand.o  str.o  \
	math.o  func.o  func_par.o \
	plot_conf.o  \
	data1d.o  data1d_nerr.o  data1d_serr.o  data1d_ope.o \
	hist_info.o  \
	hist1d.o  hist1d_nerr.o  hist1d_serr.o  hist1d_ope.o \
	hist2d.o  hist2d_nerr.o  hist2d_serr.o  hist2d_ope.o \
	qdp_tool.o

all: $(TARGET)

LIB_DEST := ../lib
libmxsim_helper.a: ${OBJ}
	$(AR) -r $@ $(OBJ)
	ranlib $@
	if [ ! -d $(LIB_DEST) ]; then mkdir $(LIB_DEST); fi
	cp $@ ${LIB_DEST}
	ranlib ${LIB_DEST}/$@

libmxsim_helper.so: ${OBJ}
	$(CC) -shared -g -O2 -o $@ ${OBJ}
	if [ ! -d $(LIB_DEST) ]; then mkdir $(LIB_DEST); fi
	cp $@ ${LIB_DEST}

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
	-rm -f *.o *.a *.so

cleaner: clean
	-rm -f ${TARGET} *% *~ core
	-rm -R $(LIB_DEST)
