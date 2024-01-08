OBJECTS=bufile.o

CFLAGS=-Wall -g
CXXFLAGS=-Wall -g

SHELL=/bin/bash

TIMEOUT=8

TESTS_DIR=tests

TESTS_SH:=$(wildcard $(TESTS_DIR)/*.sh)
TESTS_SH_NAMES:=$(patsubst $(TESTS_DIR)/%.sh, %, $(TESTS_SH))

TESTS_IO:=$(wildcard $(TESTS_DIR)/*.in)
TESTS_IO_NAMES:=$(patsubst $(TESTS_DIR)/%.in, %, $(TESTS_IO))

TESTS_C:=$(wildcard $(TESTS_DIR)/*.c)
TESTS_CXX:=$(wildcard $(TESTS_DIR)/*.cc)
TESTS_BIN:=$(patsubst $(TESTS_DIR)/%.c, $(TESTS_DIR)/%, $(TESTS_C)) \
	   $(patsubst $(TESTS_DIR)/%.cc, $(TESTS_DIR)/%, $(TESTS_CXX))
TESTS_BIN_NAMES:=$(patsubst $(TESTS_DIR)/%.c, %, $(TESTS_C)) $(patsubst $(TESTS_DIR)/%.cc, %, $(TESTS_CXX))

.PHONY: all
all: compile check

.PHONY: compile-program

compile: $(PROGRAMS) $(OBJECTS)

.PHONY: check
check: check-bin check-io-sh

.PHONY: check-io-sh
check-io-sh: compile $(TESTS_IO) $(TESTS_SH)
	@exec 2> /dev/null; \
	for p in $(foreach prog,$(PROGRAMS),$(dir $(prog))$(prog)); do \
	echo "Testing $${p}:" ; \
	for t in $(TESTS_IO_NAMES); do \
		echo -n "Running test $$t... " ; \
		"$$p" < "$(TESTS_DIR)/$$t.in"  > "$$t.out" 2>&1 & \
		prog_pid=$$!; \
		( sleep $(TIMEOUT); kill $$prog_pid > /dev/null 2>&1 ) & \
		killer_pid=$$!; \
		wait $$prog_pid; \
		res=$$?; \
		if test $$res -gt 128; \
		then \
			case `kill -l $$(($$res - 128))` in \
				ABRT ) echo "FAIL"; ;; \
				TERM ) echo "TIME OUT"; ;; \
				* ) echo "UNKNOWN ERROR"; ;; \
			esac ; \
			echo "see $(TESTS_DIR)/$$t.in" ;\
			echo "you may run $$p < $(TESTS_DIR)/$$t.in" ;\
			echo "to see what went wrong";\
			rm -f "$$t.out" ;\
		else \
			kill $$killer_pid > /dev/null 2>&1 ;\
			wait $$killer_pid; \
			if cmp -s "$$t.out" "$(TESTS_DIR)/$$t.expected"; \
			then \
				echo "PASS" ;\
				rm -f "$$t.out" ;\
			else \
				echo "FAIL" ;\
				echo "see $(TESTS_DIR)/$$t.in" ;\
				echo "run diff $$t.out $(TESTS_DIR)/$$t.expected";\
				echo "to see the difference between the actual and expected output";\
			fi; \
		fi; \
	done; \
	for t in $(TESTS_SH_NAMES); do \
		echo -n "Running test $$t... " ; \
		$(SHELL) "$(TESTS_DIR)/$$t.sh" "$$p" > "$$t.out" 2>&1 & \
		prog_pid=$$!; \
		( sleep $(TIMEOUT); kill $$prog_pid > /dev/null 2>&1 ) & \
		killer_pid=$$!; \
		wait $$prog_pid; \
		res=$$?; \
		if test $$res -gt 128; \
		then \
			case `kill -l $$(($$res - 128))` in \
				ABRT ) echo "FAIL"; ;; \
				TERM ) echo "TIME OUT"; ;; \
				* ) echo "UNKNOWN ERROR"; ;; \
			esac ; \
			echo "see $(TESTS_DIR)/$$t.sh" ;\
			echo "you may run $(TESTS_DIR)/$$t.sh $$p" ;\
			echo "to see what went wrong";\
			rm -f "$$t.out" ;\
		else \
			kill $$killer_pid > /dev/null 2>&1 ;\
			wait $$killer_pid; \
			if test -r "$(TESTS_DIR)/$$t.expected"; \
			then \
				if cmp -s "$$t.out" "$(TESTS_DIR)/$$t.expected"; \
				then \
					echo "PASS" ;\
					rm -f "$$t.out" ;\
				else \
					echo "FAIL" ;\
					echo "see $(TESTS_DIR)/$$t.sh" ;\
					echo "run diff $$t.out $(TESTS_DIR)/$$t.expected";\
					echo "to see the difference between the actual and expected output";\
				fi; \
			else \
				if test $$res = 0 ; \
				then \
					echo "PASS" ;\
					rm -f "$$t.out" ;\
				else \
					echo "FAIL" ;\
					echo "see $(TESTS_DIR)/$$t.sh" ;\
					echo "you may run $(TESTS_DIR)/$$t.sh $$p" ;\
					echo "to see what went wrong";\
					rm -f "$$t.out" ;\
				fi; \
			fi; \
		fi; \
	done; \
	done

$(TESTS_DIR)/%: $(TESTS_DIR)/%.c $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(TESTS_DIR)/$*.c $(OBJECTS) -o $@

$(TESTS_DIR)/%: $(TESTS_DIR)/%.cc $(OBJECTS)
	$(CXX) -std=c++11 $(CXXFLAGS) $(LDFLAGS) $(TESTS_DIR)/$*.cc $(OBJECTS) -o $@

.PHONY: check-bin
check-bin: $(TESTS_BIN)
	@exec 2> /dev/null; \
	for t in $(TESTS_BIN_NAMES); do \
		echo -n "Running test $$t... " ; \
		"$(TESTS_DIR)/$$t" -q &\
		prog_pid=$$!; \
		( sleep $(TIMEOUT); kill $$prog_pid > /dev/null 2>&1 ) & \
		killer_pid=$$!; \
		wait $$prog_pid; \
		res=$$?; \
		if test $$res = 0; then \
			kill $$killer_pid > /dev/null 2>&1 ;\
			wait $$killer_pid; \
			echo "PASS" ;\
		else \
			if test $$res -gt 128; \
			then \
				case `kill -l $$(($$res - 128))` in \
					ABRT ) echo "FAIL"; ;; \
					TERM ) echo "TIME OUT"; ;; \
					* ) echo "UNKNOWN ERROR"; ;; \
				esac ; \
			else \
				kill $$killer_pid > /dev/null 2>&1 ;\
				wait $$killer_pid; \
				echo "FAIL" ;\
			fi; \
			echo "run '$(TESTS_DIR)/$$t' to see what went wrong" ; \
			echo "run '$(TESTS_DIR)/$$t -d' with a debugger" ; \
		fi; \
	done


.PHONY: clean
clean:
	rm -f $(PROGRAMS) $(OBJECTS) tests/*.o $(TESTS_BIN)
