CC = gcc
CFLAG = -std=c11 -O2 -Wall
TARGETS = q1 q2 q3 q4
SRCS = q1.c q2.c q3.c q4.c
OBJS = q1.o q2.o q3.o q4.o

all: $(TARGETS)

q%: q%.o
	$(CC) $(CFLAG) $^ -o $@

q%.o: q%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(TARGETS)
