PROJECT_SOURCE_DIR := $(abspath ./)
BUILD_DIR ?= $(PROJECT_SOURCE_DIR)/build
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
    NUM_JOB := $(shell nproc)
else ifeq ($(UNAME_S), Darwin)
    NUM_JOB := $(shell sysctl -n hw.ncpu)
else
    NUM_JOB := 1
endif

clean:
	rm -rf $(BUILD_DIR)
.PHONY: clean

test:
	cmake -S . -B $(BUILD_DIR) && \
	cmake --build $(BUILD_DIR) --target cielmalloc_benchmark -j $(NUM_JOB)
	$(BUILD_DIR)/cielmalloc_benchmark
.PHONY: test

format:
	./format.sh run $(PROJECT_SOURCE_DIR)/src
.PHONY: format

check_format:
	./format.sh check $(PROJECT_SOURCE_DIR)/src
.PHONY: check_format
