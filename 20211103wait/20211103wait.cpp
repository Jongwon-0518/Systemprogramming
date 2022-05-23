// 20211103wait.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

DWORD WINAPI ThreadFunc(LPVOID);// LPVOID ==> void*

int main()
{
    HANDLE hThrd[5];
    DWORD threadId;
    int i;

    for (i = 0; i < 5; i++)
    {
        hThrd[i] = CreateThread(NULL,//스레드KO(kernel object) 생성 후 핸들을 반환한다
            0,
            ThreadFunc,//함수 포인터
            (LPVOID)i,//함수의 매개변수, 단 하나만 허락
            0,
            &threadId);
        if (hThrd[i])
        {
            printf("Thread launched %d\n", i);
            //CloseHandle(hThrd);
        }
        else {
            printf("error creating a thread\n");
            return 0;
        }
    }
    // Wait for the threads to complete.
    // We'll see a better way of doing this later.
    //스레드가 제대로 종료하였는지 알수있는방법
    //1. 모든 KO는 두가지 상태(state)를 가진다: signaled/nonsignaled
    //2. state의 의미는 ko마다 다르다
    //3. 스레드 ko의 상태: s->종료, ns->수행중
    //4. ko의 상태를 알수 있는 API: Waitforsingleobject
    //Sleep(2000); //이방법이 절대 정답은아님
    //WaitForSingleObject(hThrd[4], INFINITE);//hThrd[4]가 signaled될 때까지 무한대로 기다린다
    WaitForMultipleObjects();
    for (i = 0; i < 5; i++) {
        CloseHandle(hThrd[i]);//1.스레드 실행 종료 2. CloseHandle() 스레드 KO를 소멸
    }
    return EXIT_SUCCESS;
}

DWORD WINAPI ThreadFunc(LPVOID n)
{
    int i;
    for (i = 0; i < 10; i++)
        printf("%d%d%d%d%d%d%d%d\n", n, n, n, n, n, n, n, n);
    return 0;
}
