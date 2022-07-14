BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib
OLIBDIR=${ORACLE_HOME}/lib

BINARY=EzPortUpdater
OBJFILE=ezportupdater.o
SOURCE=ezportupdater.cpp
#PROCSOURCE=ezportupdaterdb.pc
#COBJFILE=ezportupdaterdb.o
#CSOURCE=ezportupdaterdb.c

LIBLIST=-lezdebug_util -lezsigutil -leztaskutil -lezchannelutil -lezcfg_util -lezodbcutil -lezdatetimeutil -lezchanneltools -lpthread
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
				
