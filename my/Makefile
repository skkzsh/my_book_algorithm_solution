CXX = clang++
CXXFLAGS = -Wall -Wextra -O2 -std=c++20 # -g -lpthread
CXXFLAGS += -lgtest_main -lgtest

TYPE_HEADER = type.h
TEMPLATE_HEADER = template.hpp

TARGETS = $(basename $(wildcard q[01][0-9]_[0-9][0-9].cpp))
USE_TYPE_TARGETS = q04_06
# USE_TEMPLATE_TARGETS = q05_01 q05_04 q05_06 q05_07
# C20_TARGETS = q04_05 q05_01 q05_08  # std::ranges

all: $(TARGETS)

$(USE_TYPE_TARGETS): $(USE_TYPE_TARGETS).cpp $(TYPE_HEADER)
	$(CXX) $(CXXFLAGS) $< -o $@

# FIXME: 指定を絞る
q05_%: q05_%.cpp $(TEMPLATE_HEADER)
	$(CXX) $(CXXFLAGS) $< -o $@

testall: $(TARGETS)
	for t in $(TARGETS); do echo "[$$t]"; ./$$t; done

clean:
	$(RM) $(TARGETS)

.PHONY: testall clean
