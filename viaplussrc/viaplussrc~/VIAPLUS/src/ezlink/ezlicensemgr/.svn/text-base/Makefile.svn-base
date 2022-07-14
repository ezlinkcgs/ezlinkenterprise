BINDIR=${EZDIR_HOME}/bin
LIBDIR=-L${EZDIR_HOME}/lib
BINARY=EzLicenseMgr
OBJFILE=ezlicensemgr.o
SOURCE=ezlicensemgr.cpp
OBJFILE1=ezlicenseparseutil.o
SOURCE1=ezlicenseparseutil.cpp

LIBLIST=-lezdebug_util -lezsigutil -leztaskutil -lezcfg_util -lezchanneltools -leztokenutil

INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE} ${OBJFILE1}
			g++ ${OBJFILE} ${OBJFILE1} ${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

${OBJFILE1}	:	${SOURCE1}
			g++ -c ${SOURCE1} -I${INCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
			rm tp*
				
