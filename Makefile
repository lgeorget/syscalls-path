CC:=gcc
CFLAGS:=-W -Wall --std=gnu11

SRCS:=$(wildcard samples/**/*.c)
DEPS:=$(wildcard dependencies/*)

SRCS_STRIPPED:=$(notdir $(basename $(SRCS)))
DEPS_STRIPPED:=$(notdir $(basename $(DEPS)))
UNITS:=$(filter $(SRCS_STRIPPED), $(DEPS_STRIPPED))

PROGS:=$(UNITS:%=bin/%)
MODULES:=$(UNITS:%=modules/stap_%.ko)

all: progs mods

run: $(UNITS:%=run_%)

run_%: modules/stap_%.ko | results
	staprun $^ -o results/$* -c "bin/$*"
results:
	-mkdir results

progs: $(PROGS)

bin/%: samples/**/%.c | bin
	$(CC) $(CFLAGS) -o $@ $^
bin:
	-mkdir bin

mods: $(MODULES)

$(MODULES): modules/stap_%.ko: dependencies/% $(wildcard samples/**/%.c) syscaller.stp | modules
	stap -v -p4 -m stap_$* syscaller.stp $* "*@$(shell cat $<)" -o results/$* -c "bin/$*"
	mv stap_$*.ko modules/
modules:
	-mkdir modules
