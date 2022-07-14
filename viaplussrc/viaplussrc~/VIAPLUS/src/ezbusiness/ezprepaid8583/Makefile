BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib
BINARY=EzPREPAID8583
OBJFILE=ezprepaid8583.o
SOURCE=ezprepaid8583.cpp
LIBLIST=-lezdebug_util -lezcfg_util -lezsigutil -leztaskutil -lezchannelutil -lezfmt_util -leziso8583util -lezdatetimeutil  -leznetworkutil -lezechoutil
INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE} 
			g++ ${OBJFILE} -L${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
				
