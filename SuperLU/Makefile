CC=gcc
CFLAGS= -o -W -g
LDFLAGS= -lm -lsuperlu
OBJFILES = main.o leitura.o matriz.o
TARGET = output

all: $(TARGET)

$(TARGET): $(OBJFILES)
		$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~ 