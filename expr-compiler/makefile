LEG=../thirdparty/peg/leg
NANOJIT=../thirdparty/nanojit-central
GCDIR=../thirdparty/gc
GCLIB=$(GCDIR)/libgc.a
CFLAGS=-g -I$(NANOJIT) -I$(NANOJIT)/build -I../thirdparty -DHAVE_CONFIG_H -DNANOJIT_CENTRAL -Wno-invalid-offsetof -Wno-variadic-macros -Werror

all: $(LEG) expr

$(LEG):
	make -C ../thirdparty/peg

$(GCLIB):
	make -C $(GCDIR)

$(NANOJIT)/configure: $(NANOJIT)/configure.in $(NANOJIT)/config.h.in $(NANOJIT)/Makefile.in
	cd $(NANOJIT) && autoconf
	mkdir -p $(NANOJIT)/build
	cd $(NANOJIT)/build && ../configure

$(NANOJIT)/build/libnanojit.a: $(NANOJIT)/configure
	cd $(NANOJIT)/build && make 

expr: expr.o grammar.o $(GCLIB) $(NANOJIT)/build/libnanojit.a
	g++ $(CFLAGS) -o expr expr.o grammar.o $(NANOJIT)/build/libnanojit.a $(GCLIB)

expr.o: expr.cpp expr.h $(GCDIR)/gc.h $(NANOJIT)/build/libnanojit.a
	g++ $(CFLAGS) -c -o expr.o expr.cpp

grammar.o: grammar.cpp expr.h $(GCDIR)/gc.h
	g++ $(CFLAGS) -c -o grammar.o grammar.cpp

grammar.cpp: grammar.leg
	$(LEG) -o grammar.cpp grammar.leg

clean:
	rm expr
	rm expr.o
	rm grammar.o
	rm grammar.cpp
