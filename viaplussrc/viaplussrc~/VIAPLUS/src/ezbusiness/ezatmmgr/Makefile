BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib
OLIBDIR=${ORACLE_HOME}/lib
BINARY=EzAtmMgr
OBJFILE=ezatmmgr.o
SOURCE=ezatmmgr.cpp
UTILOBJFILE=ezatmmgrutil.o
UTILSOURCE=ezatmmgrutil.cpp
DBOBJFILE=ezatmmgrodbc.o
DBSOURCE=ezatmmgrodbc.cpp
#PROCSOURCE=ezatmmgrdb.pc
#COBJFILE=ezatmmgrdb.o
#CSOURCE=ezatmmgrdb.c

LIBLIST=-lezdebug_util -lezsigutil -leztaskutil -lezchannelutil -lezcfg_util -lezodbcutil -lezdatetimeutil -lezchanneltools -lpthread -lezinstprofileutil -lezlicenseutil -lezsecuritydriverutil
INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE} ${UTILOBJFILE} ${DBOBJFILE}
			g++ ${OBJFILE} ${UTILOBJFILE} ${DBOBJFILE} -L${LIBDIR} ${LIBLIST} -L${OLIBDIR} -lodbc -o ${BINARY} 	

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR} 

${UTILOBJFILE}	:	${UTILSOURCE}
			g++ -c ${UTILSOURCE} -I${INCLUDEDIR}

${DBOBJFILE}	:	${DBSOURCE}
			g++ -c ${DBSOURCE} -I${INCLUDEDIR}			

#${COBJFILE}	:	${PROCSOURCE}
#			proc ${PROCSOURCE}
#			cc -c ${CSOURCE} -I${ORACLE_HOME}/precomp/public -I${INCLUDEDIR} 
			
install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
			rm tp*
				
