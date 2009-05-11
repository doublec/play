CFLAGS=-g

all: expr

expr: expr.o grammar.o
	g++ $(CFLAGS) -o expr expr.o grammar.o -lgc -lgccpp

expr.o: expr.cpp expr.h
	g++ $(CFLAGS) -c -o expr.o expr.cpp

grammar.o: grammar.cpp expr.h
	g++ $(CFLAGS) -c -o grammar.o grammar.cpp

grammar.cpp: grammar.leg
	leg -o grammar.cpp grammar.leg

clean:
	rm expr
	rm expr.o
	rm grammar.o
	rm grammar.cpp