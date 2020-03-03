CC := gcc
SRCDIR := src
BINDIR := bin
BLDDIR := build
INCDIR := include

ALL_SRCF := $(shell find $(SRCDIR) -type f -name about_*.c)
#https://stackoverflow.com/a/10280945/104143
ALL_OBJF := $(patsubst $(SRCDIR)/%,$(BLDDIR)/%,$(ALL_SRCF:.c=.o))
ALL_EXEF := $(patsubst $(SRCDIR)/%,$(BINDIR)/%,$(ALL_SRCF:.c=.exe))
#MAINF := # use nm to find file with main and include it
#FUNCF := $(filter-out $(MAIN_FILES), $(ALL_OBJF))
DEPS_SRCF = $(SRCDIR)/c_koans_helpers.c
DEPS_OBJF = $(BLDDIR)/c_koans_helpers.o

INC := -I $(INCDIR)

EXEC := c_koans

STD := c99
CFLAGS := -std=$(STD) -Wall -Wextra -pedantic -Wno-unused-function -Wno-nonnull

CMOCKA := -lcmocka

.PHONY: setup all clean

all: setup $(EXEC)

debug: CFLAGS += $(DFLAGS)
debug: all

setup:
	@mkdir -p bin build

$(EXEC): $(ALL_EXEF)

$(BINDIR)/%.exe: $(BLDDIR)/%.o $(DEPS_OBJF)
	$(CC) $(CFLAGS) $(INC) $< $(DEPS_OBJF) -o $@ $(CMOCKA)

$(BLDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INC) $< -c -o $@

clean:
	$(RM) -r $(BLDDIR) $(BINDIR)
