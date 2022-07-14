BINDIR=${EZDIR_HOME}/bin
LIBDIR=-L${EZDIR_HOME}/lib -L${ORACLE_HOME}/lib
BINARY=EzMMSMgr
OBJFILE=ezmmsmgr.o
SOURCE=ezmmsmgr.cpp
OBJFILE1=ezmmsmgrutil.o
SOURCE1=ezmmsmgrutil.cpp
OBJFILE2=ezmmsmgrodbcutil.o
SOURCE2=ezmmsmgrodbcutil.cpp
#SOURCEPC=ezmmsmgrdb.pc
OINCLUDEDIR=${ORACLE_HOME}/precomp/public
LIBLIST=-lezdebug_util -lezsigutil -leztaskutil -lezcfg_util -lodbc -lezchanneltools -lezodbcutil

INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE} ${OBJFILE1} ${OBJFILE2}
			g++ ${OBJFILE} ${OBJFILE1} ${OBJFILE2} ${LIBDIR} ${LIBLIST} -o ${BINARY}

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

${OBJFILE1}	:	${SOURCE1}
			g++ -c ${SOURCE1} -I${INCLUDEDIR}

${OBJFILE2}	:	${SOURCE2}
			g++ -c ${SOURCE2} -I${INCLUDEDIR}
			
#${OBJFILE2}	:	${SOURCEPC}
#			proc ${SOURCEPC}
#			cc -c ${SOURCE2} -I${INCLUDEDIR} -I${OINCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
			rm tp*
				
