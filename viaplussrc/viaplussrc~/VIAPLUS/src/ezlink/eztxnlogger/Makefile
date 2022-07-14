BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib
OLIBDIR=${ORACLE_HOME}/lib

BINARY=EzTxnLogger
OBJFILE=eztxnlogger.o
SOURCE=eztxnlogger.cpp

#PROCSOURCE=eztxnloggerdb.pc
#COBJFILE=eztxnloggerdb.o
#CSOURCE=eztxnloggerdb.c

LIBLIST=-lezdebug_util -lezsigutil -leztaskutil -lezchannelutil -lezcfg_util -lezodbcutil -lezdatetimeutil -leztxnmsgvalidator
INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE} 
			g++ ${OBJFILE} -L${LIBDIR} ${LIBLIST} -lodbc -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

#${COBJFILE}	:	${PROCSOURCE}
#			proc ${PROCSOURCE}
#			cc -c ${CSOURCE} -I${ORACLE_HOME}/precomp/public -I${INCLUDEDIR}
			
install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
			rm tp*
				
