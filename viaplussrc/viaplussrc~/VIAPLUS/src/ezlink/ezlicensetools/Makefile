genserverkey:	genserverkey.o
				g++ genserverkey.o -o  genserverkey
				
genserverkey.o:	genserverkey.cpp
				g++ -c genserverkey.cpp
				
encryptfile:	encryptlicensefile.o
				g++ encryptlicensefile.o -o  encryptfile
				
encryptlicensefile.o:	encryptlicensefile.cpp
				g++ -c encryptlicensefile.cpp
				
clean		:
			rm *.o
			rm tp*
			
install	:
	mv genserverkey ${EZDIR_HOME}/bin