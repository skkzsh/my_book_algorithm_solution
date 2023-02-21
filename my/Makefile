CXX = g++
CXX_BASE_FLAGS = -Wall -Wextra -O2 -std=c++20
CXXFLAGS = $(CXX_BASE_FLAGS) -lgtest_main -lgtest -lpthread
# -g

TYPE_HEADER = type.h
TEMPLATE_HEADER = template.hpp

UNION_FIND_SRC = union-find.cpp
UNION_FIND_OBJ = $(UNION_FIND_SRC:.cpp=.o)
UNION_FIND_HEADER = $(UNION_FIND_SRC:.cpp=.hpp)

TARGETS = $(basename $(wildcard *[01][0-9]_[0-9][0-9].cpp))
USE_TYPE_TARGETS = q04_06
# USE_TEMPLATE_TARGETS = q05_01 q05_04 q05_06 q05_07 code07_03 q07_02 q07_03 q09_03
# C++20未満のターゲット (MacでC++20をcompileしづらいため)
C20LESS_TARGETS = q03_06 q03_07 q04_01 q04_06 q05_02 q05_04 q05_05 q05_06 code07_03 q07_01 q07_02 q07_03 q09_02 q09_03 code11_03

RUN_SCRIPT = ./runall.sh

all: $(TARGETS)

c20less: $(C20LESS_TARGETS)

$(USE_TYPE_TARGETS): $(USE_TYPE_TARGETS).cpp $(TYPE_HEADER)
	$(CXX) $(CXXFLAGS) $< -o $@

# FIXME: 指定を絞る
q05_%: q05_%.cpp $(TEMPLATE_HEADER)
	$(CXX) $(CXXFLAGS) $< -o $@

# TODO: rm code11_03.o されるのを調査 (cleanに追加)
code11_%: code11_%.o $(UNION_FIND_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

code11_%.o: code11_%.cpp $(UNION_FIND_HEADER)
$(UNION_FIND_OBJ): $(UNION_FIND_SRC) $(UNION_FIND_HEADER)

.cpp.o:
	$(CXX) $(CXX_BASE_FLAGS) -c $<

testall: $(TARGETS)
	$(RUN_SCRIPT) $(TARGETS)

c20lesstestall: $(C20LESS_TARGETS)
	$(RUN_SCRIPT) $(C20LESS_TARGETS)

clean:
	$(RM) $(TARGETS) $(UNION_FIND_OBJ)

c20lessclean:
	$(RM) $(C20LESS_TARGETS) $(UNION_FIND_OBJ)

.PHONY: testall clean c20less c20lesstestall c20lessclean
