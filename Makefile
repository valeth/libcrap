PROJECT = crap

VERSION_MAJOR = 0
VERSION_MINOR = 1
VERSION_PATCH = 0
VERSION = $(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH)

CFLAGS = -Wall -Wextra -Werror -std=c99 -O2 -Isrc
LDFLAGS =

BUILD_DIR = build
SRC_DIR   = src
SOURCES   = $(wildcard $(SRC_DIR)/**/*.c $(SRC_DIR)/*.c)
OBJECTS   = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))
TARGET    = $(BUILD_DIR)/lib$(PROJECT).a
TARGET_SO = $(patsubst %.a, %.so, $(TARGET))

TESTS_DIR = tests
TESTS_SRC = $(wildcard $(TESTS_DIR)/*_test.c)
TESTS     = $(patsubst %.c, %, $(TESTS_SRC))


# --- Build ---

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | builddir
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

$(TARGET_SO): $(OBJECTS) | builddir
	$(CC) $(CFLAGS) -shared -o $@ $(OBJECTS)
	@ln -srf $(TARGET_SO) $(TARGET_SO).$(VERSION_MAJOR)
	@ln -srf $(TARGET_SO) $(TARGET_SO).$(VERSION_MAJOR).$(VERSION_MINOR)
	@ln -srf $(TARGET_SO) $(TARGET_SO).$(VERSION)

# r: replace existing or inset new files into archive
# c: no warning if library had to be created
# s: create an archive index
# v: verbose output
$(TARGET): $(OBJECTS) | builddir
	ar rcsv $@ $^


.PHONY: builddir clean tests

all: shared

shared: $(TARGET_SO)

static: $(TARGET)

builddir:
	@mkdir -pv $(BUILD_DIR)/objects

clean:
	@rm -vr $(BUILD_DIR)


# --- Tests ---
test: $(TESTS)
	@tests/test_exec.py

$(TESTS_DIR)/%_test: $(TESTS_DIR)/%_test.c | shared
	$(CC) $(CFLAGS) -Itests -L$(PWD)/build -lcrap -ldl -o $@ $<
