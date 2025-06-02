ifeq ($(shell uname -s), Darwin)
	CXX_STD := c++23
	# CXX_STD := c++2c
else
	CXX_STD := c++23
	# CXX_STD := c++2c
endif

CXX := g++
CXX_BASE_FLAGS ?= -Wall -Wextra -std=$(CXX_STD) # -O2
CXXFLAGS ?= $(CXX_BASE_FLAGS) -lgtest_main -lgtest -lpthread # -g
# pkg-config --cflags --libs gtest_main

RUN_SCRIPT := ./runall.sh

TYPE_HDR := type.h
TEMPLATE_HDR := template.hpp
GTEST_HELPER_HDR := gtest-helper.hpp

UNION_FIND_SRC := union-find.cpp
UNION_FIND_OBJ := $(UNION_FIND_SRC:.cpp=.o)
UNION_FIND_HDR := $(UNION_FIND_SRC:.cpp=.hpp)

GRAPH_SRC := graph.cpp
GRAPH_OBJ := $(GRAPH_SRC:.cpp=.o)
GRAPH_HDR := $(GRAPH_SRC:.cpp=.hpp)

TARGETS := $(basename $(wildcard *[01][0-9]_[0-9][0-9]*.cpp))
TARGETS_WITH_GTEST_HELPER := q05_01 code07_03 q07_01 q07_02 q09_02 q09_03
TARGETS_WITH_TYPE := q04_06
TARGETS_WITH_TEMPLATE := q05_04 q05_06 q05_07 q05_08 q05_09 q06_03 q07_03
TARGETS_WITH_UNION_FIND := code11_% q11_%
TARGETS_WITH_GRAPH := code13_% q13_%

# C++23とC++23未満でターゲットを分割
# (cartesian_product, enumerate, generator などが Mac で compile しづらいため)
TARGETS_23 := q03_06 q04_01_gen q06_03 q06_05 q13_04 # q09_03
TARGETS_2B := $(filter-out $(TARGETS_23), $(TARGETS))


# Apple Silicon だと /opt/homebrew 配下に gtest が置かれるため, 自前でパスを通す
ifeq ($(shell uname -p), arm)
	export CPLUS_INCLUDE_PATH := /opt/homebrew/opt/googletest/include:$(CPLUS_INCLUDE_PATH)
	# export CPATH := /opt/homebrew/opt/googletest/include:$(CPATH)
	export LIBRARY_PATH := /opt/homebrew/opt/googletest/lib:$(LIBRARY_PATH)
endif


.PHONY: testall clean 23 23testall 23clean 2b 2btestall 2bclean

all: $(TARGETS)

$(TARGETS_WITH_GTEST_HELPER): %: %.cpp $(GTEST_HELPER_HDR) $(TEMPLATE_HDR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(TARGETS_WITH_TYPE): %: %.cpp $(TYPE_HDR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(TARGETS_WITH_TEMPLATE): %: %.cpp $(TEMPLATE_HDR)
	$(CXX) $(CXXFLAGS) $< -o $@

# TODO: rm *11_*.o されるのを調査 (cleanに追加)

define CXX_WITH_UNION_FIND
$(1): $(1).o $(UNION_FIND_OBJ) $(GRAPH_OBJ)
	$$(CXX) $$(CXXFLAGS) $$^ -o $$@

$(1).o: $(1).cpp $(UNION_FIND_HDR) $(GRAPH_HDR) $(TEMPLATE_HDR) $(GTEST_HELPER_HDR)
endef

$(foreach T, $(TARGETS_WITH_UNION_FIND), $(eval $(call CXX_WITH_UNION_FIND, $(T))))


define CXX_WITH_GRAPH
$(1): $(1).o $(GRAPH_OBJ)
	$$(CXX) $$(CXXFLAGS) $$^ -o $$@

$(1).o: $(1).cpp $(GRAPH_HDR)
endef

$(foreach T, $(TARGETS_WITH_GRAPH), $(eval $(call CXX_WITH_GRAPH, $(T))))


$(UNION_FIND_OBJ): $(UNION_FIND_SRC) $(UNION_FIND_HDR)
$(GRAPH_OBJ): $(GRAPH_SRC) $(GRAPH_HDR) $(TEMPLATE_HDR)


.cpp.o:
	$(CXX) $(CXX_BASE_FLAGS) -c $<

testall: $(TARGETS)
	$(RUN_SCRIPT) $(TARGETS)

clean:
	$(RM) $(TARGETS) $(UNION_FIND_OBJ) $(GRAPH_OBJ)


UPPERCASE = $(shell echo $(1) | tr [:lower:] [:upper:])

# 与えられたターゲットに対して, ルール一式を作るマクロ
define GENERATE_RULES
$(1): $$(TARGETS_$(call UPPERCASE, $(1)))

$(1)testall: $$(TARGETS_$(call UPPERCASE, $(1)))
	$$(RUN_SCRIPT) $$(TARGETS_$(call UPPERCASE, $(1)))

$(1)clean:
	$$(RM) $$(TARGETS_$(call UPPERCASE, $(1))) $$(UNION_FIND_OBJ) $$(GRAPH_OBJ)
endef

$(foreach T, 23 2b, $(eval $(call GENERATE_RULES, $(T))))
