BINDIR=${EZDIR_HOME}/bin
LIBDIR=-L${EZDIR_HOME}/lib 
BINARY=ezuploadcmd
OBJFILE=ezuploadcmd.o
SOURCE=ezuploadcmd.cpp
LIBLIST=-lezdebug_util -lezchlocateutil -lezcfg_util -lezchanneltools -lezcmdutil -lezchannelutil -leztaskutil
INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE} 
			g++ ${OBJFILE} ${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}		:	${SOURCE}
					g++ -c ${SOURCE} -I${INCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
				
