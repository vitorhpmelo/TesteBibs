CC=gcc
CFLAGS= -o -W -g
LDFLAGS= -lm -llapacke -lblas -llapack
OBJFILES = main.o leitura.o matriz.o
TARGET = output

all: $(TARGET)

$(TARGET): $(OBJFILES)
		$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~ 