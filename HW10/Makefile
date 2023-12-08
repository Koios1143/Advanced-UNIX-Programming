CC = gcc
CFLAG = -std=c11 -g -pthread -Wall
TARGET = assignment10
SRCS = assignment10.c
OBJS = assignment10.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAG) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
