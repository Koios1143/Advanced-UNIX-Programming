CC = gcc
CFLAG = -std=c11 -O2 -Wall
TARGET = mocktest
SRCS = mocktest.c
OBJS = mocktest.o
TMPS = output.txt output1.txt output2.txt

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAG) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(TMPS)

test: test1 test2 test3 test4 test5 test6 test7 test8

test1:
	@uniq source.txt output1.txt
	@./$(TARGET) source.txt output2.txt
	@diff output1.txt output2.txt || echo "Test 1 failed"

test2:
	@uniq -u source.txt output1.txt
	@./$(TARGET) -u source.txt output2.txt
	@diff output1.txt output2.txt || echo "Test 2 failed"

test3:
	@uniq -c source.txt output1.txt
	@./$(TARGET) -c source.txt output2.txt
	@diff output1.txt output2.txt || echo "Test 3 failed"

test4:
	@uniq -i source.txt output1.txt
	@./$(TARGET) -i source.txt output2.txt
	@diff output1.txt output2.txt || echo "Test 4 failed"


test5:
	@uniq -uc source.txt output1.txt
	@./$(TARGET) -uc source.txt output2.txt
	@diff output1.txt output2.txt || echo "Test 5 failed"

test6:
	@uniq -ui source.txt output1.txt
	@./$(TARGET) -ui source.txt output2.txt
	@diff output1.txt output2.txt || echo "Test 6 failed"

test7:
	@uniq -ic source.txt output1.txt
	@./$(TARGET) -ic source.txt output2.txt
	@diff output1.txt output2.txt || echo "Test 7 failed"

test8:
	@uniq -uci source.txt output1.txt
	@./$(TARGET) -uci source.txt output2.txt
	@diff output1.txt output2.txt || echo "Test 8 failed"
