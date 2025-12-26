# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++17 -g -O0

# Output executable name
TARGET = Stack_app.exe

# Source files
SRCS = Main.cpp LinkedList.cpp TestLinkedList.cpp DoublyLinkedList.cpp TestDoublyLinkedList.cpp Stack.cpp testStack.cpp Queue.cpp TestQueue.cpp ../Rational/Rational.cpp

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