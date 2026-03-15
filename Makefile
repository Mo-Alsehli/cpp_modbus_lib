CXX = g++
INCLUDE_DIRS := $(shell find include -type d)
CPPFLAGS = $(addprefix -I,$(INCLUDE_DIRS))
CXXFLAGS = -std=c++20 -Wall -Wextra -g $(CPPFLAGS)

SRC = $(wildcard src/*/*.cpp)

OBJ = $(patsubst src/%.cpp,build/%.o,$(SRC))

LIB = build/libmodbus.a

all: $(LIB)

$(LIB): $(OBJ)
	ar rcs $@ $^

build/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build
