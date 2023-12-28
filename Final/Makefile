CC = gcc
CFLAGS = -pthread
TARGETS = q1 q2 q3
SRCS = q1.c q2.c q3.c

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f  $(TARGETS)
