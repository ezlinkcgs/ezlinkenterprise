BINDIR=${EZDIR_HOME}/bin
LIBDIR=-L${EZDIR_HOME}/lib -L${ORACLE_HOME}/lib
BINARY=ezbusdaycmd
OBJFILE=ezbusdaycmd.o
SOURCE=ezbusdaycmd.cpp
#OBJFILE2=ezbusdaycmddb.o
#SOURCE2=ezbusdaycmddb.c
#SOURCEPC=ezbusdaycmddb.pc
LIBLIST=-lezdebug_util -lezodbcutil -lodbc -lezcmdutil -lezbusdayutil -lezchanneltools
INCLUDEDIR=${EZDIR_HOME}/include
OINCLUDEDIR=${ORACLE_HOME}/precomp/public

${BINARY}	:	${OBJFILE}
			g++ ${OBJFILE} ${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}		:	${SOURCE}
					g++ -c ${SOURCE} -I${INCLUDEDIR}

${OBJFILE2}		:	${SOURCEPC}
					proc ${SOURCEPC}
					cc -c ${SOURCE2} -I${INCLUDEDIR} -I${OINCLUDEDIR}
			
install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
			rm tp*
				
