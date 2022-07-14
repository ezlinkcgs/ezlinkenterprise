BINDIR=${EZDIR_HOME}/bin
LIBDIR=-L${EZDIR_HOME}/lib -L${ORACLE_HOME}/lib
BINARY=ezalertcmd
OBJFILE=ezalertcmd.o
SOURCE=ezalertcmd.cpp
OBJFILE2=ezalertcmddb.o
SOURCE2=ezalertcmddb.c
SOURCEPC=ezalertcmddb.pc
LIBLIST=-lezdebug_util -lezdbutil -lclntsh -lezcmdutil -lezalertmemutil -lezchlocateutil -lezsequtil -leztokenutil

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
				
