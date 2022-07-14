BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib
OLIBDIR=${ORACLE_HOME}/lib
BINARY=ezatmcmd
OBJFILE=ezatmcmd.o
SOURCE=ezatmcmd.cpp
#PROCSOURCE=ezatmcmddb.pc
#COBJFILE=ezatmcmddb.o
#CSOURCE=ezatmcmddb.c

LIBLIST=-lezdebug_util -lezcmdutil -leztaskutil -lezchlocateutil -lezcfg_util -lezatmutil -lezdatetimeutil -lezodbcutil -lezchannelutil -lezatmmemutil
INCLUDEDIR=${EZDIR_HOME}/include


${BINARY}	:	${OBJFILE} 
			g++ ${OBJFILE} -L${LIBDIR} ${LIBLIST} -L${OLIBDIR} -lodbc -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -g -c ${SOURCE} -I${INCLUDEDIR}

#${COBJFILE}	:	${PROCSOURCE}
#			proc ${PROCSOURCE}
#			cc -c ${CSOURCE} -I${ORACLE_HOME}/precomp/public -I${INCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
			rm tp*
