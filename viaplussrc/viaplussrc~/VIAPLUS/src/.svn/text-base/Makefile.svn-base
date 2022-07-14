
SUBDIRS =	ezbusiness/ezatmcmd \
		ezbusiness/ezsecuritycmd \
		ezbusiness/ezdevicemgr \
		ezbusiness/ezsecuritymgr \
		ezbusiness/ezsecuritydriver \
		ezbusiness/ezatmcontroller \
		ezbusiness/ezd912 \
		ezbusiness/ezNDC \
		ezbusiness/eztritonstd \
		ezbusiness/ezhost8583 \
		ezbusiness/ezvisa8583 \
		ezkernel/ezchannelcmd \
		ezkernel/ezportcmd \
		ezkernel/eztaskcmd \
		ezkernel/ezchannelmgr \
		ezkernel/ezcommdrvr \
		ezkernel/ezcommmgr \
		ezkernel/ezeventmgr \
		ezkernel/ezeventpoolmgr \
		ezkernel/ezmsgrouter\
		ezkernel/eztaskmgr \
		ezlink/eznetcmd \
		ezlink/ezauthmgr \
		ezlink/eztxnmgr \
		ezlink/eznetworkmgr \
		ezlink/ezsafreader \
		ezlink/ezsafwriter \
		ezlink/ezechomgr \
		ezlink/eztxnlogger 


all:
	list='$(SUBDIRS)'; \
	for subdir in $$list; do \
	  (cd $$subdir && $(MAKE)); \
	done

install:
	list='$(SUBDIRS)'; \
	for subdir in $$list; do \
	  (cd $$subdir && $(MAKE) install); \
	done

clean:
	list='$(SUBDIRS)'; \
	for subdir in $$list; do \
	  (cd $$subdir && $(MAKE) clean); \
	done


