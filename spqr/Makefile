CC=gcc
CFLAGS= -o -W -g -Wall -Wextra -Wformat -Wnonnull
LDFLAGS= -lm -lumfpack -lcholmod -lspqr -lsuitesparseconfig 
OBJFILES = main.o matriz.o leitura.o numref.o
TARGET = teste

all: $(TARGET)

$(TARGET): $(OBJFILES)
		$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~ 