CC = gcc
CFLAG = -std=c11 -g -Wall
TARGET = assignment12
SRCS = assignment12.c
OBJS = assignment12.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAG) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
