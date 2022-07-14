BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib

BINARY=EzATM0001

OBJFILE=ezsimulator.o
SOURCE=ezsimulator.cpp

OBJFILE1=ezatmsimulator.o
SOURCE1=ezatmsimulator.cpp

OBJFILE2=DESutil.o
SOURCE2=DESutil.cpp

LIBLIST=-lezdebug_util -lezsigutil -leztaskutil -lezchannelutil -lezcfg_util -lezdbutil -lezchanneltools 

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
				
