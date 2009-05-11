CFLAGS=-g -I../thirdparty --include ../thirdparty/nanojit/mozilla-config.h
LEG=../thirdparty/peg/leg
NANOJIT=../thirdparty/nanojit/libnanojit.a
all: $(LEG) $(NANOJIT) expr

$(LEG):
	make -C ../thirdparty/peg

$(NANOJIT):
	make -C `(dirname $(NANOJIT))`

expr: expr.o grammar.o
	g++ $(CFLAGS) -o expr expr.o grammar.o -lgc -lgccpp $(NANOJIT)

expr.o: expr.cpp expr.h
	g++ $(CFLAGS) -c -o expr.o expr.cpp

grammar.o: grammar.cpp expr.h
	g++ $(CFLAGS) -c -o grammar.o grammar.cpp

grammar.cpp: grammar.leg
	$(LEG) -o grammar.cpp grammar.leg

clean:
	rm expr
	rm expr.o
	rm grammar.o
	rm grammar.cpp