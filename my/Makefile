CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -std=c++20 # -g
CXXFLAGS += -lgtest_main -lgtest -lpthread

TYPE_HEADER = type.h
TEMPLATE_HEADER = template.hpp

TARGETS = $(basename $(wildcard *[01][0-9]_[0-9][0-9].cpp))
USE_TYPE_TARGETS = q04_06
# USE_TEMPLATE_TARGETS = q05_01 q05_04 q05_06 q05_07 code07_03 q07_02 q07_03 q09_03
# C++20未満のターゲット (MacでC++20をcompileしづらいため)
C20LESS_TARGETS = q03_06 q03_07 q04_01 q04_06 q05_02 q05_04 q05_05 q05_06 code07_03 q07_01 q07_02 q07_03 q09_02 q09_03

all: $(TARGETS)

c20less: $(C20LESS_TARGETS)

$(USE_TYPE_TARGETS): $(USE_TYPE_TARGETS).cpp $(TYPE_HEADER)
	$(CXX) $(CXXFLAGS) $< -o $@

# FIXME: 指定を絞る
q05_%: q05_%.cpp $(TEMPLATE_HEADER)
	$(CXX) $(CXXFLAGS) $< -o $@

testall: $(TARGETS)
	./runall.sh $(TARGETS)

c20lesstestall: $(C20LESS_TARGETS)
	./runall.sh $(C20LESS_TARGETS)

clean:
	$(RM) $(TARGETS)

c20lessclean:
	$(RM) $(C20LESS_TARGETS)

.PHONY: testall clean c20less c20lesstestall c20lessclean
