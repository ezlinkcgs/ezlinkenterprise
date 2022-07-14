BINDIR=${EZDIR_HOME}/bin
LIBDIR=-L${EZDIR_HOME}/lib -L${ORACLE_HOME}/lib
BINARY=EzEchoMgr
OBJFILE=ezechomanager.o
SOURCE=ezechomanager.cpp
OBJFILE1=ezechointervaltable.o
SOURCE1=ezechointervaltable.cpp
#OBJFILE2=ezechomanagerodbc.o
#SOURCE2=ezechomanagerodbc.cpp
#SOURCEPC=ezechomanagerdb.pc
#OINCLUDEDIR=${ORACLE_HOME}/precomp/public
LIBLIST=-lezdebug_util -lezsigutil -leztaskutil -lezchannelutil -lezcfg_util -lezcommutil -leznetworkutil -lezodbcutil -lezdatetimeutil -lezechoutil -lodbc
INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE1} ${OBJFILE} 
			g++ ${OBJFILE1} ${OBJFILE} ${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

${OBJFILE1}	:	${SOURCE1}
			g++ -c ${SOURCE1} -I${INCLUDEDIR}
			
#${OBJFILE2}	:	${SOURCE2}
#			proc ${SOURCEPC}
#			g++ -c ${SOURCE2} -I${INCLUDEDIR}
			
			
install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
			rm tp*
				
