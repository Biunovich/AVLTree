TARGET_LIB=libavl_tree
TEST_EXE=test

BUILD_DIR=build
SRC_DIRS=src
TESTS_DIR=tests

RM=rm

SRCS:=$(shell find $(SRC_DIRS) -name *.c)
OBJS:=$(SRCS:%.c=$(BUILD_DIR)/%.o)

INC_DIRS:=$(shell find $(SRC_DIRS) -type d)
INC_FLAGS:=$(addprefix -I,$(INC_DIRS))

CFLAGS:=$(INC_FLAGS)
AR_FLAGS:=rsc

$(BUILD_DIR)/$(TARGET_LIB).a: $(OBJS)
	$(AR) $(AR_FLAGS) $@ $(OBJS)

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean tests

tests: $(BUILD_DIR)/$(TARGET_LIB).a
	$(CC) $(CFLAGS) $(TESTS_DIR)/$(TEST_EXE).c -o $(BUILD_DIR)/$(TEST_EXE) $(BUILD_DIR)/$(TARGET_LIB).a

clean:
	$(RM) -rf $(BUILD_DIR)
