BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib
BINARY=EzSMSDriver
OBJFILE=ezsmsdriver.o
SOURCE=ezsmsdriver.cpp
OBJFILE1=ezsmsdriverutil.o
SOURCE1=ezsmsdriverutil.cpp
OBJFILE2=ezsmsinfoqueue.o
SOURCE2=ezsmsinfoqueue.cpp

LIBLIST=-lezdebug_util -lezcfg_util -lezsigutil -leztaskutil -lezchannelutil -lezchanneltools -lpthread

INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE2} ${OBJFILE1} ${OBJFILE}
			g++ ${OBJFILE2} ${OBJFILE1} ${OBJFILE} -L${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

${OBJFILE1}	:	${SOURCE1}
			g++ -c ${SOURCE1} -I${INCLUDEDIR}
			
${OBJFILE2}	:	${SOURCE2}
			g++ -c ${SOURCE2} -I${INCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
				


