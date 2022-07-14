BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib
BINARY=EzVISASMS8583
OBJFILE=ezvisasms8583.o
SOURCE=ezvisasms8583.cpp
LIBLIST=-lezdebug_util -lezcfg_util -lezsigutil -leztaskutil -lezchannelutil -lezfmt_util -leziso8583util -lezdatetimeutil
INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE} 
			g++ ${OBJFILE} -L${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
				
