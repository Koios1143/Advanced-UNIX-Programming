CC = gcc
CFLAG = -std=c11 -O2 -Wall
TARGET = assignment2
SRCS = assignment2.c
OBJS = assignment2.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAG) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
