BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib
BINARY=EzChannelMgr
OBJFILE=ezchannelmgr.o
SOURCE=ezchannelmgr.cpp
OBJFILE1=ezchannelmgrutil.o
SOURCE1=ezchannelmgrutil.cpp
OBJFILE2=ezipckeyutil.o
SOURCE2=ezipckeyutil.cpp
LIBLIST=-lezdebug_util -lezcfg_util -lezsigutil -leztaskutil -lezchannelparam
INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE} ${OBJFILE1} ${OBJFILE2}
			g++ ${OBJFILE} ${OBJFILE1} ${OBJFILE2} -L${LIBDIR} ${LIBLIST} -o ${BINARY}	

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
				
