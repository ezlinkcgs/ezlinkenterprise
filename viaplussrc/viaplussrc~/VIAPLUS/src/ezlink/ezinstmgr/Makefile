BINDIR=${EZDIR_HOME}/bin
LIBDIR=-L${EZDIR_HOME}/lib -L${ORACLE_HOME}/lib
BINARY=EzInstMgr
OBJFILE=ezinstmgr.o
SOURCE=ezinstmgr.cpp
OBJFILE1=ezinstmgrutil.o
SOURCE1=ezinstmgrutil.cpp
OBJFILE2=ezinstmgrodbc.o
SOURCE2=ezinstmgrodbc.cpp
#OINCLUDEDIR=${ORACLE_HOME}/precomp/public
LIBLIST=-lezdebug_util -lezsigutil -leztaskutil -lezcfg_util -lodbc -lezchanneltools -lezodbcutil -lezlicenseutil

INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE} ${OBJFILE1} ${OBJFILE2}
			g++ ${OBJFILE} ${OBJFILE1} ${OBJFILE2} ${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

${OBJFILE1}	:	${SOURCE1}
			g++ -c ${SOURCE1} -I${INCLUDEDIR}

${OBJFILE2}     :	${SOURCE2}
			g++ -c ${SOURCE2} -I${INCLUDEDIR} 

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
			rm tp*
				
