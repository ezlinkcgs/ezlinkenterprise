BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib
BINARY=ezchannelcmd
OBJFILE=ezchannelcmd.o
SOURCE=ezchannelcmd.cpp
OBJFILE1=ezchannelcmdutil.o
SOURCE1=ezchannelcmdutil.cpp
LIBLIST=-lezdebug_util -lezcmdutil -leztaskutil -lezcfg_util -lezmsgqutil -lezchannelparam -lezeventtable -lezchanneltools
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
