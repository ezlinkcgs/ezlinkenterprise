SRCPATH=$EZDIR_HOME

for i in ezatmmgr ezatmcontroller ezatmejmgr ezd912 ezndc ezguicontroller ezportupdater ezsecuritymgr ezsecuritydriver ezatmcmd ezejcmd ezgsmcmd ezsecuritycmd
do
	cd $SRCPATH/src/ezbusiness/$i
	make clean
	make
	make install
	make clean
done

