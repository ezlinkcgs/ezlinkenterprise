BINDIR=${EZDIR_HOME}/bin
LIBDIR=-L${EZDIR_HOME}/lib -L${ORACLE_HOME}/lib
BINARY=EzSafWriter
OBJFILE=ezsafwriter.o
SOURCE=ezsafwriter.cpp
#OBJFILE2=ezsafwriterdb.o
#SOURCE2=ezsafwriterdb.c
#SOURCEPC=ezsafwriterdb.pc
LIBLIST=-lezdebug_util -lezsigutil -leztaskutil -lezchannelutil -lezcfg_util -lezodbcutil -lpthread -lodbc -lezreplayutil -lezchanneltools -leztxnrefselectutil -leztxnsequtil -lezdatetimeutil -lezsequtil -leznetworkutil -lezsafpropertyutil -lezsafformatutil -leztxnlogutil -leztxnmsgorderutil -lezpadssutil -lezinstprofileutil
INCLUDEDIR=${EZDIR_HOME}/include
#OINCLUDEDIR=${ORACLE_HOME}/precomp/public

${BINARY}	:	${OBJFILE} 
			g++ ${OBJFILE} ${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}		:	${SOURCE}
					g++ -c ${SOURCE} -I${INCLUDEDIR}

#${OBJFILE2}		:	${SOURCEPC}
#					proc ${SOURCEPC}
#					cc -c ${SOURCE2} -I${INCLUDEDIR} -I${OINCLUDEDIR}
			
install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
			rm tp*
				
