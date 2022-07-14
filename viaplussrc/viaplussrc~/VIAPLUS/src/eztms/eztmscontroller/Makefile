BINDIR=${EZDIR_HOME}/bin
LIBDIR=-L${EZDIR_HOME}/lib -L${ORACLE_HOME}/lib
BINARY=EzTMSController
OBJFILE=eztmscontroller.o
SOURCE=eztmscontroller.cpp
OBJFILE2=eztmscontrollerodbc.o
SOURCE2=eztmscontrollerodbc.cpp
#SOURCEPC=eztmscontrollerdb.pc
#OINCLUDEDIR=${ORACLE_HOME}/precomp/public
LIBLIST=-lezdebug_util -lezsigutil -leztaskutil -lezcfg_util -lodbc -lezchanneltools -lezodbcutil -lezchannelutil -leztmsdriverutil -lezdatetimeutil -leztokenutil -lezmmsutil -lezinstprofileutil

INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE} ${OBJFILE2}
			g++ ${OBJFILE} ${OBJFILE2} ${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

${OBJFILE2}	:	${SOURCE2}
			g++ -c ${SOURCE2} -I${INCLUDEDIR}
			
#${OBJFILE2}	:	${SOURCEPC}
#			proc ${SOURCEPC}
#			cc -c ${SOURCE2} -I${INCLUDEDIR} -I${OINCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
			rm tp*
				
