BINDIR=${EZDIR_HOME}/bin
LIBDIR=${EZDIR_HOME}/lib

BINARY=EzGUIController

OBJFILE1=ezguicontroller.o
SOURCE1=ezguicontroller.cpp

OBJFILE2=ezguinetworkrequest.o
SOURCE2=ezguinetworkrequest.cpp

OBJFILE3=ezguireplayrequest.o	
SOURCE3=ezguireplayrequest.cpp

OBJFILE4=ezguiechorequest.o	
SOURCE4=ezguiechorequest.cpp

OBJFILE5=ezguiportrequest.o	
SOURCE5=ezguiportrequest.cpp

OBJFILE6=ezguitaskrequest.o	
SOURCE6=ezguitaskrequest.cpp

OBJFILE7=ezguisecurityrequest.o	
SOURCE7=ezguisecurityrequest.cpp

OBJFILE8=ezguiatmrequest.o	
SOURCE8=ezguiatmrequest.cpp

OBJFILE9=ezguibranchrequest.o	
SOURCE9=ezguibranchrequest.cpp

OBJFILE10=ezguibinrequest.o	
SOURCE10=ezguibinrequest.cpp

OBJFILE11=ezguiinstrequest.o	
SOURCE11=ezguiinstrequest.cpp

OBJFILE12=ezguiinstselectrequest.o	
SOURCE12=ezguiinstselectrequest.cpp

OBJFILE13=ezguinetworkselectrequest.o	
SOURCE13=ezguinetworkselectrequest.cpp

OBJFILE14=ezguifitrequest.o	
SOURCE14=ezguifitrequest.cpp

OBJFILE15=ezguichannelrequest.o	
SOURCE15=ezguichannelrequest.cpp

OBJFILE16=ezguiposrequest.o	
SOURCE16=ezguiposrequest.cpp

OBJFILE17=ezguibinselectrequest.o	
SOURCE17=ezguibinselectrequest.cpp

OBJFILE18=ezguibusdayrequest.o
SOURCE18=ezguibusdayrequest.cpp

OBJFILE19=ezguialertrequest.o
SOURCE19=ezguialertrequest.cpp

OBJFILEDB=ezguicontrollerodbc.o
SOURCEDB=ezguicontrollerodbc.cpp
#SOURCEPC=ezguicontrollerdb.pc

LIBLIST=-lezdebug_util -lezcfg_util -lezsigutil -lezchannelutil -leztaskutil -lezchanneltools -lezcommutil -lezmsgqutil -lezodbcutil -lezatmutil -lodbc -lezdatetimeutil -lezinstprofileutil -lezinstselectutil -lezbinprofileutil -lezbranchprofileutil -leznetworkselectutil -lezdevicetypemaputil -leznetworkutil -lezreplayutil -lezechoutil -lezbusdayutil -lezdatetimeutil -leztokenutil -lezsecuritydriverutil -lezatmmemutil -lezbinselectutil -lezbusdayutil -lezalertmemutil -lezsequtil

INCLUDEDIR=${EZDIR_HOME}/include
OINCLUDEDIR=${ORACLE_HOME}/precomp/public

#${BINARY}	:	${OBJFILE1} ${OBJFILE2} ${OBJFILE3} ${OBJFILE4} ${OBJFILE5} ${OBJFILE6} ${OBJFILE7} ${OBJFILE8} ${OBJFILE9} ${OBJFILE10} ${OBJFILE11} ${OBJFILE12} ${OBJFILE13} ${OBJFILE14} ${OBJFILE15} ${OBJFILE16} ${OBJFILE17} ${OBJFILE18} ${OBJFILE19} ${OBJFILEDB} 
#			g++ ${OBJFILE1} ${OBJFILE2} ${OBJFILE3} ${OBJFILE4} ${OBJFILE5} ${OBJFILE6} ${OBJFILE7} ${OBJFILE8} ${OBJFILE9} ${OBJFILE10} ${OBJFILE11} ${OBJFILE12} ${OBJFILE13} ${OBJFILE14} ${OBJFILE15} ${OBJFILE16} ${OBJFILE17} ${OBJFILE18} ${OBJFILE19} ${OBJFILEDB} -L${LIBDIR} ${LIBLIST} -o ${BINARY}	

