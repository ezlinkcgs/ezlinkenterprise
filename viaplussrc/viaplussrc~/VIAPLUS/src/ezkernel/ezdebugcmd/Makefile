BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib
BINARY=ezdebugcmd
OBJFILE=ezdebugcmd.o
SOURCE=ezdebugcmd.cpp
LIBLIST=-lezdebug_util -lezcmdutil -leztaskutil -lezcfg_util
INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE}
			g++ ${OBJFILE} -L${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
