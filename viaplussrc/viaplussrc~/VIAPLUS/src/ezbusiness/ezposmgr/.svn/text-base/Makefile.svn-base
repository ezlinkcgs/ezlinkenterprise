BINDIR=${EZDIR_HOME}/bin
LIBDIR=-L${EZDIR_HOME}/lib -L${ORACLE_HOME}/lib
BINARY=EzPOSMgr
OBJFILE=ezposmgr.o
SOURCE=ezposmgr.cpp
OBJFILE1=ezposmgrutil.o
SOURCE1=ezposmgrutil.cpp
OBJFILE2=ezposmgrdb.o
SOURCE2=ezposmgrdb.c
SOURCEPC=ezposmgrdb.pc
OINCLUDEDIR=${ORACLE_HOME}/precomp/public
LIBLIST=-lezdebug_util -lezsigutil -leztaskutil -lezcfg_util -lclntsh -lezchanneltools -lezdbutil

INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE} ${OBJFILE1} ${OBJFILE2}
			g++ ${OBJFILE} ${OBJFILE1} ${OBJFILE2} ${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

${OBJFILE1}	:	${SOURCE1}
			g++ -c ${SOURCE1} -I${INCLUDEDIR}

${OBJFILE2}	:	${SOURCEPC}
			proc ${SOURCEPC}
			cc -c ${SOURCE2} -I${INCLUDEDIR} -I${OINCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
			rm tp*
				
