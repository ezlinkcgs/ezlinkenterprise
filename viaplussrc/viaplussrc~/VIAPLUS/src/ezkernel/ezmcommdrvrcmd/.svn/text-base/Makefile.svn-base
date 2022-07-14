BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib

BINARY=ezmcommdrvrcmd

OBJFILE=ezmcommdrvrcmd.o
SOURCE=ezmcommdrvrcmd.cpp

LIBLIST=-lezdebug_util -lezcmdutil -lezchlocateutil -lezcfg_util -lezchanneltools 

INCLUDEDIR=${EZDIR_HOME}/include


${BINARY}	:	${OBJFILE}  
			g++ ${OBJFILE} -L${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE}	:	${SOURCE}
			g++ -g -c ${SOURCE} -I${INCLUDEDIR}
			
install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
			rm tp*
