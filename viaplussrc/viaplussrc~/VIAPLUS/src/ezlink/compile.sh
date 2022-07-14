SRCPATH=$EZDIR_HOME

for i in ezinstmgr ezlicensemgr ezauthmgr ezechomgr eznetworkkeymgr eznetworkmgr eztxnmgr eztxnlogger ezsafreader ezsafwriter ezinstdbcmd eznetcmd ezreplaycmd ezsafcmd ezechocmd ezbusdaycmd
do
	cd $SRCPATH/src/ezlink/$i
	make clean
	make
	make install
	make clean
done
