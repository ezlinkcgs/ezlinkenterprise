BINDIR=${EZDIR_HOME}/bin
LIBDIR=-L${EZDIR_HOME}/lib
BINARY=EzTxnSim
OBJFILE=eztxnsim.o
SOURCE=eztxnsim.cpp
LIBLIST=-lezdebug_util -lezchannelutil -lezcfg_util -lezdatetimeutil
INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE}
			g++ ${OBJFILE} ${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}		:	${SOURCE}
					g++ -c ${SOURCE} -I${INCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
					