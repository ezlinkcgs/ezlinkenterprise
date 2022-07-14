BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib
BINARY=EzEventMgr
OBJFILE=ezeventlocater.o
SOURCE=ezeventlocater.cpp

INCLUDEDIR=${EZDIR_HOME}/include
LIBDIR=${EZDIR_HOME}/lib
LIBLIST=-lezdebug_util -lezcfg_util -lezsigutil -leztaskutil -lezeventtable -lezchannelutil -lezchanneltools

${BINARY}	:	${OBJFILE}
			g++ ${OBJFILE} -L${LIBDIR} ${LIBLIST} -o ${BINARY}

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

install         :
			mv ${BINARY} ${BINDIR}

clean           :
			rm -f *.o

