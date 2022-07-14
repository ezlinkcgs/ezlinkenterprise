BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib
BINARY=EzMsgRouter
OBJFILE=ezmsgrouter.o
SOURCE=ezmsgrouter.cpp
OBJFILE1=ezmsgrouterutil.o
SOURCE1=ezmsgrouterutil.cpp
LIBLIST=-lezdebug_util -lezsigutil -leztaskutil -lezcfg_util -lezcommutil -lezchanneltools -lezchannelparam
INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE1} ${OBJFILE} 
			g++ ${OBJFILE1} ${OBJFILE} -L${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

${OBJFILE1}	:	${SOURCE1}
			g++ -c ${SOURCE1} -I${INCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
				
