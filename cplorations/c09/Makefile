CC = gcc
CFLAGS = -Wall -I.
LDFLAGS = 
OBJFILES = main.o error.o symtable.o parser.o
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~