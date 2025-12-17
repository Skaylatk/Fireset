# ====================================================
# Project
# ====================================================
TARGET := fireset

# ====================================================
# Tools
# ====================================================
CC := gcc
AR := ar
RM := rm -rf

# ====================================================
# Sources
# ====================================================
SRC := $(shell find src -name "*.c")
LIB_SRC := $(filter-out src/main.c,$(SRC))

# ====================================================
# Build dirs (default = debug)
# ====================================================
BUILD_DIR := build/debug

# ====================================================
# Objects
# ====================================================
OBJ := $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SRC))
LIB_OBJ := $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(LIB_SRC))
DEP := $(OBJ:.o=.d)

# ====================================================
# Flags
# ====================================================
DEPFLAGS := -MMD -MP

CFLAGS := -g -O0 -Wall -Wextra -Iinclude $(DEPFLAGS)
LDFLAGS := -lglfw -lGL -lm

# ====================================================
# Outputs (same names)
# ====================================================
BIN := bin/$(TARGET)
LIB := lib/lib$(TARGET).a

# ====================================================
# Phony
# ====================================================
.PHONY: all debug release clean

# ====================================================
# High-level targets
# ====================================================
all: debug

debug: $(BIN) $(LIB)

doc:
	doxygen Doxyfile

STAGE      := fireset-dev
PKGNAME    := fireset-dev
VERSION    := 0.1.0
LIB        := lib/libfireset.a

DEBIANDIR  := $(STAGE)/DEBIAN
USRDIR     := $(STAGE)/usr
LIBDIR     := $(USRDIR)/lib
INCDIR     := $(USRDIR)/include/fireset
DOCDIR     := $(USRDIR)/share/doc/$(PKGNAME)
PCDIR      := $(LIBDIR)/pkgconfig
OVERRIDEDIR := $(USRDIR)/share/lintian/overrides

deb:
	@set -e

	rm -rf $(STAGE)

	mkdir -p $(DEBIANDIR) $(LIBDIR) $(INCDIR) $(DOCDIR) $(PCDIR)

	cp $(LIB) $(LIBDIR)/
	cp include/fireset/*.h $(INCDIR)/

	cp debian/control $(DEBIANDIR)/
	cp debian/copyright $(DOCDIR)/
	cp debian/changelog $(DOCDIR)/changelog
	cp LICENSE $(DOCDIR)/

	mkdir -p $(OVERRIDEDIR)
	cp debian/fireset-dev.lintian-overrides $(OVERRIDEDIR)/fireset-dev

	cp debian/fireset.pc $(PCDIR)/

	gzip -n -9 $(DOCDIR)/changelog

	find $(STAGE) -type d -exec chmod 755 {} +
	find $(STAGE) -type f -exec chmod 644 {} +

	dpkg-deb --build --root-owner-group $(STAGE)

	lintian $(STAGE).deb

release: BUILD_DIR := build/release
release: CFLAGS := -O3 -Wall -Wextra -Iinclude $(DEPFLAGS)
release: $(BIN) $(LIB)

# ====================================================
# Executable
# ====================================================
$(BIN): $(OBJ)
	@mkdir -p bin
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# ====================================================
# Static library (sem main.c)
# ====================================================
$(LIB): $(LIB_OBJ)
	@mkdir -p lib
	$(AR) rcs $@ $^

# ====================================================
# Object compilation
# ====================================================
$(BUILD_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# ====================================================
# Dependencies
# ====================================================
-include $(DEP)

# ====================================================
# Cleaning
# ====================================================
clean:
	$(RM) build bin lib docs fireset-dev.deb fireset-dev