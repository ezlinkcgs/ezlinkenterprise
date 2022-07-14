BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib -L${ORACLE_HOME}/lib
BINARY=EzPOSDriver
OBJFILE=ezposdriver.o
SOURCE=ezposdriver.cpp
OBJFILE1=ezhypercomutil.o
SOURCE1=ezhypercomutil.cpp
OBJFILEDB=ezposdriverdb.o
SOURCEDB=ezposdriverdb.c
SOURCEPC=ezposdriverdb.pc
OINCLUDEDIR=${ORACLE_HOME}/precomp/public
LIBLIST=-lezdebug_util -lezcfg_util -lezsigutil -leztaskutil -lezchannelutil -lezfmt_util -leziso8583util -lezdatetimeutil -lezchanneltools -lezposdriverutil -lclntsh -lezdbutil -lezsecurityutil -leztokenutil -lezpostxnmemoryutil -leztxnsequtil -lezsequtil -lezpadssutil
INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE} ${OBJFILE1} ${OBJFILEDB}
			g++ ${OBJFILE} ${OBJFILE1} ${OBJFILEDB} -L${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

${OBJFILE1}	:	${SOURCE1}
			g++ -c ${SOURCE1} -I${INCLUDEDIR}
			
${OBJFILEDB}     :       ${SOURCEPC}
			proc ${SOURCEPC}
			cc -c ${SOURCEDB} -I${INCLUDEDIR} -I${OINCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
			rm *.c
			rm *.lis
			rm tp*
				
