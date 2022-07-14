BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib
BINARY=EzNDCDriver
OBJFILE=ezndcdriver.o
SOURCE=ezndcdriver.cpp
LIBLIST=-lezdebug_util -lezcfg_util -lezatmutil -lezsigutil -lezchannelutil -leztaskutil -leztemplateutil -lezdatetimeutil -lezatmcashutil -lezsequtil -leztxnsequtil -lezpadssutil 
INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE}  
			g++ ${OBJFILE} -L${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -g -c ${SOURCE} -I${INCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
