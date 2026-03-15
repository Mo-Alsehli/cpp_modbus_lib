CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude

BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)
EXAMPLES_DIR = $(BUILD_DIR)/examples

LIB = $(BUILD_DIR)/libmodbus.a

# Automatically find all cpp files
SRC := $(shell find src -name "*.cpp")

# Convert src/...cpp → build/...o
OBJ := $(patsubst src/%.cpp,$(BUILD_DIR)/%.o,$(SRC))

CLIENT_EXAMPLE = $(EXAMPLES_DIR)/client_rtu_example
SERVER_EXAMPLE = $(EXAMPLES_DIR)/server_rtu_example


all: directories $(LIB) examples

examples: $(CLIENT_EXAMPLE) $(SERVER_EXAMPLE)


directories:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/client
	mkdir -p $(BUILD_DIR)/core
	mkdir -p $(BUILD_DIR)/function_codes
	mkdir -p $(BUILD_DIR)/server
	mkdir -p $(BUILD_DIR)/transport
	mkdir -p $(EXAMPLES_DIR)


# Build library
$(LIB): $(OBJ)
	ar rcs $@ $^


# Compile objects
$(BUILD_DIR)/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


# Examples
$(CLIENT_EXAMPLE): examples/client_rtu_example.cpp $(LIB)
	$(CXX) $(CXXFLAGS) $< $(LIB) -o $@

$(SERVER_EXAMPLE): examples/server_rtu_example.cpp $(LIB)
	$(CXX) $(CXXFLAGS) $< $(LIB) -o $@


clean:
	rm -rf build


.PHONY: all clean examples directories