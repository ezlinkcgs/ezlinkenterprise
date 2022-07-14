BINDIR=${EZDIR_HOME}/bin
LIBDIR=-L${EZDIR_HOME}/lib -L${ORACLE_HOME}/lib
BINARY=ezexport
OBJFILE=ezexportutil.o
SOURCE=ezexportutil.cpp
OBJFILE1=ezexportutildb.o
SOURCE1=ezexportutildb.c
SOURCEPC=ezexportutildb.pc
LIBLIST=-lezdebug_util -lezdbutil -lclntsh -lezchanneltools -lezdatetimeutil
INCLUDEDIR=${EZDIR_HOME}/include
OINCLUDEDIR=${ORACLE_HOME}/precomp/public

${BINARY}	:	${OBJFILE} ${OBJFILE1}
			g++ ${OBJFILE} ${OBJFILE1} ${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}		:	${SOURCE}
					g++ -c ${SOURCE} -I${INCLUDEDIR}

${OBJFILE1}		:	${SOURCEPC}
					proc ${SOURCEPC}
					cc -c ${SOURCE1} -I${INCLUDEDIR} -I${OINCLUDEDIR}
			
install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
			rm tp*
			rm *.lis
				

