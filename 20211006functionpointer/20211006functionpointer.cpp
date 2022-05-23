// 20211006functionpointer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <stdio.h>
//함수선언
//1. sum은 함수의 이름
//2. 매개변수의 갯수와 각각의 자료형 (int, int)
//3. 반환형(int)
int sum(int a, int b) {
	return a + b;
}
int main() {
	int a = 10;//변수 선언 : 1. a는 변수의 이름 2. a의 자료형은 int
	int* ptr, *varptr;
	ptr = &a; // &a는 a의 주소
	*ptr = 100;
	printf("a = %d\n", a);

	//function pointer
	//함수 포인터 선언
	//1.fptr : 함수포인터변수: 함수가 시작하는 주소를 가르킨다.
	//2. 함수의 매개변수의 갯수와 각각의 자료형
	//3. 반환형
	int (*fptr) (int, int);//
	fptr = sum;//fptr=&sum; 우변:함수이름만 사용하면 함수 포인터 값을 반환
	int c;
	c = fptr(10, 20);
	printf("c=%d\n", c);

	//void*
	void* vptr;
	vptr = ptr;
	varptr = (int*) vptr;

	return 0;
}
