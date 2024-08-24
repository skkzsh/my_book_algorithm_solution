CXX := g++
CXX_BASE_FLAGS ?= -Wall -Wextra -std=c++2b # -O2
CXXFLAGS ?= $(CXX_BASE_FLAGS) -lgtest_main -lgtest -lpthread
# -g
# pkg-config --cflags --libs gtest_main gtest

TYPE_HDR := type.h
TEMPLATE_HDR := template.hpp
GTEST_HELPER_HDR := gtest-helper.hpp

UNION_FIND_SRC := union-find.cpp
UNION_FIND_OBJ := $(UNION_FIND_SRC:.cpp=.o)
UNION_FIND_HDR := $(UNION_FIND_SRC:.cpp=.hpp)

GRAPH_SRC := graph.cpp
GRAPH_OBJ := $(GRAPH_SRC:.cpp=.o)
GRAPH_HDR := $(GRAPH_SRC:.cpp=.hpp)

TARGETS := $(basename $(wildcard *[01][0-9]_[0-9][0-9].cpp))
TARGETS_WITH_GTEST_HELPER := q05_01 code07_03 q07_01 q07_02 q09_02 q09_03
TARGETS_WITH_TYPE := q04_06
TARGETS_WITH_TEMPLATE := q05_04 q05_06 q05_07 q05_08 q05_09 q06_03 q07_03
TARGETS_WITH_UNION_FIND := code11_% q11_%
TARGETS_WITH_GRAPH := code13_% q13_%

# C++23とC++23未満のターゲットで分割
# (cartesian_product や enumerate が Mac で compile しづらいため)
TARGETS_C23 := q03_06 q06_03 q06_05 q13_04 # q09_03
TARGETS_C23LESS := $(filter-out $(TARGETS_C23), $(TARGETS))

RUN_SCRIPT := ./runall.sh

# Apple Silicon だと /opt/homebrew 配下に gtest が置かれる
ifeq ($(shell uname -p), arm)
    export CPLUS_INCLUDE_PATH := /opt/homebrew/include:$(CPLUS_INCLUDE_PATH)
    # export CPATH := /opt/homebrew/include:$(CPATH)
    export LIBRARY_PATH := /opt/homebrew/lib:$(LIBRARY_PATH)
endif

all: $(TARGETS)

c23: $(TARGETS_C23)
c23less: $(TARGETS_C23LESS)

$(TARGETS_WITH_GTEST_HELPER): %: %.cpp $(GTEST_HELPER_HDR) $(TEMPLATE_HDR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(TARGETS_WITH_TYPE): %: %.cpp $(TYPE_HDR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(TARGETS_WITH_TEMPLATE): %: %.cpp $(TEMPLATE_HDR)
	$(CXX) $(CXXFLAGS) $< -o $@

# TODO: rm *11_*.o されるのを調査 (cleanに追加)

define CXX_WITH_UNION_FIND
$(1): $(1).o $(UNION_FIND_OBJ) $(GRAPH_OBJ)
	$(CXX) $(CXXFLAGS) $$^ -o $$@

$(1).o: $(1).cpp $(UNION_FIND_HDR) $(GRAPH_HDR) $(TEMPLATE_HDR) $(GTEST_HELPER_HDR)
endef

$(foreach T, $(TARGETS_WITH_UNION_FIND), $(eval $(call CXX_WITH_UNION_FIND, $(T))))

define CXX_WITH_GRAPH
$(1): $(1).o $(GRAPH_OBJ)
	$(CXX) $(CXXFLAGS) $$^ -o $$@

$(1).o: $(1).cpp $(GRAPH_HDR)
endef

$(foreach T, $(TARGETS_WITH_GRAPH), $(eval $(call CXX_WITH_GRAPH, $(T))))

$(UNION_FIND_OBJ): $(UNION_FIND_SRC) $(UNION_FIND_HDR)
$(GRAPH_OBJ): $(GRAPH_SRC) $(GRAPH_HDR) $(TEMPLATE_HDR)

.cpp.o:
	$(CXX) $(CXX_BASE_FLAGS) -c $<

testall: $(TARGETS)
	$(RUN_SCRIPT) $(TARGETS)

c23testall: $(TARGETS_C23)
	$(RUN_SCRIPT) $(TARGETS_C23)
c23lesstestall: $(TARGETS_C23LESS)
	$(RUN_SCRIPT) $(TARGETS_C23LESS)

clean:
	$(RM) $(TARGETS) $(UNION_FIND_OBJ) $(GRAPH_OBJ)

c23clean:
	$(RM) $(TARGETS_C23) $(UNION_FIND_OBJ) $(GRAPH_OBJ)
c23lessclean:
	$(RM) $(TARGETS_C23LESS) $(UNION_FIND_OBJ) $(GRAPH_OBJ)

.PHONY: testall clean c23 c23testall c23clean c23less c23lesstestall c23lessclean
