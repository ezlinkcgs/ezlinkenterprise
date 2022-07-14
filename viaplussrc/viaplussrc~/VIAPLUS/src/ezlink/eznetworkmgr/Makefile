BINDIR=${EZDIR_HOME}/bin
LIBDIR=-L${EZDIR_HOME}/lib -L${ORACLE_HOME}/lib
BINARY=EzNetworkMgr
OBJFILE=eznetworkmgr.o
SOURCE=eznetworkmgr.cpp
OBJFILE1=eznetworkmgrutil.o
SOURCE1=eznetworkmgrutil.cpp
OBJFILE2=eznetworkmgrodbc.o
SOURCE2=eznetworkmgrodbc.cpp
#SOURCEPC=eznetworkmgrdb.pc
#OINCLUDEDIR=${ORACLE_HOME}/precomp/public
LIBLIST=-lezdebug_util -lezsigutil -leztaskutil -lezchannelutil -lezcfg_util -lpthread -lodbc -lezdatetimeutil -lezchanneltools -lezsequtil -lezodbcutil -lezsecurityutil

INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE} ${OBJFILE1} ${OBJFILE2}
			g++ ${OBJFILE} ${OBJFILE1} ${OBJFILE2} ${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

${OBJFILE1}	:	${SOURCE1}
			g++ -c ${SOURCE1} -I${INCLUDEDIR}

${OBJFILE2}	:	${SOURCE2}
#			proc ${SOURCEPC}
			g++ -c ${SOURCE2} -I${INCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
			rm tp*
				
