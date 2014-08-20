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

run_%: modules/stap_%.ko | results_dir
	staprun $^ -o results/$* SY_syscaller=$* -D
	sleep 5
	bin/$*
results_dir:
	-mkdir results

progs: $(PROGS)

bin/%: samples/**/%.c | binary_dir
	$(CC) $(CFLAGS) -o $@ $^
binary_dir:
	-mkdir bin

modules: $(MODULES)

$(MODULES): modules/stap_%.ko: dependencies/% $(wildcard samples/**/%.c) syscaller.stp | modules_dir
	stap -p4 -v -m stap_$* syscaller.stp $* '"*@$(shell cat $<)"'
	mv stap_$*.ko modules/
modules_dir:
	-mkdir modules
