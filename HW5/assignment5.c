#include<stdio.h>
int* f1(int *val){
	int num = 0;
	int *ptr = &num;
	if(num == 0){
		int val;
		val = 5;
		ptr = &val;
	}
	return val;
}

int main(){
	int val = 5;
	printf("Value %d is at %p\n", val, f1(&val));
	return 0;
}
