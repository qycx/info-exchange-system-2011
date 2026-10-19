# $Id: Makefile,v 1.12 2004/02/17 18:38:37 mjt Exp $
# Makefile for proxycheck.  GPL

CC = cc
CFLAGS = -O
DEFS = -D_GNU_SOURCE
LD = $(CC)
LDFLAGS =

# For Solaris, we need -lsocket -lnsl and -lresolv for inet_aton
RSOCKLIBS = `[ -f /usr/lib/libsocket.so ] && echo -lresolv -lsocket -lnsl || :`
SOCKLIBS = `[ -f /usr/lib/libsocket.so ] && echo -lsocket -lnsl || :`

USE_CFLAGS = $(CFLAGS) $(DEFS)

SRCS = proxycheck.c pxy.c event.c memmem.c proxylogger.c
HDRS = pxy.h event.h
DIST = $(SRCS) $(HDRS) Makefile event.3 proxycheck.1 CHANGES
VERSION = 0.46
VERSION_DATE = 2004-02-17

all: proxycheck

proxycheck_OBJS = proxycheck.o pxy.o event.o memmem.o
proxycheck: $(proxycheck_OBJS)
	$(LD) $(LDFLAGS) -o $@ $(proxycheck_OBJS) $(RSOCKLIBS)

proxylogger_OBJS = proxylogger.o
proxylogger: $(proxylogger_OBJS)
	$(LD) $(LDFLAGS) -o $@ $(proxylogger_OBJS) $(SOCKLIBS)

.c.o:
	$(CC) $(USE_CFLAGS) -c $<

proxycheck.o:
	$(CC) $(USE_CFLAGS) -c -DVERSION_STR='"$(VERSION) $(VERSION_DATE)"' $<

b = proxycheck-$(VERSION)
dist: $(b).tar.gz
$(b).tar.gz: $(DIST)
	rm -rf $(b)
	mkdir $(b)
	ln $(DIST) $(b)/
	tar cfz $@ $(b)
	rm -rf $(b)

clean:
	rm -f *~ *.o core

depend dep deps:
	@echo Generating deps for:
	@echo \ $(SRCS)
	@sed '/^# depend/q' Makefile > Makefile.tmp
	@$(CC) $(CFLAGS) -MM $(SRCS) >> Makefile.tmp
	@if cmp Makefile.tmp Makefile ; then \
	  echo Makefile unchanged; \
	  rm -f Makefile.tmp; \
	else \
	  echo Updating Makfile; \
	  mv -f Makefile.tmp Makefile ; \
	fi

# depend: anything after this line will be replaced by make depend
proxycheck.o: proxycheck.c event.h pxy.h
pxy.o: pxy.c event.h pxy.h
event.o: event.c event.h
memmem.o: memmem.c
proxylogger.o: proxylogger.c
