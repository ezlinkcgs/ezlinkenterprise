BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib
BINARY=EzMerchant8583
V=0.000
OBJFILE=ezmerchant8583.$V.o
SOURCE=ezmerchant8583.$V.cpp
LIBLIST=-lezdebug_util -lezcfg_util -lezsigutil -leztaskutil -lezchannelutil -lezfmt_util -leziso8583util -lezdatetimeutil -lezmmsutil -lezmmsdbutil -lezdbutil
INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE} 
			g++ ${OBJFILE} -L${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
				
