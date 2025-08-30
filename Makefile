# Compiler
CXX = clang++
CXXFLAGS = -std=c++17 -I/opt/homebrew/include -I"/Users/mac/Documents/undefined/Coding/C++/game/prototypes"

# Linker flags
LDFLAGS = -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lenet

# Source files
SRCS = files/platform.cpp files/util.cpp files/levels.cpp

# Output executable
TARGET = sfmltest

# Default target
all: $(TARGET)

# Build executable
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)
	

server: files/server.cpp
	$(CXX) files/server.cpp -o server $(CXXFLAGS) -lenet

# Clean build files
clean:
	rm -f $(TARGET)
