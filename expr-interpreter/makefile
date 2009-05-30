LEG=../thirdparty/peg/leg
GCDIR=../thirdparty/gc
GCLIB=$(GCDIR)/libgc.a
CFLAGS=-g -I$(GCDIR)

all: $(LEG) expr

$(LEG):
	make -C ../thirdparty/peg

$(GCLIB):
	make -C $(GCDIR)

expr: expr.o grammar.o $(GCLIB)
	g++ $(CFLAGS) -o expr expr.o grammar.o $(GCLIB)

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