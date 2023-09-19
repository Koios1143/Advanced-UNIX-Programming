CC = gcc
CFLAG = -std=c11 -O2 -Wall
TARGET = assignment1
SRCS = assignment1.c
OBJS = assignment1.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAG) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
