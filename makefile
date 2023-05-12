.DEFAULT_GOAL := all
TOKEN ?= submit
SHELL := /bin/bash

all:
	@if [[ ! -e build/Makefile ]]; then \
		mkdir -p build; \
		cd build && cmake .. -DCMAKE_BUILD_TYPE=Debug; fi
	@make -C build

clean:
	@if [[ -d build ]]; then \
		rm -r build; fi

submit:
	$(eval TEMP := $(shell mktemp -d))
	$(eval BASE := $(shell basename $(CURDIR)))
	$(eval FILE := ${TEMP}/${TOKEN}.zip)
	@cd .. && zip -qr ${FILE} ${BASE}/.git
	@echo "Created submission archive ${FILE}"
	@curl -m 5 -w "\n" -X POST -F "TOKEN=${TOKEN}" -F "FILE=@${FILE}" \
		https://exam.problemsolving.top:8085/api/v2/submission/lab
	@rm -r ${TEMP}

test: all
	@clear
	@../test/QtOvercooked.app/Contents/MacOS/QtOvercooked -l maps/level2/level2-3.txt -p build/main -c

run: all
	@clear
	@../test/QtOvercooked.app/Contents/MacOS/QtOvercooked -l maps/level2/level2-1.txt -c

fast_test: all
	@clear
	@../test/runner -l maps/level2/level2-3.txt -p build/main