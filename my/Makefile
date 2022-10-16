CXX = clang++
CXXFLAGS = -Wall -Wextra -O2 -lm # -g -lpthread
CXXFLAGS += -std=c++11 -lgtest_main -lgtest
TARGETS = q03_06

all: $(TARGETS)

test: $(TARGETS)
	 for t in $(TARGETS); do ./$$t; done

clean:
	$(RM) $(TARGETS)

.PHONY: clean
