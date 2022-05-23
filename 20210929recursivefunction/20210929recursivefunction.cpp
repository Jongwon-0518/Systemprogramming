// 20210929recursivefunction.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <stdio.h>

//recursive function (재귀함수)
//함수 안에서 자신을 호출
void rfunction(int a) {
	rfunction(a);
}
int main() {
	int x = 10;
	rfunction(x);
	//return 0;
}