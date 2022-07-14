BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib

BINARY=ezseccmd

OBJFILE=ezsecuritycmd.o
SOURCE=ezsecuritycmd.cpp

#PROCSOURCE=ezsecuritycmddb.pc
#COBJFILE=ezsecuritycmddb.o
#CSOURCE=ezsecuritycmddb.c

LIBLIST=-lezdebug_util -lezcmdutil -leztaskutil -lezchlocateutil -lezcfg_util -lezchanneltools -lezodbcutil -lezsecuritydriverutil

INCLUDEDIR=${EZDIR_HOME}/include


${BINARY}	:	${OBJFILE}  
			g++ ${OBJFILE} -L${LIBDIR} ${LIBLIST} -lodbc -o ${BINARY}	

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
