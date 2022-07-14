BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib
OLIBDIR=${ORACLE_HOME}/lib

BINARY=EzSecurityMgr

OBJFILE=ezsecuritymgr.o
SOURCE=ezsecuritymgr.cpp

UTILOBJFILE=ezsecuritymgrutil.o
UTILSOURCE=ezsecuritymgrutil.cpp

#PROCSOURCE=ezsecuritymgrdb.pc
DBOBJFILE=ezsecuritymgrodbc.o
DBSOURCE=ezsecuritymgrodbc.cpp

LIBLIST=-lezdebug_util -lezsigutil -leztaskutil -lezchannelutil -lezcfg_util -lezodbcutil -lezchanneltools -lezsecuritydriverutil -lezinstprofileutil

INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE} ${UTILOBJFILE}  ${DBOBJFILE}
			g++ ${OBJFILE} ${UTILOBJFILE} ${DBOBJFILE} -L${LIBDIR} ${LIBLIST} -L${OLIBDIR} -lodbc -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

${UTILOBJFILE}	:	${UTILSOURCE}
			g++ -c ${UTILSOURCE} -I${INCLUDEDIR}
			

${DBOBJFILE}	:	${DBSOURCE}
			g++ -c ${DBSOURCE} -I${INCLUDEDIR}
			
install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
			rm tp*
				
