BINDIR=${EZDIR_HOME}/bin
LIBDIR=-L${EZDIR_HOME}/lib -L${ORACLE_HOME}/lib
BINARY=ezechocmd
OBJFILE=ezechocmd.o
SOURCE=ezechocmd.cpp
#OBJFILE2=ezechocmddb.o
#SOURCE2=ezechocmddb.c
#SOURCEPC=ezechocmddb.pc
LIBLIST=-lezdebug_util -lezcfg_util -lezodbcutil -lodbc -lezchanneltools -lezcmdutil
INCLUDEDIR=${EZDIR_HOME}/include
#OINCLUDEDIR=${ORACLE_HOME}/precomp/public

${BINARY}	:	${OBJFILE} 
			g++ ${OBJFILE}  ${LIBDIR} ${LIBLIST} -o ${BINARY}	

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
				
