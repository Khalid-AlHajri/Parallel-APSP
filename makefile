OBJDIR = build
TARGETDIR = bin

SOURCES = main.c bh.c algorithms.c adjlist.c util.c
OBJECTS = $(patsubst %.c,$(OBJDIR)/%.o,$(SOURCES))
TEST_OBJS = $(OBJDIR)/tests_bh.o

.PHONY: all clean tests

all: $(TARGETDIR)/main

tests: $(TARGETDIR)/tests

# Link the main binary
$(TARGETDIR)/main: $(OBJECTS)
	@mkdir -p $(TARGETDIR)
	gcc -o $@ $^

# Compile each .c to .o
$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	gcc -c $< -o $@

# Special target for test binary
$(TARGETDIR)/tests: $(OBJDIR)/bh.o $(OBJDIR)/algorithms.o $(OBJDIR)/adjlist.o $(OBJDIR)/tests_bh.o $(OBJDIR)/util.o
	@mkdir -p $(TARGETDIR)
	gcc -o $@ $^

clean:
	rm -rf $(OBJDIR) $(TARGETDIR)
