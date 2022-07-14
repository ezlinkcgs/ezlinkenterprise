BINDIR=${EZDIR_HOME}/bin
LIBDIR=-L${EZDIR_HOME}/lib -L${ORACLE_HOME}/lib
BINARY=EzAGENTMMSMgr_06JUL21
V=0.000
OBJFILE=ezagentmmsmgr.$V.o
SOURCE=ezagentmmsmgr.$V.cpp
OBJFILE1=ezagentmmsmgrutil.$V.o
SOURCE1=ezagentmmsmgrutil.$V.cpp
OBJFILE2=ezagentmmsmgrodbcutil.$V.o
SOURCE2=ezagentmmsmgrodbcutil.$V.cpp
#SOURCEPC=ezagentmmsmgrdb.$V.pc
OINCLUDEDIR=${ORACLE_HOME}/precomp/public
#LIBLIST=-lezdebug_util -lezsigutil -leztaskutil -lezcfg_util -lclntsh -lezchanneltools -lezdbutil -lezschemainfoutil
LIBLIST=-lezdebug_util -lezsigutil -leztaskutil -lezcfg_util -lodbc -lezchanneltools -lezodbcutil
INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE} ${OBJFILE1} ${OBJFILE2}
			g++ ${OBJFILE} ${OBJFILE1} ${OBJFILE2} ${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

${OBJFILE1}	:	${SOURCE1}
			g++ -c ${SOURCE1} -I${INCLUDEDIR}

${OBJFILE2}	:	${SOURCE2}
			g++ -c ${SOURCE2} -I${INCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
			rm tp*
				
