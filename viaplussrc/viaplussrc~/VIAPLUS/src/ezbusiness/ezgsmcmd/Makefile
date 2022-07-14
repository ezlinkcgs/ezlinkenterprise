BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib
BINARY=ezgsmcmd
OBJFILE=ezgsmcmd.o
SOURCE=ezgsmcmd.cpp
LIBLIST=-lezdebug_util -lezcmdutil -lezcfg_util -lezchlocateutil -lezchanneltools
INCLUDEDIR=${EZDIR_HOME}/include


${BINARY}	:	${OBJFILE}  
			g++ ${OBJFILE} -L${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -g -c ${SOURCE} -I${INCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o

