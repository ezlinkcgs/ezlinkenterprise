BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib
BINARY=ezejcmd
OBJFILE=ezejcmd.o
SOURCE=ezejcmd.cpp
LIBLIST=-lezdebug_util -lezcmdutil -leztaskutil -lezchlocateutil -lezcfg_util -lezdatetimeutil
INCLUDEDIR=${EZDIR_HOME}/include


${BINARY}	:	${OBJFILE}  
			g++ ${OBJFILE} -L${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -g -c ${SOURCE} -I${INCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
