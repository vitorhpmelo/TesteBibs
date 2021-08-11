CC=gcc
CFLAGS= -o -W -g -Wall
LIBS= -L/usr/local/lib -llapack -lblas
LDFLAGS= -lm 
OBJFILES = main.o leitura.o matriz.o
TARGET = output

all: $(TARGET)

$(TARGET): $(OBJFILES)
		$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS) $(LIBS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~ 