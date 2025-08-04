# Makefile for Eurydice C++ Project

# Variables
BUILD_DIR := build
BIN_DIR   := $(BUILD_DIR)/bin
CMAKE := cmake
MAKE := make

# Default target
.PHONY: all
all: build

# Create build directory and build project
.PHONY: build
build:
	@echo "Building Eurydice..."
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && $(CMAKE) .. && $(MAKE)

# Clean build artifacts
.PHONY: clean
clean:
	@echo "Cleaning build artifacts..."
	@rm -rf $(BUILD_DIR)

# Run the application
.PHONY: run
run: build
	@echo "Running Eurydice..."
	@$(BIN_DIR)/eurydice

# Run tests
.PHONY: test
test: build
	@echo "Running tests..."
	@cd $(BUILD_DIR) && $(MAKE) test

# Help target
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  build        - Build the project"
	@echo "  clean        - Clean build artifacts"
	@echo "  run          - Build and run the application"
	@echo "  test         - Run tests"
	@echo "  check        - Alias for test"
	@echo "  install-deps - Install development dependencies"
	@echo "  format       - Format code with clang-format"
	@echo "  lint         - Lint code with cppcheck"
	@echo "  help         - Show this help message" 
