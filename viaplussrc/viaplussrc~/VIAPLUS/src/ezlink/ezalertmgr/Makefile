BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib
BINARY=EzAlertMgr
FNAME=ezalertmgr

LIBLIST=-lezdebug_util -lezsigutil -leztaskutil -lezchannelutil -lezcfg_util -lezdbutil -lezatmutil -leznetworkutil -lezdatetimeutil -leztokenutil -lezalertmemutil -lezsequtil
INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${FNAME}.o ${FNAME}db.o ${FNAME}util.o 
				g++ ${FNAME}.o ${FNAME}db.o ${FNAME}util.o -L${LIBDIR} ${LIBLIST} -L${ORACLE_HOME}/lib -lclntsh -o ${BINARY}	

${FNAME}.o	:	${FNAME}.cpp
			g++ -c ${FNAME}.cpp -I${INCLUDEDIR}

${FNAME}util.o	:	${FNAME}util.cpp
			g++ -c ${FNAME}util.cpp -I${INCLUDEDIR}
			
${FNAME}db.o	:	${FNAME}db.pc
			proc ${FNAME}db.pc
			cc -c -fPIC ${FNAME}db.c -I${ORACLE_HOME}/precomp/public -I${INCLUDEDIR}

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
			rm tp*
				

