CC = gcc
CFLAG = -std=c11 -O2 -Wall
TARGET = q2
SRCS = q2.c
OBJS = q2.o
ORZ = output1 output2 output3 output4 output5

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAG) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(ORZ)
