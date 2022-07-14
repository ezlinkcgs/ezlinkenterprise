
BINDIR=${EZDIR_HOME}/bin
LIBDIR=-L${EZDIR_HOME}/lib -L${ORACLE_HOME}/lib
BINARY=ezreplaycmd
OBJFILE=ezreplaycmd.o
SOURCE=ezreplaycmd.cpp
#OBJFILE2=ezreplaycmddb.o
#SOURCE2=ezreplaycmddb.c
#SOURCEPC=ezreplaycmddb.pc
LIBLIST=-lezdebug_util -lezchannelutil -lezcfg_util -lezodbcutil -lodbc -lezchanneltools -lezcmdutil
INCLUDEDIR=${EZDIR_HOME}/include
OINCLUDEDIR=${ORACLE_HOME}/precomp/public

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
				
