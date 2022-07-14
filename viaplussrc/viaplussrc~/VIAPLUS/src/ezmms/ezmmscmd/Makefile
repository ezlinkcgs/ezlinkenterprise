BINDIR=${EZDIR_HOME}/bin
LIBDIR=-L${EZDIR_HOME}/lib
BINARY=ezmmscmd
FILENAME=ezmmscmd
OBJFILE=${FILENAME}.o
SOURCE=${FILENAME}.cpp
OBJFILE2=${FILENAME}odbc.o
SOURCE2=${FILENAME}odbc.cpp
#SOURCEPC=${FILENAME}db.pc
OINCLUDEDIR=${ORACLE_HOME}/precomp/public
LIBLIST=-lezdebug_util -lezcfg_util -lodbc -lezodbcutil -lezcmdutil -lezmmsutil -leztokenutil

INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE}
			g++ ${OBJFILE} ${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

#${OBJFILE2}	:	${SOURCEPC}
#			proc ${SOURCEPC}
#			cc -c ${SOURCE2} -I${INCLUDEDIR} -I${OINCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
			rm tp*
				
