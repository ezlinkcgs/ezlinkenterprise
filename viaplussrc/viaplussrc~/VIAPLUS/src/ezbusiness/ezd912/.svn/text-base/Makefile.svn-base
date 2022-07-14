BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib
BINARY=EzD912Driver
OBJFILE=ezd912driver.o
SOURCE=ezd912driver.cpp
LIBLIST=-lezdebug_util -lezcfg_util -lezatmutil -lezsigutil -lezchannelutil -leztaskutil -leztemplateutil -lezatmcashutil -lezdatetimeutil -lezpadssutil
INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE}  
			g++ ${OBJFILE} -L${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -g -c ${SOURCE} -I${INCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
