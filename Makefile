
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

OUTPUT=output

cmd_ls.elf: cmd_ls.o $(LIB_APUE)
	$(CC) $(OUTPUT)/$< $(OUTPUT)/syserr.o $(CFLAGS) -o $@ 


OBJ_APUE_OUTPUT=$(foreach each_obj,$(OBJ_APUE),$(OUTPUT)/$(each_obj))
$(LIB_APUE): $(OBJ_APUE)
	$(AR) rcs $(LIB_APUE) $(OBJ_APUE_OUTPUT)
	$(RANLIB) $@


%.o: %.c
	@mkdir -p $(OUTPUT)
	$(CC) $(CFLAGS) -c -o $(OUTPUT)/$@ $<

clean:
	@rm -f *.o *.a *.elf
	@rm -rf output

#.PHONY cmd_ls
