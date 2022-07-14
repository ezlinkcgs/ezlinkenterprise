BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib
BINARY=ezmon
OBJFILE=ezmon.o
SOURCE=ezmon.cpp
LIBLIST=-lezdebug_util -lezcfg_util -lezmsgqutil -lezeventtable -lezchanneltools -leztxnmoninfoutil -lcurses

INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE}
			g++ ${OBJFILE} -L${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
