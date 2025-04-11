CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
INCLUDES = -I./src

# Directories
SRC_DIR = src
BIN_DIR = bin
TARGET = crypto

# Source files
SRCS = $(SRC_DIR)/Main.cpp \
	$(SRC_DIR)/IntMod.cpp \
	$(SRC_DIR)/Logger.cpp

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)

# Ensure bin directory exists
$(shell mkdir -p $(BIN_DIR))

# Main target
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Compile source files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean
clean:
	rm -rf $(BIN_DIR) $(TARGET)

.PHONY: clean