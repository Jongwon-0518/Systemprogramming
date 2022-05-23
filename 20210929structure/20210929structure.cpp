// 20210929structure.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
//구조체 선언
#include <stdio.h>
#include <stdlib.h>

typedef struct complex {
	double real;//실수부 : 멤버변수
	double imag;//허수부 : 멤버변수
} Complex;

int main()
{
	//struct complex c1, c2;//구조체변수 선언
	//c1.real = 3.0;// 구조체변수, 멤버변수
	//c1.imag = 4.0;
	struct complex* ptr1;//구조체 포인터 변수 선언
	ptr1 = (struct complex*)malloc(sizeof(struct complex));
	//즉, 모든 구조체는 포인터 변수를 통해 접근한다.
	Complex* ptr2;
	ptr2 = (Complex*)malloc(sizeof(Complex));
	ptr1->real = 3.0; // 구조체포인터변수 -> 멤버변수
	ptr1->imag = 4.0;


	return 0;
}
