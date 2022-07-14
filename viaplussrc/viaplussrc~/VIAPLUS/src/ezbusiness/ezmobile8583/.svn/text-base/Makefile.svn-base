BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib
OLIBDIR=${ORACLE_HOME}/lib
BINARY=EzMobile8583
OBJFILE=ezmobile8583.o
SOURCE=ezmobile8583.cpp

PROCSOURCE=ezmobile8583db.pc
COBJFILE=ezmobile8583db.o
CSOURCE=ezmobile8583db.c

LIBLIST=-lezdebug_util -lezcfg_util -lezsigutil -leztaskutil -lezchannelutil -lezfmt_util -lezdbutil 
INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE} ${COBJFILE}
			g++ ${OBJFILE} ${COBJFILE} -L${LIBDIR} ${LIBLIST} -L${OLIBDIR} -lclntsh -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

${COBJFILE}     :       ${PROCSOURCE}
                        
			proc ${PROCSOURCE}
			cc -c ${CSOURCE} -I${ORACLE_HOME}/precomp/public -I${INCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
				
