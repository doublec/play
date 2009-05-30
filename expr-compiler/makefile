LEG=../thirdparty/peg/leg
NANOJIT=../thirdparty/nanojit/libnanojit.a
GCDIR=../thirdparty/gc
GCLIB=$(GCDIR)/libgc.a
CFLAGS=-g -I../thirdparty --include ../thirdparty/nanojit/mozilla-config.h

all: $(LEG) expr

$(LEG):
	make -C ../thirdparty/peg

$(GCLIB):
	make -C $(GCDIR)

$(NANOJIT):
	make -C `(dirname $(NANOJIT))`

expr: expr.o grammar.o $(GCLIB) $(NANOJIT)
	g++ $(CFLAGS) -o expr expr.o grammar.o $(NANOJIT) $(GCLIB)

expr.o: expr.cpp expr.h $(GCDIR)/gc.h
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