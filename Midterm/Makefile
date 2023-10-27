CC = gcc
CFLAG = -std=c11 -O2 -Wall
TARGET = q1 q2
SRCS = q1.c q2.c
OBJS = q1.o q2.o
TMPS = output.txt output1.txt output2.txt

all: $(TARGET)

q1: q1.o
	$(CC) $(CFLAG) -o q1 q1.o
q2: q2.o
	$(CC) $(CFLAG) -o q2 q2.o


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(TMPS)

test: test1 test2 test3 test4 test5 test6 test7 test8

test1:
	@sort source1.txt | uniq - > output1.txt
	@./$(TARGET) source1.txt output2.txt
	@diff output1.txt output2.txt || echo "Test 1 failed"

test2:
	@sort source1.txt | uniq -u - > output1.txt
	@./$(TARGET) -u source1.txt output2.txt
	@diff output1.txt output2.txt || echo "Test 2 failed"

test3:
	@sort source1.txt | uniq -c - > output1.txt
	@./$(TARGET) -c source1.txt output2.txt
	@diff output1.txt output2.txt || echo "Test 3 failed"

test4:
	@sort source1.txt | uniq -i - > output1.txt
	@./$(TARGET) -i source1.txt output2.txt
	@diff output1.txt output2.txt || echo "Test 4 failed"


test5:
	@sort source1.txt | uniq -uc - > output1.txt
	@./$(TARGET) -uc source1.txt output2.txt
	@diff output1.txt output2.txt || echo "Test 5 failed"

test6:
	@sort source1.txt | uniq -ui - > output1.txt
	@./$(TARGET) -ui source1.txt output2.txt
	@diff output1.txt output2.txt || echo "Test 6 failed"

test7:
	@sort source1.txt | uniq -ic - > output1.txt
	@./$(TARGET) -ic source1.txt output2.txt
	@diff output1.txt output2.txt || echo "Test 7 failed"

test8:
	@sort source1.txt | uniq -uci - > output1.txt
	@./$(TARGET) -uci source1.txt output2.txt
	@diff output1.txt output2.txt || echo "Test 8 failed"
