BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib
BINARY=EzLoadBalancer
OBJFILE=ezloadbalancer.o
SOURCE=ezloadbalancer.cpp

INCLUDEDIR=${EZDIR_HOME}/include
LIBDIR=${EZDIR_HOME}/lib
LIBLIST=-lezdebug_util -lezcfg_util -lezsigutil -leztaskutil -lezmsgqutil

${BINARY}	:	${OBJFILE}
			g++ ${OBJFILE} -L${LIBDIR} ${LIBLIST} -o ${BINARY}

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

install         :
			mv ${BINARY} ${BINDIR}

clean           :
			rm -f *.o

