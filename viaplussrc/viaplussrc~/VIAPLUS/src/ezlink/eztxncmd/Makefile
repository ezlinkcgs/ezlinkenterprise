BINDIR=${EZDIR_HOME}/bin
LIBDIR=-L${EZDIR_HOME}/lib -L${ORACLE_HOME}/lib
BINARY=eztxncmd
OBJFILE=eztxncmd.o
SOURCE=eztxncmd.cpp
LIBLIST=-lezdebug_util -lezchlocateutil -lezchanneltools -lezcmdutil -lezcfg_util -lezdatetimeutil 
INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE}
			g++ ${OBJFILE} ${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}		:	${SOURCE}
					g++ -c ${SOURCE} -I${INCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
					