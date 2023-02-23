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
TARGETS_WITH_TYPE = q04_06
TARGETS_WITH_TEMPLATE = q05_04 q05_06 q05_07 q05_08 q05_09 q06_03 code07_03 q07_02 q07_03 q09_03
TARGETS_WITH_UNION_FIND = code11_% q11_%
# C++20未満のターゲット (MacでC++20をcompileしづらいため)
C20LESS_TARGETS = q03_06 q03_07 q04_01 q04_06 q05_02 q05_04 q05_05 q05_06 code07_03 q07_01 q07_02 q07_03 q09_02 q09_03

RUN_SCRIPT = ./runall.sh

all: $(TARGETS)

c20less: $(C20LESS_TARGETS)

$(TARGETS_WITH_TYPE): $(TARGETS_WITH_TYPE).cpp $(TYPE_HEADER)
	$(CXX) $(CXXFLAGS) $< -o $@

define CXX_WITH_TEMPLATE
$(1): $(1).cpp $(TEMPLATE_HEADER)
	$(CXX) $(CXXFLAGS) $$< -o $$@
endef

$(foreach T, $(TARGETS_WITH_TEMPLATE), $(eval $(call CXX_WITH_TEMPLATE, $(T))))

# TODO: rm *11_*.o されるのを調査 (cleanに追加)
define CXX_WITH_UNION_FIND
$(1): $(1).o $(UNION_FIND_OBJ)
	$(CXX) $(CXXFLAGS) $$^ -o $$@

$(1).o: $(1).cpp $(UNION_FIND_HEADER)
endef

$(foreach T, $(TARGETS_WITH_UNION_FIND), $(eval $(call CXX_WITH_UNION_FIND, $(T))))

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
	$(RM) $(C20LESS_TARGETS)

.PHONY: testall clean c20less c20lesstestall c20lessclean
