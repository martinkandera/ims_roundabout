CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I./include
LDFLAGS =

TARGET = roundabout
SRCS = src/main.cpp src/graph.cpp src/renderer.cpp src/debug.cpp  # Add src/debug.cpp here
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET) data/intersection.json

clean:
	rm -f $(TARGET) src/*.o

install-deps:
	@echo "Installing nlohmann/json..."
	@mkdir -p include/nlohmann
	@wget -q -O include/nlohmann/json.hpp \
	  https://github.com/nlohmann/json/releases/download/v3.11.3/json.hpp
	@echo "✓ Dependencies installed"

.PHONY: all run clean install-deps