${BINARY}	:	${OBJFILE1} ${OBJFILE2} ${OBJFILE3} ${OBJFILE4} ${OBJFILE5} ${OBJFILE6} ${OBJFILE7} ${OBJFILE8} ${OBJFILE9} ${OBJFILE10} ${OBJFILE11} ${OBJFILE12} ${OBJFILE13} ${OBJFILE14} ${OBJFILE15} ${OBJFILE17} ${OBJFILE18} ${OBJFILEDB} 
			g++ ${OBJFILE1} ${OBJFILE2} ${OBJFILE3} ${OBJFILE4} ${OBJFILE5} ${OBJFILE6} ${OBJFILE7} ${OBJFILE8} ${OBJFILE9} ${OBJFILE10} ${OBJFILE11} ${OBJFILE12} ${OBJFILE13} ${OBJFILE14} ${OBJFILE15} ${OBJFILE17} ${OBJFILE18} ${OBJFILEDB} -L${LIBDIR} ${LIBLIST} -o ${BINARY}	

${OBJFILE1}	:	${SOURCE1}
			g++ -g -c ${SOURCE1} -I${INCLUDEDIR}
			
${OBJFILE2}	:	${SOURCE2}
			g++ -g -c ${SOURCE2} -I${INCLUDEDIR}
			
${OBJFILE3}	:	${SOURCE3}
			g++ -g -c ${SOURCE3} -I${INCLUDEDIR}
			
${OBJFILE4}	:	${SOURCE4}
			g++ -g -c ${SOURCE4} -I${INCLUDEDIR}
			
${OBJFILE5}	:	${SOURCE5}
			g++ -g -c ${SOURCE5} -I${INCLUDEDIR}
			
${OBJFILE6}	:	${SOURCE6}
			g++ -g -c ${SOURCE6} -I${INCLUDEDIR}
			
${OBJFILE7}	:	${SOURCE7}
			g++ -g -c ${SOURCE7} -I${INCLUDEDIR}
			
${OBJFILE8}	:	${SOURCE8}
			g++ -g -c ${SOURCE8} -I${INCLUDEDIR}
			
${OBJFILE9}	:	${SOURCE9}
			g++ -g -c ${SOURCE9} -I${INCLUDEDIR}

${OBJFILE10}	:	${SOURCE10}
			g++ -g -c ${SOURCE10} -I${INCLUDEDIR}
			
${OBJFILE11}	:	${SOURCE11}
			g++ -g -c ${SOURCE11} -I${INCLUDEDIR}

${OBJFILE12}	:	${SOURCE12}
			g++ -g -c ${SOURCE12} -I${INCLUDEDIR}

${OBJFILE13}	:	${SOURCE13}
			g++ -g -c ${SOURCE13} -I${INCLUDEDIR}
			
${OBJFILE14}	:	${SOURCE14}
			g++ -g -c ${SOURCE14} -I${INCLUDEDIR}
			
${OBJFILE15}	:	${SOURCE15}
			g++ -g -c ${SOURCE15} -I${INCLUDEDIR}

${OBJFILE16}	:	${SOURCE16}
			g++ -g -c ${SOURCE16} -I${INCLUDEDIR}
			
${OBJFILE17}	:	${SOURCE17}
			g++ -g -c ${SOURCE17} -I${INCLUDEDIR}
			
${OBJFILE18}	:	${SOURCE18}
			g++ -g -c ${SOURCE18} -I${INCLUDEDIR}

${OBJFILE19}	:	${SOURCE19}
			g++ -g -c ${SOURCE19} -I${INCLUDEDIR}


${OBJFILEDB}     :       ${SOURCEDB}
#			proc ${SOURCEPC}
			g++ -c ${SOURCEDB} -I${INCLUDEDIR} 

install		:
			mv ${BINARY} ${BINDIR}

clean		:
			rm *.o
			rm tp*
