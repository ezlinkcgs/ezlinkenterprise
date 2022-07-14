BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib
BINARY=EzCommMgr
OBJFILE=ezcommmgr.o
SOURCE=ezcommmgr.cpp
OBJFILE1=ezcommmgrutil.o
SOURCE1=ezcommmgrutil.cpp
LIBLIST=-lezdebug_util -lezcfg_util -lezsigutil -leztaskutil -lpthread
INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE} ${OBJFILE1} 
			g++ ${OBJFILE} ${OBJFILE1} -L${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

${OBJFILE1}	:	${SOURCE1}
			g++ -c ${SOURCE1} -I${INCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
