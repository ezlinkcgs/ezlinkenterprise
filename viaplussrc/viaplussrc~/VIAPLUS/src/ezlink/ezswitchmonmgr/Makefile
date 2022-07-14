BINDIR=${EZDIR_HOME}/bin
LIBDIR=-L${EZDIR_HOME}/lib -L${ORACLE_HOME}/lib
BINARY=EzSwitchMonMgr
OBJFILE=ezswitchmonmgr.o
SOURCE=ezswitchmonmgr.cpp

LIBLIST=-lezdebug_util -lezsigutil -leztaskutil -lezcfg_util -lclntsh -lezchanneltools  -lezchannelutil 

INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE} 
			g++ ${OBJFILE}  ${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}


install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
			rm tp*
				
