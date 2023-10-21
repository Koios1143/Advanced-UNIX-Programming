CC = gcc
CFLAG = -std=c11 -O2 -Wall
TARGET = assignment4
SRCS = assignment4.c
OBJS = assignment4.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAG) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

test1:
	@env TZ=Asia/Taipei ./$(TARGET)
test2:
	@env TZ=NZ ./$(TARGET)
