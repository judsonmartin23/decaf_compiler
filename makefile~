decafg: decaf-codegen-release.o decafs.o lex.yy.o y.tab.o semantics.o parsetree.o
	g++ -o decafg decaf-codegen-release.o decafs.o lex.yy.o y.tab.o semantics.o parsetree.o

decaf-codegen-release.o: decaf-codegen-release.cc decafs.h
	g++ -c decaf-codegen-release.cc

decafs.o: decafs.h decafs.cc semantics.h parsetree.h
	g++ -c decafs.cc

semantics.o: semantics.h semantics.cc parsetree.h
	g++ -c semantics.cc

parsetree.o: parsetree.h parsetree.cc
	g++ -c parsetree.cc

y.tab.o: y.tab.c
	g++ -c y.tab.c

lex.yy.o: lex.yy.c
	g++ -c lex.yy.c

y.tab.h: decaf.y
	yacc -d -v decaf.y

y.tab.c: decaf.y
	yacc -d -v decaf.y

lex.yy.c: decaf.l y.tab.h
	flex decaf.l

clean:
	rm -rf *~ lex.yy.* *.o y.tab.* decafp decafs a.out y.output
