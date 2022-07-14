BINDIR=${EZDIR_HOME}/bin
LIBDIR=-L${EZDIR_HOME}/lib
BINARY=EzMMSSim
SRCFILE=ezmmssim
V=0.000
OBJFILE=${SRCFILE}.$V.o
SOURCE=${SRCFILE}.$V.cpp
LIBLIST=-lezdebug_util -lezcfg_util -lezchannelutil -lezdatetimeutil

INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE}
			g++ ${OBJFILE} ${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
			rm tp*
				

