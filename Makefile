CC=gcc
CFLAGS= -o -W -g -Wall
LIBS= -L/usr/local/lib 
LDFLAGS= -lm -llapacke -lblas
OBJFILES = main.o leitura.o matriz.o
TARGET = a

all: $(TARGET)

$(TARGET): $(OBJFILES)
		$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS) $(LIBS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~ 