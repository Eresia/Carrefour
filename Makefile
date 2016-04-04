EXE=project
CFLAGS= -Wall
LDFLAGS= -lpthread

SRC= $(wildcard *.c)

OBJDIR=bin
OBJ= $(SRC:%.c=$(OBJDIR)/%.o)

all: $(EXE)

$(EXE): $(OBJ)
	gcc -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: %.c *.h
	@mkdir bin -p
	gcc -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(OBJDIR)

mrproper: clean
	rm -f $(EXE)
