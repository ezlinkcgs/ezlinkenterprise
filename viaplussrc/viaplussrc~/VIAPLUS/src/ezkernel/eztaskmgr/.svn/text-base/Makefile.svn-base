BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib
BINARY=EzTaskMgr
OBJFILE=eztaskmgr.o
SOURCE=eztaskmgr.cpp
OBJFILE1=eztaskmgrutil.o
SOURCE1=eztaskmgrutil.cpp
LIBLIST=-lezdebug_util -lezcfg_util -lezsigutil
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
