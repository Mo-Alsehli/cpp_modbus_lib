CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude

SRC = $(wildcard src/*/*.cpp)
OBJ = $(SRC:.cpp=.o)

LIB = build/libmodbus.a

all: build $(LIB)

build:
mkdir -p build

$(LIB): $(OBJ)
ar rcs $@ $^

%.o: %.cpp
$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
rm -rf build src/*/*.o
