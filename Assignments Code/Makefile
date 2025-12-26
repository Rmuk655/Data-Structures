# Compiler
CXX = g++

# Source and target
SRCS = A7P2.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = A7P2.exe

# Flags
CXXFLAGS_RELEASE = -O2 -Wall -std=c++17
CXXFLAGS_DEBUG = -g -Wall -std=c++17

# Default target (release)
all: CXXFLAGS := $(CXXFLAGS_RELEASE)
all: $(TARGET)

# Debug build
debug: CXXFLAGS := $(CXXFLAGS_DEBUG)
debug: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilation
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OBJS) $(TARGET)