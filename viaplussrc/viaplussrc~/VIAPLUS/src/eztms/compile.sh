SRCPATH=$EZDIR_HOME

for i in ezmmsmgr ezmmscmd
do
	cd $SRCPATH/src/ezmms/$i
	make clean
	make
	make install
	make clean
done

for i in eztmscontroller eztmsdriver eztmslogger eztmsmgr
do
	cd $SRCPATH/src/eztms/$i
	make clean
	make
	make install
	make clean
done
