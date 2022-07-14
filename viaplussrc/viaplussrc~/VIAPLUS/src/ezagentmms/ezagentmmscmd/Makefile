BINDIR=${EZDIR_HOME}/bin
LIBDIR=-L${EZDIR_HOME}/lib -L${ORACLE_HOME}/lib
BINARY=ezagentmmscmd_21JAN21
FILENAME=ezagentmmscmd
V=0.000
OBJFILE=${FILENAME}.$V.o
SOURCE=${FILENAME}.$V.cpp

#LIBLIST=-lezdebug_util -lezcfg_util -lclntsh -lezdbutil -lezcmdutil -lezmmsutil -leztokenutil -leztabtoshmutil -lezprepaidutil -leztmsdriverutil
LIBLIST=-lezdebug_util -lezcfg_util -lclntsh -lezdbutil -lezcmdutil -lezagentmmsutil -leztokenutil -leztabtoshmutil -lezprepaidutil -lezagenttmsdriverutil

INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE}
			g++ ${OBJFILE} ${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
			rm tp*
				
