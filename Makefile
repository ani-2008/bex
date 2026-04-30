CC = gcc
TARGET = bex 
SRC = src/bex.c 

all:
	$(CC) $(SRC) -o $(TARGET)
clean:
	rm -f $(TARGET)
