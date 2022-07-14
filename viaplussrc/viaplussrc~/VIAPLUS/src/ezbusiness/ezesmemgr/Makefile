BINDIR=${EZDIR_HOME}/bin
LIBDIR=-L${EZDIR_HOME}/lib -L${ORACLE_HOME}/lib
BINARY=EzESMEmgr
OBJFILE=ezesmemgr.o
SOURCE=ezesmemgr.cpp
OBJFILE1=ezesmemgrutil.o
SOURCE1=ezesmemgrutil.cpp
OBJFILE2=ezsmscutil.o
SOURCE2=ezsmscutil.cpp
PROCSOURCE=ezesmemgrutildb.pc
CSOURCE=ezesmemgrutildb.c
COBJFILE=ezesmemgrutildb.o

LIBLIST=-lezdebug_util -lezsigutil -leztaskutil -lezchannelutil -lezcfg_util -lezdbutil -lpthread -lclntsh -lezchanneltools -lezeventutil -lezdatetimeutil
INCLUDEDIR=${EZDIR_HOME}/include
OINCLUDEDIR=${ORACLE_HOME}/precomp/public

${BINARY}	:	${OBJFILE} ${OBJFILE1} ${OBJFILE2} ${COBJFILE}
			g++ ${OBJFILE} ${OBJFILE1} ${OBJFILE2} ${COBJFILE} ${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

${OBJFILE1}	:	${SOURCE1}
			g++ -c ${SOURCE1} -I${INCLUDEDIR}

${OBJFILE2}	:	${SOURCE2}
			g++ -c ${SOURCE2} -I${INCLUDEDIR}

${COBJFILE}	:	${PROCSOURCE}
			proc ${PROCSOURCE}
			cc -c ${CSOURCE} -I${INCLUDEDIR} -I${OINCLUDEDIR}
					
install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
			rm tp*
				
