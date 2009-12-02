CC      =   gcc-4
CCFLAGS =   -Werror -ansi -pedantic

COBJ    =   number_theory.o

CINC    =
CLIB    =   -lgmp

TEST    =   test.exe

all:    $(TEST)

.c.o:
	$(CC) $(CCFLAGS) $(CINC) -c $^ -o $@

$(TEST): $(COBJ)
	$(CC) $(CCFLAGS) -o $@ $^ $(CLIB)

clean:
	rm -rf *.o *~ $(TEST)
