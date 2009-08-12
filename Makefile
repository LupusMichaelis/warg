TARGET=warg

CC=g++
DB=gdb
CXXFLAGS= \
		-W -Wall \
		-Wno-multichar \
		-Wno-unused-parameter \
		-DDEBUG -g -ggdb \
		-I/usr/include/boost-1_37/ \
		-Isrc/ \
		-DGTKMM_DISABLE_DEPRECATED \
		`pkg-config gtkmm-2.4 --cflags` \
#
#		-Werror \

LDFLAGS= \
		-L. \
		-g -ggdb \
		-lboost_regex-mt \
		`pkg-config gtkmm-2.4 --libs` \
#
SRCDIR=src/
SRCS=$(wildcard $(SRCDIR)*.cpp)
#

OBJS=$(SRCS:.cpp=.o)

TESTDIR=tests/
TESTSRCS=$(wildcard $(TESTDIR)*.cpp)
TESTOBJS=$(TESTSRCS:.cpp=:.o)
TESTBUILDS=$(TESTSRCS:.cpp=)

.SUFFIXES: .o .cpp .h
.PHONY: all clean test doc


all: test $(TARGET) g$(TARGET)

test: $(TESTBUILDS)

tests/test_app_cli: tests/test_app_cli.o src/app_cli.o src/app.o
tests/test_engine: tests/test_engine.o src/engine.o
tests/test_engine_u: tests/test_engine_u.o src/engine-ustring.o
tests/test_engine_w: tests/test_engine_w.o src/engine-wstring.o 

%.o: %.h %.cpp

$(TARGET): $(OBJS)
	 $(CXX) -o $@ $(OBJS) $(LDFLAGS)

g$(TARGET): $(TARGET)
	cp $(TARGET) g$(TARGET)

# Documentation generation with doxygen
doc:
	doxygen Doxyfile

clean:
	$(RM) g$(TARGET) $(TARGET) $(OBJS) $(TSTEXES) $(TSTOBJS)

