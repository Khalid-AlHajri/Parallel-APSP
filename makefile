OBJDIR = build
TARGETDIR = bin

.PHONY: all clean

all: $(TARGETDIR)/main
tests: $(TARGETDIR)/tests


$(TARGETDIR)/main: $(OBJDIR)/main.o $(OBJDIR)/bh.o
	@mkdir -p $(TARGETDIR)
	gcc -o $@ $^

$(OBJDIR)/bh.o: bh.h bh.c
	@mkdir -p $(OBJDIR)
	gcc -c bh.c -o $@

$(OBJDIR)/main.o: bh.h main.c
	@mkdir -p $(OBJDIR)
	gcc -c main.c -o $@

$(TARGETDIR)/tests: bh.h tests_bh.c
	gcc tests_bh.c bh.c -o ${TARGETDIR}/tests

clean:
	rm -f $(OBJDIR)/*.o $(TARGETDIR)/main
