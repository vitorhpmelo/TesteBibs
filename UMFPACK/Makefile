CC=gcc
CFLAGS= -o -W -g -Wall
LDFLAGS= -lm -lumfpack
OBJFILES = teste.o matriz.o leitura.o numref.o
TARGET = teste

all: $(TARGET)

$(TARGET): $(OBJFILES)
		$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~ 