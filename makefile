# ====================================================
# Variables
# ====================================================
SRC := $(shell find src -name "*.c")
OBJ := $(patsubst src/%.c,build/%.o,$(SRC))
DEP := $(OBJ:.o=.d)

CC := gcc
AR := ar
RM := rm -rf

DEPFLAGS := -MMD -MP
CFLAGS := -Iinclude -Wall -Wextra $(DEPFLAGS)
RELEASEFLAGS := -O3 -Iinclude $(DEPFLAGS)
LDFLAGS := 

TARGET := engine

# ====================================================
# Main Rules
# ====================================================
.PHONY: all release clean

all: bin/$(TARGET)

release: CFLAGS := $(RELEASEFLAGS)
release: bin/$(TARGET)
	mkdir -p lib
	ar rcs lib/lib$(TARGET).a $(OBJ)

# ====================================================
# Executable
# ====================================================
bin/$(TARGET): $(OBJ)
	mkdir -p bin
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)

# ====================================================
# Object Compiling
# ====================================================
build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# ====================================================
# Automatic Dependencies
# ====================================================
-include $(DEP)

# ====================================================
# Cleaning
# ====================================================
clean:
	$(RM) build bin lib