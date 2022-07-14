SRCPATH=$EZDIR_HOME

for i in ezdebugmgr eztaskmgr ezchannelmgr ezcommmgr ezcommdrvr ezmcommdrvr ezeventmgr ezeventlocater ezloadbalancer ezmsgrouter ezchannelcmd ezdebugcmd ezportcmd eztaskcmd  
do
	cd $SRCPATH/src/ezkernel/$i
	make clean
	make
	make install
	make clean
done
