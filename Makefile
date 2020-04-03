.POSIX:

include config.mk

SRC = readvtc.c
OBJ = $(SRC:.c=.o)

all: options readvtc

options:
	@echo readvtc build options:
	@echo "VERSION = $(VERSION)"
	@echo "PREFIX  = $(PREFIX)"
	@echo "CFLAGS  = $(STCFLAGS)"
	@echo "CC      = $(CC)"

.c.o:
	$(CC) $(STCFLAGS) -c $<

$(OBJ): config.mk

readvtc: $(OBJ)
	$(CC) -o $@ $(OBJ) $(STCFLAGS)

clean:
	rm -f readvtc $(OBJ)

install: readvtc
	@echo installing executable to ${PREFIX}/bin
	mkdir -p $(PREFIX)/bin
	cp -f readvtc $(PREFIX)/bin
	chmod 755 $(PREFIX)/bin/readvtc
	@echo installing manual page to ${MANPREFIX}/man1
	mkdir -p ${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < readvtc.1 > ${MANPREFIX}/man1/readvtc.1
	chmod 644 ${MANPREFIX}/man1/readvtc.1

uninstall:
	rm -f $(PREFIX)/bin/readvtc
	rm -f $(MANPREFIX)/man1/readvtc.1

.PHONY: all options clean install uninstall
