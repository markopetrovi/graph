CXX = g++
CXXFLAGS = -std=c++20 -Wall -Werror -I. -O2
SRCS := $(shell find . -name '*.cpp')
OBJS = $(SRCS:.cpp=.o)
TARGET = my_program

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)