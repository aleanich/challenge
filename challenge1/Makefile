CXX = g++
CXXFLAGS = -Wall -std=c++23 -I${HOME}/pacs/pacs-examples/Examples/include
#LDLIBS = -L../Examples/lib 
LINK.o = $(CXX) $(LDFLAGS) $(TARGET_ARCH)

# get all files *.cpp
SRCS=$(wildcard *.cpp)
# get the corresponding object file
OBJS = $(SRCS:.cpp=.o)
# get all headers in the working directory
HEADERS=$(wildcard *.hpp)
#
exe_sources=$(filter main%.cpp,$(SRCS))
EXEC=$(exe_sources:.cpp=)

#========================== NEW THE DEFINITION OF THE TARGETS
.phony= all clean 

.DEFAULT_GOAL = run

all: $(EXEC)

clean:
	$(RM) -f $(EXEC) $(OBJS) $(wildcard *.dat)

run: $(EXEC)
	./$(EXEC)

result: $(EXEC)
	./plot.sh

err: $(EXEC)
	./errors.sh

$(EXEC): $(OBJS)

$(OBJS): $(SRCS)
