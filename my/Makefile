CXX = clang++
CXXFLAGS = -Wall -Wextra -O2 -lm # -g -lpthread
CXXFLAGS += -std=c++11 -lgtest_main -lgtest

#TYPE_HEADER = type.h

TARGETS = $(patsubst %.cpp, %, $(wildcard q[01][0-9]_[0-9][0-9].cpp))

all: $(TARGETS)

testall: $(TARGETS)
	for t in $(TARGETS); do echo "[$$t]"; ./$$t; done

clean:
	$(RM) $(TARGETS)

.PHONY: testall clean
