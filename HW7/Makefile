CC = gcc
CFLAG = -std=c11 -O2 -Wall
TARGET = assignment7
SRCS = assignment7.c
OBJS = assignment7.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAG) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
