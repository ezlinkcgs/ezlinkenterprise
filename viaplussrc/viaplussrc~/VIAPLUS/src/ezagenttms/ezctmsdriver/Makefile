BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib -L${ORACLE_HOME}/lib
#BINARY=EzCTMSDriver_CNP_REV_18OCT20
BINARY=EzCTMSDriver_17JAN21_2
OBJFILE=eztmsdriver.o
SOURCE=eztmsdriver.cpp
OBJFILE1=ezcastles8583.o
SOURCE3=eztmsdrivertemplate.cpp
OBJFILE3=eztmsdrivertemplate.o
SOURCE1=ezcastles8583.cpp
OBJFILE2=eztmsdriverdb.o
SOURCE2=eztmsdriverdb.c
SOURCEPC=eztmsdriverdb.pc
OINCLUDEDIR=${ORACLE_HOME}/precomp/public
LIBLIST=-lezdebug_util -lezcfg_util -lezsigutil -lclntsh -leztaskutil -lezchannelutil -lezfmt_util -leziso8583util -lezdatetimeutil -lezchanneltools -leztmsdriverutil -leztokenutil -lezsecurityutil -leztxnsequtil -lezsequtil -lezpadssutil -lezdbutil -lezmmsutil -leztmstxnmemoryutil -lezemvutil -lezmmsdbutil -lezamount_util -lezschemainfoutil
INCLUDEDIR=${EZDIR_HOME}/include

${BINARY}	:	${OBJFILE} ${OBJFILE1} ${OBJFILE3} ${OBJFILE2}
			g++ ${OBJFILE} ${OBJFILE1} ${OBJFILE3} ${OBJFILE2} -L${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -c ${SOURCE} -I${INCLUDEDIR}

${OBJFILE1}	:	${SOURCE1}
			g++ -c ${SOURCE1} -I${INCLUDEDIR}
			
${OBJFILE3}	:	${SOURCE3}
			g++ -c ${SOURCE3} -I${INCLUDEDIR}

${OBJFILE2}	:	${SOURCEPC}
			proc ${SOURCEPC}
			cc -c ${SOURCE2} -I${INCLUDEDIR} -I${OINCLUDEDIR}

			
install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
			rm *.c
			rm *.lis
			rm tp*
				
