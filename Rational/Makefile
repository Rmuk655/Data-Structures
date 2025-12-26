# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++17

# Output executable name
TARGET = rational_app

# Source files
SRCS = main.cpp Rational.cpp test.cpp

# Object files (replace .cpp with .o)
OBJS = $(SRCS:.cpp=.o)

# Default rule
all: $(TARGET)

# Link object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)