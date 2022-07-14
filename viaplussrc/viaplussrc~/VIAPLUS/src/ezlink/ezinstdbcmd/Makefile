BINDIR=${EZDIR_HOME}/bin
LIBDIR=-L${EZDIR_HOME}/lib -L${ORACLE_HOME}/lib
BINARY=ezinstdbcmd
OBJFILE=ezinstdbcmd.o
SOURCE=ezinstdbcmd.cpp
OBJFILE1=ezinstdbodbc.o
SOURCE1=ezinstdbodbc.cpp
LIBLIST=-lezdebug_util -lezodbcutil -lodbc -lezcmdutil -lezinstroutetypeutil -lezinstprofileutil -lezinstselectutil -lezbinselectutil -lezbinprofileutil -lezbranchprofileutil -leznetworkselectutil -lezdevicetypemaputil -leznetworkutil -lezauthpropertyutil -lezchannelpropertyutil -leztxnrefselectutil -leztxnrouteinfoutil -leztxnrouteselectutil -lezinboundmsgpropertyutil -lezeventpropertyutil -lezmsgtypepropertyutil -lezmsgtranslateutil -lezdatetimeutil -leztxnsequtil -lezsequtil -leztxnmsgorderutil -lezinstextntwkprofileutil -lezextntwkprofileutil -lezsafpropertyutil
INCLUDEDIR=${EZDIR_HOME}/include
#OINCLUDEDIR=${ORACLE_HOME}/precomp/public

${BINARY}	:	${OBJFILE} ${OBJFILE1} 
			g++ ${OBJFILE} ${OBJFILE1} ${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

${OBJFILE1}	:	${SOURCE1}
			g++ -c ${SOURCE1} -I${INCLUDEDIR}
			
install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
			rm tp*
				
