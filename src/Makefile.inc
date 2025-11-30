#@HDR@	$Id$
#@HDR@		Copyright 2024 by
#@HDR@		Christopher Caldwell/Brightsands
#@HDR@		P.O. Box 401, Bailey Island, ME 04003
#@HDR@		All Rights Reserved
#@HDR@
#@HDR@	This software comprises unpublished confidential information
#@HDR@	of Brightsands and may not be used, copied or made available
#@HDR@	to anyone, except in accordance with the license under which
#@HDR@	it is furnished.

PWD=$(shell pwd)

# PROJ should be set by the time this is included
ifeq ($($PROJ),)
    PROJ=$(subst src.,,$(notdir $(PWD)))
endif

# Should either be "OBJDIR" or "SRCDIR"
#BUILD_IN=OBJDIR
BUILD_IN=SRCDIR

SHELL=/bin/sh
CC=gcc
CFLAGS= -g -ggdb	# Compile with symbols and for GDB
LDFLAGS+=-lm
NOW=`date +%Y%m%d%H%M`

COMPILER_TARGET=$(shell $(CC) -v 2>&1 | awk '/Target:/ { print $$2 }')
COMPILER_VERSION=$(shell $(CC) -v 2>&1 | awk '/ version / { print $$3 }')
BUILDFOR=$(COMPILER_TARGET)-$(COMPILER_VERSION)
#BUILDFOR=$(shell uname -s).$(shell uname -m).$(shell uname -r)

BUP_DIR=../BUPS/$(PROJ)

OBJDIR=../obj/$(BUILDFOR)/$(PROJ)
ifeq (,$(SRCDIR))
    SRCDIR=$(PWD)
endif
VPATH=$(SRCDIR)

OBJMAKE=$(MAKE) -C$($(BUILD_IN)) -f$(SRCDIR)/Makefile SRCDIR=$(SRCDIR)

CHECKLIBS=/lib /usr/lib /usr/ccs/lib

libsearch = $(firstword $(wildcard $(addsuffix /lib$(1).*,$(CHECKLIBS))))

ifneq ($(call libsearch,socket),)
    SOCKETLIBS=-lsocket
endif

# Tell $(CC) compiler where nn.h etc is.
ifeq ($(INCLUDE_FLAGS0),)
    INCLUDE_FLAGS0=-I$(SRCDIR)
endif

		# Here are the object files required for nn
ifeq ($(OBJS0),)
    OBJS0	=	$(subst .c,.o,$(notdir $(wildcard $(SRCDIR)/*.c)))
    XOBJS0	=	$(addprefix $(OBJDIR)/,$(OBJS0))
endif

ifeq ($(INCS0),)
    INCS0	=	$(wildcard $(SRCDIR)/*.h)
endif

ifeq ($(BIN0),)
    BIN0=$(PROJ)
endif
ifeq ($(BINS),)
    BINS=$(BIN0)
endif
ifeq ($(OBJS),)
    OBJS=$(OBJS0)
endif

ifeq ($(BUILD_IN),OBJDIR)
    XBINS	=	$(BINS)
else
    XBINS	=	$(addprefix $(OBJDIR)/,$(BINS))
endif

ifeq ($(TESTS),)
    TESTS=test_$(PROJ)
endif

ifeq ($(DEST_BIN),)
    DEST_DIR=/usr/local
    DEST_BIN=$(DEST_DIR)/bin
endif

all:		; @mkdir -p $(OBJDIR); $(OBJMAKE) $@_objs
install:	; @mkdir -p $(OBJDIR); $(OBJMAKE) $@_objs
test:		; @mkdir -p $(OBJDIR); $(OBJMAKE) $@_objs
all_objs:	$(XBINS)
test_objs:	$(TESTS)
install_objs:	$(XBINS)
		mkdir -p $(DEST_BIN)
		cd $(OBJDIR); cp $(BINS) $(DEST_BIN)

clean:
		rm -rf $(OBJDIR) *.o core

again:
		make clean
		make all

.c.o:
		$(CC) -c $(CFLAGS) $(INCLUDE_FLAGS0) $<

$(OBJDIR)/%.o:	%.c $(INCS0)
		@mkdir -p $(OBJDIR)
		$(CC) -c $(CFLAGS) -I. $< -o $@

$(OBJDIR)/$(BIN0):	$(XOBJS0)
		cd $(OBJDIR); $(CC) $(OBJS0) -o $(BIN0) $(LDFLAGS)

$(OBJS0):	$(INCS0)

%.o:		$(SRCDIR)/%.c

$(BIN0):	$(OBJS0)
		$(CC) $(LDFLAGS) -o $@ $(OBJS0)

bup:		clean
		mkdir -p $(BUP_DIR)
		tar cf - . | bzip2 -9 > $(BUP_DIR)/$(NOW).bz2

vars:
		@echo PROJ=$(PROJ) NOW=$(NOW)
		@echo SRCDIR=$(SRCDIR) OBJDIR=$(OBJDIR)
		@echo BIN0=$(BIN0) BINS=$(BINS) XBINS=$(XBINS)
		@echo OBJS0=$(OBJS0)
		@echo XOBJS0=$(XOBJS0)
		@echo INCS0=$(INCS0)
