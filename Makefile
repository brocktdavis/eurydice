# Makefile for Eurydice C++ Project

# Variables
BUILD_DIR := build
BIN_DIR   := $(BUILD_DIR)/bin
CMAKE := cmake
MAKE := make
VCPKG_DIR := vcpkg

# Default target
.PHONY: help
all: help

# Setup vcpkg and install dependencies
.PHONY: setup
setup:
	@if [ ! -d "$(VCPKG_DIR)" ]; then \
		git clone https://github.com/Microsoft/vcpkg.git $(VCPKG_DIR); \
	fi
	@if [ ! -f "$(VCPKG_DIR)/vcpkg" ]; then \
		cd $(VCPKG_DIR) && ./bootstrap-vcpkg.sh; \
	fi
	@$(VCPKG_DIR)/vcpkg install rtaudio[pulse]

# Build with vcpkg toolchain (required)
.PHONY: build
build:
	@if [ ! -d "$(VCPKG_DIR)" ]; then \
		echo "Error: vcpkg directory does not exist: $(VCPKG_DIR)"; \
		echo "Please run: make setup"; \
		exit 1; \
	fi
	@if [ ! -f "$(VCPKG_DIR)/vcpkg" ]; then \
		echo "Error: vcpkg executable not found in $(VCPKG_DIR)"; \
		echo "Please run: make setup"; \
		exit 1; \
	fi
	@echo "Building Eurydice with vcpkg toolchain..."
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && $(CMAKE) .. -DCMAKE_TOOLCHAIN_FILE=$(VCPKG_DIR)/scripts/buildsystems/vcpkg.cmake && $(MAKE)

# Clean build artifacts
.PHONY: clean
clean:
	@echo "Cleaning build artifacts..."
	@rm -rf $(BUILD_DIR)

# Run the application
.PHONY: run
run: build
	@$(BIN_DIR)/eurydice

# Run tests
.PHONY: test
test: build
	@cd $(BUILD_DIR) && $(MAKE) test

# Help target
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  setup        - Setup vcpkg and install RtAudio"
	@echo "  build        - Build the project"
	@echo "  clean        - Clean build artifacts"
	@echo "  run          - Build and run the application"
	@echo "  test         - Run tests"
	@echo "  help         - Show this help message"
	@echo ""
	@echo "Quick start:"
	@echo "  make setup"
	@echo "  make build" 
	@echo "  make test"
	@echo "  make run"
