CC:=gcc
CFLAGS:=-W -Wall --std=gnu11

SRCS:=$(wildcard samples/**/*.c)
DEPS:=$(wildcard dependencies/*)

SRCS_STRIPPED:=$(notdir $(basename $(SRCS)))
DEPS_STRIPPED:=$(notdir $(basename $(DEPS)))
UNITS:=$(filter $(SRCS_STRIPPED), $(DEPS_STRIPPED))

PROGS:=$(UNITS:%=bin/%)
MODULES:=$(UNITS:%=modules/stap_%.ko)

all: progs modules

run: $(UNITS:%=run_%)

run_%: modules/stap_%.ko
	staprun $^ -o results/$* SY_syscaller=$* -D
	sleep 5
	bin/$*

progs: $(PROGS)

bin/%: samples/**/%.c
	$(CC) $(CFLAGS) -o $@ $^

modules: $(MODULES)

$(MODULES): modules/stap_%.ko: dependencies/% $(wildcard samples/**/%.c) syscaller.stp
	stap -p4 -v -m stap_$* syscaller.stp $* '"*@$(shell cat $<)"'
	mv stap_$*.ko modules/
