CC = gcc
CFLAG = -std=c11 -O2 -Wall
TARGET = assignment3
SRCS = assignment3.c
OBJS = assignment3.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAG) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
