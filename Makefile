# Makefile — Simulated Annealing para SEP
# Fontes em src/, objetos em build/, executável na raiz

CC := gcc
override CFLAGS += -Wall -Werror -g -fmax-errors=99 -Wuninitialized -Wmissing-prototypes -Wredundant-decls -Wno-unused-result -O2 -I/usr/local/include
LIBS := -L/usr/local/lib -Wl,-rpath -Wl,/usr/local/lib -Wl,--enable-new-dtags -leps -lhsl_ma48 -lblas -lgfortran -lm -lquadmath

SRCDIR := src
BUILDDIR := build

SRCS := $(SRCDIR)/main.c $(SRCDIR)/sa_power.c $(SRCDIR)/power_system_functions.c
OBJS := $(BUILDDIR)/main.o $(BUILDDIR)/sa_power.o $(BUILDDIR)/power_system_functions.o

.PHONY: all clean test mem_test

all: main.exe

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/main.o: $(SRCDIR)/main.c $(SRCDIR)/power_system_functions.h $(SRCDIR)/sa_power.h | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $(SRCDIR)/main.c -o $(BUILDDIR)/main.o

$(BUILDDIR)/sa_power.o: $(SRCDIR)/sa_power.c $(SRCDIR)/sa_power.h $(SRCDIR)/power_system_functions.h | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $(SRCDIR)/sa_power.c -o $(BUILDDIR)/sa_power.o

$(BUILDDIR)/power_system_functions.o: $(SRCDIR)/power_system_functions.c $(SRCDIR)/power_system_functions.h | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $(SRCDIR)/power_system_functions.c -o $(BUILDDIR)/power_system_functions.o

main.exe: $(OBJS)
	$(CC) $(CFLAGS) -o main.exe $(OBJS) $(LIBS)

test: main.exe
	./main.exe

mem_test: main.exe
	valgrind --tool=memcheck ./main.exe

clean:
	rm -f $(BUILDDIR)/*.o main.exe
	rm -rf $(BUILDDIR)
