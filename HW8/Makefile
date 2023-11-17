CC = gcc
CFLAG = -std=c11 -O2 -Wall
TARGET = assignment8
SRCS = assignment8.c
OBJS = assignment8.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAG) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
