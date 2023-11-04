CC = gcc
CFLAG = -std=c11 -O2 -Wall
TARGET = assignment6
SRCS = assignment6.c
OBJS = assignment6.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAG) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
