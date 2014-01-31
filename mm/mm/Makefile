
CCC = g++
CCFLAGS= -O2
LEX = flex
LFLAGS= -8
YACC= bison
YFLAGS= -d -t -y -v

RM = /bin/rm -f

mm: y.tab.o lex.yy.o 
	${CCC} ${CCFLAGS} lex.yy.o y.tab.o -o mm -lfl

y.tab.o: mm.ypp
	${YACC} ${YFLAGS} mm.ypp
	${CCC} ${CCFLAGS} y.tab.c -c 

lex.yy.o: mm.lpp
	${LEX} $(LFLAGS) mm.lpp
	${CCC} ${CCFLAGS} lex.yy.c -c 

clean:
	/bin/rm -f lex.yy.* y.tab.* *.o mm
