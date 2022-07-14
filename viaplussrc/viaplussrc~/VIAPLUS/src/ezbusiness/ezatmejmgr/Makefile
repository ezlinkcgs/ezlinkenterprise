BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib

BINARY=EzAtmEJMgr

OBJFILE=ezatmejmgr.o
SOURCE=ezatmejmgr.cpp
UTILOBJFILE=ezatmejutil.o
UTILSOURCE=ezatmejutil.cpp

LIBLIST=-lezdebug_util -lezcfg_util -lezsigutil -lezchannelutil -leztaskutil -lezdatetimeutil 

INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE} ${UTILOBJFILE} 
			g++ ${OBJFILE} ${UTILOBJFILE} -L${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -g -c ${SOURCE} -I${INCLUDEDIR}

${UTILOBJFILE}  :	${UTILSOURCE}
			g++ -c ${UTILSOURCE} -I${INCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
