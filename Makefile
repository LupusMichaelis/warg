TARGET=warg

CC=g++
DB=gdb
CXXFLAGS= \
		-std=c++14  \
		-W -Wall \
		-Wno-multichar \
		-Wno-unused-parameter \
		-DDEBUG -g -ggdb \
		-I/usr/include/boost-1_37/ \
		-Isrc/ \
		-DGTKMM_DISABLE_DEPRECATED \
		`pkg-config gtkmm-3.0 --cflags` \
		`pkg-config icu-uc icu-io --libs --cflags` \
		-Werror \

LDFLAGS= \
		-L. \
		-g -ggdb \
		-lboost_regex \
		`pkg-config gtkmm-3.0 --libs` \
		`pkg-config icu-uc icu-io --libs --cflags` \
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

