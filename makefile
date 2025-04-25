OBJDIR = build
TARGETDIR = bin

SOURCES = main.c bh.c algorithms.c adjlist.c util.c
OBJECTS = $(patsubst %.c,$(OBJDIR)/%.o,$(SOURCES))
TEST_OBJS = $(OBJDIR)/tests_bh.o
PERF_TEST_OBJ = $(OBJDIR)/test_performance.o
VALID_TEST_OBJ = $(OBJDIR)/validation_test.o

.PHONY: all clean tests

all: $(TARGETDIR)/main

tests: $(TARGETDIR)/tests
perf_bench: $(TARGETDIR)/test_performance
test_valid: $(TARGETDIR)/validation_test

# Link the main binary
$(TARGETDIR)/main: $(OBJECTS)
	@mkdir -p $(TARGETDIR)
	gcc -o $@ $^ -O3

# Compile each .c to .o
$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	gcc -c $< -o $@

$(TARGETDIR)/test_performance: $(PERF_TEST_OBJ) $(OBJDIR)/bh.o $(OBJDIR)/algorithms.o $(OBJDIR)/adjlist.o $(OBJDIR)/util.o
	@mkdir -p $(TARGETDIR)
	gcc -o $@ $^ -O3

$(TARGETDIR)/validation_test: $(VALID_TEST_OBJ) $(OBJDIR)/bh.o $(OBJDIR)/algorithms.o $(OBJDIR)/adjlist.o $(OBJDIR)/util.o
	@mkdir -p $(TARGETDIR)
	gcc -o $@ $^ -O3

# Special target for test binary
$(TARGETDIR)/tests: $(OBJDIR)/bh.o $(OBJDIR)/algorithms.o $(OBJDIR)/adjlist.o $(OBJDIR)/tests_bh.o $(OBJDIR)/util.o
	@mkdir -p $(TARGETDIR)
	gcc -o $@ $^

clean:
	rm -rf $(OBJDIR) $(TARGETDIR)
