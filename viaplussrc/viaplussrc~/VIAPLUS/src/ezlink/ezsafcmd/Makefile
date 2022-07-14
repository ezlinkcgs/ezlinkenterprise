BINDIR=${EZDIR_HOME}/bin
LIBDIR=-L${EZDIR_HOME}/lib -L${ORACLE_HOME}/lib
BINARY=ezsafcmd
OBJFILE=ezsafcmd.o
SOURCE=ezsafcmd.cpp
OBJFILE2=ezsafcmddb.o
SOURCE2=ezsafcmddb.c
SOURCEPC=ezsafcmddb.pc
LIBLIST=-lezdebug_util -lezcfg_util -lezdbutil -lclntsh -lezcmdutil -lezsafformatutil

INCLUDEDIR=${EZDIR_HOME}/include
OINCLUDEDIR=${ORACLE_HOME}/precomp/public

${BINARY}	:	${OBJFILE} ${OBJFILE2}
			g++ ${OBJFILE} ${OBJFILE2} ${LIBDIR} ${LIBLIST} -o ${BINARY}	

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
				
