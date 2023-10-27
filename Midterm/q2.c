#include<stdio.h>
#include<fcntl.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/times.h>

void output(int i, struct tms end, struct tms start, clock_t end_time, clock_t start_time){
	printf("Task%d\tUser CPU: %lf\tSystem CPU: %lf\tClock Time: %lf\n",
		i,
		((double)end.tms_utime - (double)start.tms_utime)/CLOCKS_PER_SEC,
		((double)end.tms_stime - (double)start.tms_stime)/CLOCKS_PER_SEC,
		((double)end_time - (double)start_time)/CLOCKS_PER_SEC
	);
}

int main(){
	// read file to buffer "input"
	const int output_size = 20 * 1024 * 1024;
	char *input = malloc(output_size);
	int source_fd = open("source2", O_RDONLY);
	read(source_fd, input, output_size);

	// for timer
	struct tms start, end;
	clock_t start_time, end_time;

	// Task 1: fread / fwrite with buffer size 1  byte
	const int size1 = 1;
	char *buf1_in = malloc(size1);
	char *buf1_out = malloc(output_size);
	FILE *fd1_in = fmemopen(input, output_size, "r");
	FILE *fd1_out = fmemopen(buf1_out, output_size, "w");
	buf1_in = malloc(size1);
	int receive;

	// start!
	start_time = times(&start);
	while(receive = fread(buf1_in, sizeof(char), size1, fd1_in) > 0){
		fwrite(buf1_in, sizeof(char), receive, fd1_out);
	}
	end_time = times(&end);
	// output time
	printf("Task1\tUser CPU: %f\tSystem CPU: %f\tClock Time: %f\n",
		((float)end.tms_utime - (float)start.tms_utime)/CLOCKS_PER_SEC,
		((float)end.tms_stime - (float)start.tms_stime)/CLOCKS_PER_SEC,
		((float)end_time - (float)start_time)/CLOCKS_PER_SEC
	);

	/* DO NOT contain this into calculation */
	int fd1_output = open("output1", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	write(fd1_output, buf1_out, output_size);


	// Task 2: fread / fwrite with buffer size 32 bytes
	
	const int size2 = 32;
	char *buf2_in = malloc(size2);
	char *buf2_out = malloc(output_size);
	FILE *fd2_in = fmemopen(input, output_size, "r");
	FILE *fd2_out = fmemopen(buf1_out, output_size, "w");
	buf2_in = malloc(size2);

	// start!
	start_time = times(&start);
	while(receive = fread(buf2_in, sizeof(char), size2, fd2_in) > 0){
		fwrite(buf2_in, sizeof(char), receive, fd2_out);
	}
	end_time = times(&end);
	// output time
	output(2, end, start, end_time, start_time);

	/* DO NOT contain this into calculation */
	int fd2_output = open("output2", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	write(fd2_output, buf2_out, output_size);

	// Task 3: fread / fwrite with buffer size 1024 bytes

	const int size3 = 1024;
	char *buf3_in = malloc(size3);
	char *buf3_out = malloc(output_size);
	FILE *fd3_in = fmemopen(input, output_size, "r");
	FILE *fd3_out = fmemopen(buf3_out, output_size, "w");
	buf3_in = malloc(size3);

	// start!
	start_time = times(&start);
	while(receive = fread(buf3_in, sizeof(char), size3, fd3_in) > 0){
		fwrite(buf3_in, sizeof(char), receive, fd3_out);
	}
	end_time = times(&end);
	// output time
	output(3, end, start, end_time, start_time);

	/* DO NOT contain this into calculation */
	int fd3_output = open("output3", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	write(fd3_output, buf3_out, output_size);

	// Task 4: fread / fwrite with buffer size 4096 bytes
	
	const int size4 = 4096;
	char *buf4_in = malloc(size4);
	char *buf4_out = malloc(output_size);
	FILE *fd4_in = fmemopen(input, output_size, "r");
	FILE *fd4_out = fmemopen(buf4_out, output_size, "w");
	buf4_in = malloc(size4);

	// start!
	start_time = times(&start);
	while(receive = fread(buf4_in, sizeof(char), size4, fd4_in) > 0){
		fwrite(buf4_in, sizeof(char), receive, fd4_out);
	}
	end_time = times(&end);
	// output time
	output(4, end, start, end_time, start_time);

	/* DO NOT contain this into calculation */
	int fd4_output = open("output4", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	write(fd4_output, buf4_out, output_size);

	// Task 5: fgets / fputs with buffer size 4096 bytes
	
	const int size5 = 4096;
	char *buf5_in = malloc(size5);
	char *buf5_out = malloc(output_size);
	FILE *fd5_in = fmemopen(input, output_size, "r");
	FILE *fd5_out = fmemopen(buf5_out, output_size, "w");

	buf5_in = malloc(size5);
	// start!
	start_time = times(&start);
	while(fgets(buf5_in, size5, fd5_in) != NULL){
		fputs(buf5_in, fd5_out);
	}
	end_time = times(&end);
	// output time
	output(5, end, start, end_time, start_time);

	/* DO NOT contain this into calculation */
	int fd5_output = open("output5", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	write(fd5_output, buf5_out, output_size);

	// Task 6: fgetc / fputc
	const int size6 = 4096;
	// just dummy, for fmemopen
	char *buf6_in = malloc(size6);
	char *buf6_out = malloc(output_size);
	FILE *fd6_in = fmemopen(input, output_size, "r");
	FILE *fd6_out = fmemopen(buf6_out, output_size, "w");
	char rec;
	// start!
	start_time = times(&start);
	while(rec = fgetc(fd6_in) != EOF){
		fputc(rec, fd6_out);
	}
	end_time = times(&end);	
	// output time
	output(6, end, start, end_time, start_time);

	/* DO NOT contain this into calculation */
	int fd6_output = open("output6", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	write(fd6_output, buf6_out, output_size);

	return 0;
}
