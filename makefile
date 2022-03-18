CC=gcc
export CC

ROOT_MAKEFILE=$(abspath $(lastword $(MAKEFILE_LIST)))
D_ROOT := $(patsubst %/,%,$(dir $(ROOT_MAKEFILE)))
export D_ROOT

C_INCLUDE_PATH=$(D_ROOT)
export C_INCLUDE_PATH

D_LIB=$(D_ROOT)/scr
D_TEST=$(D_ROOT)/test
SUBDIRS = $(D_LIB) $(D_TEST)
export D_LIB D_TEST

all :
	for sdir in $(SUBDIRS); do \
		$(MAKE) -C $$sdir; \
	done

test::
	$(MAKE) -C ./test run

clean:
	for sdir in $(SUBDIRS); do \
		$(MAKE) -C $$sdir clean; \
	done