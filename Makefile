#COMPILING AND LINKING
CC       = gcc
CFLAGS   = -Wall -g -pedantic
LDFLAGS  =
ARCHIVER = ar

#INSTALL
DESTDIR    =
PREFIX     = /usr
LIBDIR     = $(PREFIX)/lib
INCLUDEDIR = $(PREFIX)/include
MANDIR     = $(PREFIX)/man

#LIBRARY
LIBRARY     = listlib
VERSION     = 0
REVISION    = 7
LIBRARYNAME = lib$(LIBRARY).so
SONAME      = lib$(LIBRARY).so.$(VERSION)
LIBRARYVER  = lib$(LIBRARY).so.$(VERSION).$(REVISION)
STATICLIB   = lib$(LIBRARY).a

#PACKAGE
TARDIR  = $(LIBRARY)-$(VERSION).$(REVISION)
TARFILE = $(TARDIR).tar

#MAN PAGE
PODFILE    = $(LIBRARY).pod
MANSECTION = 3
MANPAGE    = $(LIBRARY).$(MANSECTION)

all: shared static

shared: $(LIBRARYVER)

static: $(STATICLIB)

$(LIBRARYVER): $(LIBRARY).o
	$(CC) -shared -fpic -o $(LIBRARYVER) $(LIBRARY).o -lc -Wl,-soname,$(SONAME) $(LDFLAGS)

listlib.o:
	$(CC) -c -fpic -g -Wall $(LIBRARY).c

$(STATICLIB): static$(LIBRARY).o
	$(ARCHIVER) rcs $(STATICLIB) static$(LIBRARY).o $(LDFLAGS)

staticlistlib.o:
	$(CC) -c -g -Wall $(LIBRARY).c -o static$(LIBRARY).o

test: all
	ln -fs $(LIBRARYVER) $(SONAME)
	ln -fs $(SONAME) $(LIBRARYNAME)
	$(CC) -c test.c $(CFLAGS)
	$(CC) -o $@ test.o -Wl,-rpath,. -L. -l$(LIBRARY) $(LDFLAGS)
	@echo Testing shared library
	@./test
	rm -f test.o test
	rm -f $(LIBRARYNAME) $(SONAME)

install: all 
	mkdir -p $(DESTDIR)$(LIBDIR)
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	mkdir -p $(DESTDIR)$(MANDIR)/man$(MANSECTION)
	cp -f $(LIBRARYVER) $(STATICLIB) $(DESTDIR)$(LIBDIR)
	cp -f $(LIBRARY).h $(DESTDIR)$(INCLUDEDIR)
	cp -f $(MANPAGE) $(DESTDIR)$(MANDIR)/man$(MANSECTION)
	ln -fs $(LIBRARYVER) $(DESTDIR)$(LIBDIR)/$(SONAME)
	ln -fs $(SONAME) $(DESTDIR)$(LIBDIR)/$(LIBRARYNAME)

package:
	rm -rf $(TARFILE) $(TARDIR) $(TARFILE).bz2
	mkdir $(TARDIR)
	cp Makefile $(LIBRARY).c $(LIBRARY).h test.c README.html LICENSE $(PODFILE) $(MANPAGE) $(TARDIR)
	tar cf $(TARFILE) $(TARDIR)
	bzip2 -zf9 $(TARFILE)
	rm -rf $(TARDIR)

manpage:
	pod2man -s 3 -c $(LIBRARY) --release=$(VERSION).$(REVISION) -d $(LIBRARY) $(PODFILE) > $(MANPAGE)

clean:
	rm -f $(LIBRARY).o static$(LIBRARY).o
	rm -f $(LIBRARYVER) $(STATICLIB)
