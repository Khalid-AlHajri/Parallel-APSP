OBJDIR = build
TARGETDIR = bin

.PHONY: all clean

all: $(TARGETDIR)/main


$(TARGETDIR)/main: $(OBJDIR)/main.o $(OBJDIR)/bh.o
	@mkdir -p $(TARGETDIR)
	gcc -o $@ $^

$(OBJDIR)/bh.o: bh.h bh.c
	@mkdir -p $(OBJDIR)
	gcc -c bh.c -o $@

$(OBJDIR)/main.o: bh.h main.c
	@mkdir -p $(OBJDIR)
	gcc -c main.c -o $@

clean:
	rm -f $(OBJDIR)/*.o $(TARGETDIR)/main
