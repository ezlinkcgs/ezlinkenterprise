BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib

BINARY=EzATMController

OBJFILE=ezatmcontroller.o
SOURCE=ezatmcontroller.cpp

LIBLIST=-lezdebug_util -lezcfg_util -lezsigutil -lezchannelutil -leztaskutil -lezatmutil -lezsecurityutil -lezdatetimeutil

INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE}  
			g++ ${OBJFILE} -L${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -g -c ${SOURCE} -I${INCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
