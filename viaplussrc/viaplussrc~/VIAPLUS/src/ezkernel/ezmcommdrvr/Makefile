BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib
BINARY=EzPOSSRVR_1
OBJFILE=ezmcommdrvr.o
SOURCE=ezmcommdrvr.cpp
LIBLIST=-lezdebug_util -lezcfg_util -lezsigutil -lezchannelutil -lpthread -lnsl -lezdatetimeutil -lezchanneltools -leztaskutil -leztcpiputil
INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE} ${OBJFILE1} 
			g++ ${OBJFILE} ${OBJFILE1} -L${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o

				
