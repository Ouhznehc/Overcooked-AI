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
	@rm main

submit:
	$(eval TEMP := $(shell mktemp -d))
	$(eval BASE := $(shell basename $(CURDIR)))
	$(eval FILE := ${TEMP}/${TOKEN}.zip)
	@cd .. && zip -qr ${FILE} ${BASE}/.git
	@echo "Created submission archive ${FILE}"
	@curl -m 5 -w "\n" -X POST -F "TOKEN=${TOKEN}" -F "FILE=@${FILE}" \
		https://exam.problemsolving.top:8085/api/v2/submission/lab
	@rm -r ${TEMP}

MAP = maps/level2/level2-4.txt


test: all
	@clear
	@../test/QtOvercooked.app/Contents/MacOS/QtOvercooked -l ${MAP} -p build/main -c

run:
	@clear
	@../test/QtOvercooked.app/Contents/MacOS/QtOvercooked -l ${MAP} -c

fast_test: all
	@clear
	@../test/runner -l ${MAP} -p build/main

compile:
	@find source -type f -name "*.cpp" -exec \
    g++ -std=c++20 -fsanitize=address -Wall -O2 -I include -o main {} +

strict_test: compile
	@clear
	@../test/QtOvercooked.app/Contents/MacOS/QtOvercooked -l ${MAP} -p main -c

strict_fast_test: compile
	@clear
	@../test/runner -l ${MAP} -p main

xsz: compile
	@clear
	@../test/QtOvercooked.app/Contents/MacOS/QtOvercooked -l ${MAP} -p xsz -c
