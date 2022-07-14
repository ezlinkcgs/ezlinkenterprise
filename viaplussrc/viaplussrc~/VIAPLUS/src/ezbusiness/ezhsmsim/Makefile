
ezhsmsim:	ezhsmsim.o ezdebugutil.o ezcfg_util.o
		g++ ezhsmsim.o ezdebugutil.o ezcfg_util.o -o ezhsmsim

ezhsmsim.o:	ezhsmsim.h
		g++ -c ezhsmsim.cpp

ezdebugutil.o:	ezdebugutil.h
		g++ -c ezdebugutil.cpp

ezcfg_util.o:	ezcfg_util.h
		g++ -c ezcfg_util.cpp

clean:
		rm *.o
