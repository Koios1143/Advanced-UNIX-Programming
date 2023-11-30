CC = gcc
CFLAG = -std=c11 -pthread -O2 -Wall
TARGET = assignment9
SRCS = assignment9.c
OBJS = assignment9.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAG) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
