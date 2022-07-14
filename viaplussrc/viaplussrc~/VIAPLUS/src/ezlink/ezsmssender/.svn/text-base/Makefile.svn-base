BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib
BINARY=EzSMSSender
FNAME=ezsmssender

LIBLIST=-lezdebug_util -lezsigutil -leztaskutil -lezchannelutil -lezcfg_util -lezdatetimeutil -leztokenutil

INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${FNAME}.o
				g++ ${FNAME}.o -L${LIBDIR} ${LIBLIST} -o ${BINARY}	

${FNAME}.o	:	${FNAME}.cpp
			g++ -c ${FNAME}.cpp -I${INCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
			rm tp*
				

