BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib -L${ORACLE_HOME}/lib
BINARY=EzTMSDriver
OBJFILE=eztmsdriver.o
SOURCE=eztmsdriver.cpp
OBJFILEDB=eztmsdriverodbc.o
SOURCEDB=eztmsdriverodbc.cpp
OBJFILE1=ezhypercomutil.o
SOURCE1=ezhypercomutil.cpp
OBJFILE2=ezcastles8583.o
SOURCE2=ezcastles8583.cpp
#SOURCEPC=eztmsdriverdb.pc
#OINCLUDEDIR=${ORACLE_HOME}/precomp/public
LIBLIST=-lezdebug_util -lezcfg_util -lezsigutil -lodbc -leztaskutil -lezchannelutil -lezfmt_util -leziso8583util -lezdatetimeutil -lezchanneltools -leztmsdriverutil -leztokenutil -lezsecurityutil -leztxnsequtil -lezsequtil -lezpadssutil -lezodbcutil -lezmmsutil -leztmstxnmemoryutil
INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE} ${OBJFILEDB} ${OBJFILE1} ${OBJFILE2}
			g++ ${OBJFILE} ${OBJFILEDB} ${OBJFILE1} ${OBJFILE2} -L${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

${OBJFILEDB}	:	${SOURCEDB}
			g++ -c ${SOURCEDB} -I${INCLUDEDIR}

${OBJFILE1}	:	${SOURCE1}
			g++ -c ${SOURCE1} -I${INCLUDEDIR}

${OBJFILE2}	:	${SOURCE2}
			g++ -c ${SOURCE2} -I${INCLUDEDIR}

#${OBJFILE2}	:	${SOURCEPC}
#			proc ${SOURCEPC}
#			cc -c ${SOURCE2} -I${INCLUDEDIR} -I${OINCLUDEDIR}

			
install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
			rm *.c
			rm *.lis
			rm tp*
				
