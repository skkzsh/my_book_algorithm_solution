CXX = clang++
CXXFLAGS = -Wall -Wextra -O2 -lm # -g -lpthread
CXXFLAGS += -std=c++11 -lgtest_main -lgtest
TARGETS = q03_06 q03_07 q04_01

all: $(TARGETS)

testall: $(TARGETS)
	for t in $(TARGETS); do ./$$t; done

clean:
	$(RM) $(TARGETS)

.PHONY: clean
