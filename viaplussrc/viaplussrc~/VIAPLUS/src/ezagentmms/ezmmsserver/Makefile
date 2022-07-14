BINDIR=${EZDIR_HOME}/bin
LIBDIR=-L${EZDIR_HOME}/lib -L${ORACLE_HOME}/lib
BINARY=EzMMSServer
V=0.000
OBJFILE=ezmmsserver.$V.o
SOURCE=ezmmsserver.$V.cpp
OBJFILE1=ezmmsserverutil.$V.o
SOURCE1=ezmmsserverutil.$V.cpp
OBJFILE2=ezmmsserverdb.$V.o
SOURCE2=ezmmsserverdb.$V.c
SOURCEPC=ezmmsserverdb.$V.pc
OINCLUDEDIR=${ORACLE_HOME}/precomp/public
LIBLIST=-lezdebug_util -lezsigutil -leztaskutil -lezcfg_util -lclntsh -lezchanneltools -lezdbutil -lezpadssutil -lezsecurityutil -leztokenutil -lezchannelutil -lezinstprofileutil -lezsecurityutil -lezmmsutil -lezamount_util

INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE} ${OBJFILE1} ${OBJFILE2}
			g++ ${OBJFILE} ${OBJFILE1} ${OBJFILE2} ${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

${OBJFILE1}	:	${SOURCE1}
			g++ -c ${SOURCE1} -I${INCLUDEDIR}

${OBJFILE2}	:	${SOURCEPC}
			proc ${SOURCEPC}
			cc -c ${SOURCE2} -I${INCLUDEDIR} -I${OINCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
			rm tp*
				
