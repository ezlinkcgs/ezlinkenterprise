BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib -L${ORACLE_HOME}/lib
BINARY=EzAgentTMSDriver_06JUL21
OBJFILE=ezagenttmsdriver.o
SOURCE=ezagenttmsdriver.cpp
OBJFILE1=ezagentpos8583.o
SOURCE3=ezagenttmsdrivertemplate.cpp
OBJFILE3=ezagenttmsdrivertemplate.o
SOURCE1=ezagentpos8583.cpp
OBJFILEDB=ezagenttmsdriverodbc.o
SOURCEDB=ezagenttmsdriverodbc.cpp
OINCLUDEDIR=${ORACLE_HOME}/precomp/public
#LIBLIST=-lezdebug_util -lezcfg_util -lezsigutil -lclntsh -leztaskutil -lezchannelutil -lezfmt_util -leziso8583util -lezdatetimeutil -lezchanneltools -lezagenttmsdriverutil -leztokenutil -lezsecurityutil -leztxnsequtil -lezsequtil -lezpadssutil -lezdbutil -lezagentmmsutil -leztmstxnmemoryutil -lezemvutil -lezagentmmsdbutil -lezamount_util -lezschemainfoutil
LIBLIST=-lezdebug_util -lezcfg_util -lezsigutil -lodbc -leztaskutil -lezchannelutil -lezfmt_util -leziso8583util -lezdatetimeutil -lezchanneltools -lezagenttmsdriverutil -leztmstxnmemoryutil -leztokenutil -lezsecurityutil -leztxnsequtil -lezsequtil -lezpadssutil -lezodbcutil -lezagentmmsutil -lezemvutil -lezagentmmsdbutil -lezamount_util
INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE} ${OBJFILE1} ${OBJFILE3} ${OBJFILEDB}
			g++ ${OBJFILE} ${OBJFILE1} ${OBJFILE3} ${OBJFILEDB} -L${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

${OBJFILE1}	:	${SOURCE1}
			g++ -c ${SOURCE1} -I${INCLUDEDIR}
			
${OBJFILE3}	:	${SOURCE3}
			g++ -c ${SOURCE3} -I${INCLUDEDIR}

${OBJFILEDB}	:	${SOURCEDB}
			g++ -c ${SOURCEDB} -I${INCLUDEDIR}

			
install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
			rm *.c
			rm *.lis
			rm tp*
				
