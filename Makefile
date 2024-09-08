

CC:=g++
CSTD_FLAG:=-std=c++17
FLAGS:=-Wall -Wextra -Wpedantic $(CSTD_FLAG)

PROJ_DIR:=$(shell git rev-parse --show-toplevel)

BUILD_DIR:=$(PROJ_DIR)/build
LIB_OUT_DIR:=$(BUILD_DIR)/lib
TEST_OUT_DIR:=$(BUILD_DIR)/test

LIB_FILE:=$(LIB_OUT_DIR)/libgfx.a

INCLUDE_DIR:=$(PROJ_DIR)/include
FULL_INCLUDE_HEADERS:=$(wildcard $(INCLUDE_DIR)/gfx/*.h)

SRC_DIR:=$(PROJ_DIR)/src
SRC_SRCS:=vec.cpp \
		  img.cpp

FULL_SRC_SRCS:=$(addprefix $(SRC_DIR)/,$(SRC_SRCS))

SRC_OBJS:=$(patsubst %.cpp,%.o,$(SRC_SRCS))
FULL_SRC_OBJS:=$(addprefix $(LIB_OUT_DIR)/,$(SRC_OBJS))

TEST_DIR:=$(PROJ_DIR)/test
TEST_SRCS:=main.cpp

FULL_TEST_SRCS:=$(addprefix $(TEST_DIR)/,$(TEST_SRCS))
FULL_TEST_HEADERS:=$(wildcard $(TEST_DIR)/*.h)

TEST_OBJS:=$(patsubst %.cpp,%.o,$(TEST_SRCS))
FULL_TEST_OBJS:=$(addprefix $(TEST_OUT_DIR)/,$(TEST_OBJS))

.PHONY: all lib test run clangd clean

all: lib test

$(BUILD_DIR) $(LIB_OUT_DIR) $(TEST_OUT_DIR):
	mkdir -p $@

$(LIB_OUT_DIR)/%.o: $(SRC_DIR)/%.cpp $(FULL_INCLUDE_HEADERS) | $(LIB_OUT_DIR)
	$(CC) $(FLAGS) $< -I$(INCLUDE_DIR) -c -o $@

lib: $(LIB_FILE)
$(LIB_FILE): $(FULL_SRC_OBJS)
	ar rcs $@ $^


$(TEST_OUT_DIR)/%.o: $(TEST_DIR)/%.cpp $(FULL_TEST_HEADERS) $(FULL_INCLUDE_HEADERS) | $(TEST_OUT_DIR)
	$(CC) $(FLAGS) $< -I$(TEST_DIR) -I$(INCLUDE_DIR) -c -o $@

test: $(TEST_OUT_DIR)/test
$(TEST_OUT_DIR)/test: $(FULL_TEST_OBJS) $(LIB_FILE)
	$(CC) $(FULL_TEST_OBJS) -L$(LIB_OUT_DIR) -lgfx -o $@

# Temporary target.
run: test
	$(TEST_OUT_DIR)/test $(BUILD_DIR)/i.ppm

clangd:
	echo "CompileFlags:" > temp.clangd
	echo "  Add:" >> temp.clangd
	echo "    - $(CSTD_FLAG)" >> temp.clangd
	echo "    - -I$(INCLUDE_DIR)" >> temp.clangd
	cp temp.clangd $(INCLUDE_DIR)/gfx/.clangd
	cp temp.clangd $(SRC_DIR)/.clangd
	echo "    - -I$(SRC_DIR)" >> $(SRC_DIR)/.clangd
	cp temp.clangd $(TEST_DIR)/.clangd
	echo "    - -I$(TEST_DIR)" >> $(TEST_DIR)/.clangd
	rm temp.clangd

clean:
	rm -rf $(BUILD_DIR)

