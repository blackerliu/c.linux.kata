
CC	=$(CROSS_PREFIX)gcc
LD	=$(CROSS_PREFIX)ld
AR	=$(CROSS_PREFIX)ar
NM	=$(CROSS_PREFIX)nm
RANLIB	=$(CROSS_PREFIX)ranlib

CFLAGS  += -I./include

LDFLAGS += -static
LDFLAGS += -L.
LDFLAGS += -lapue
LDFLAGS += -lc

CFLAGS	+= $(EXTRA_CFLAGS)
LDFLAGS	+= $(EXTRA_LDFLAGS)

LIB_APUE=libapue.a
OBJ_APUE=syserr.o syslog.o

DIR_OUTPUT=output
DIR_BIN=bin
DIR_SRC=src

FILES_SRC=$(shell cd src; ls *.c)
FILES_OBJ=$(shell echo $(FILES_SRC) | sed 's/\.c/\.o/g')
FILES_BIN=$(shell echo $(FILES_SRC) | sed 's/\.c//g')

build: $(LIB_APUE) $(FILES_OBJ) 
	@echo "Generate command ..."
	@for each_bin in $(FILES_BIN); do \
		echo "Command:" $$each_bin; \
		$(CC) $(DIR_OUTPUT)/$$each_bin.o $(DIR_OUTPUT)/syserr.o $(CFLAGS) -o $(DIR_BIN)/$$each_bin;\
	done;

obj_apue_with_path=$(foreach each_obj,$(OBJ_APUE),$(DIR_OUTPUT)/$(each_obj))
$(LIB_APUE): syserr.o syslog.o
	$(AR) rcs $(LIB_APUE) $(obj_apue_with_path)
	$(RANLIB) $@

syserr.o: syserr.c
	@mkdir -p $(DIR_OUTPUT)
	$(CC) $(CFLAGS) -c -o $(DIR_OUTPUT)/$@ $<

syslog.o: syslog.c
	@mkdir -p $(DIR_OUTPUT)
	$(CC) $(CFLAGS) -c -o $(DIR_OUTPUT)/$@ $<

	
%.o: $(DIR_SRC)/%.c
	@mkdir -p $(DIR_OUTPUT)
	$(CC) $(CFLAGS) -c -o $(DIR_OUTPUT)/$@ $<

clean:
	@rm -f *.o *.a *.elf
	@rm -f $(DIR_BIN)/*
	@rm -rf $(DIR_OUTPUT)

debug:
	@echo "SRC:" $(FILES_SRC)
	@echo "OBJ:" $(FILES_OBJ)
	@echo "BIN:" $(FILES_BIN)

#.PHONY cmd_ls