CXX = clang++
CXXFLAGS = -Wall -Wextra -O2 -lm # -g -lpthread
CXXFLAGS += -std=c++11 -lgtest_main -lgtest
TARGETS = $(patsubst %.cpp, %, $(wildcard *.cpp))

all: $(TARGETS)

testall: $(TARGETS)
	for t in $(TARGETS); do echo "[$$t]"; ./$$t; done

clean:
	$(RM) $(TARGETS)

.PHONY: testall clean
