// 20211027static.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <stdio.h>
//전역변수: 프로그램 수행 내내 동일한 메모리 공간을 사용한다.
int ga;//BSS 세그먼트를 사용
int gb = 10;//DATA 세그먼트를 사용
int main() {
	int a,b,c;
	//정적 변수
	static int sa;//BSS 세그먼트를 사용
	static int sb = 20;//DATA 세그먼트를 사용

	a = 10;
	b = 20;
	c = a + b;
	//sa = a + sb;
	//printf("c = %d\n", c);
	return 0;
}

