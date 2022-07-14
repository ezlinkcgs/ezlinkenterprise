BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib
BINARY=EzCommDriver
OBJFILE=ezcommdrvr.o
SOURCE=ezcommdrvr.cpp
LIBLIST=-lezdebug_util -lezcfg_util -lezsigutil -lezcommutil -leztcpiputil -lezchannelutil -lpthread -lnsl -lezdatetimeutil
INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE} 
			g++ ${OBJFILE} -L${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o

				
