#! Sostitute here your directory that contains Examples to run the code 
PACS_ROOT=${HOME}/pacs/pacs-examples

CXX = g++
CXXFLAGS = -Wall -std=c++23 -I${PACS_ROOT}/Examples/include 
LDLIBS = -lmuparser
LDFLAGS = -L${PACS_ROOT}/Examples/lib -Wl,-rpath=${PACS_ROOT}/Examples/lib 
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
