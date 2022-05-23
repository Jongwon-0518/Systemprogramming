// HW3.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

// createThread함수에 의해 호출되는 함수는
// 반드시 아래와 같은 함수형을 가져야 한다.
// 1, 매개변수는 하나이고 자료형은 LPVOID
// 2. 반환형 DWORD
// 3. calling convention(함수 호출방법) WINAPI
DWORD WINAPI ThreadFunc_A(LPVOID); // LPVOID ==> void*
DWORD WINAPI ThreadFunc_B(LPVOID);

typedef struct node {
    int data;
    struct node* pNext;
}Node;

// 구조체 List
typedef struct list {
    Node* pHead;
    HANDLE hMutex; // 깃발 추가
}List;

// 함수 : creatList()
// 입력 : 없음
// 출력 : List 구조체의 객체를 생성하여 이 포인터를 반환
List* createList() {
    List* pList = (List*)malloc(sizeof(List));
    pList->pHead = NULL;
    pList->hMutex = CreateMutex(NULL, FALSE, NULL);
    // CS 객체 초기화
    return pList;
}

// 함수 : deleteList()
// 입력 : List*
// 출력 : 없음
void deleteList(List* pList) {
    CloseHandle(&pList->hMutex);
    free(pList);
}

// 함수 : createNode()
// 입력 : data
// 출력 : 생성한 노드의 포인터
Node* createNode(int value) {
    Node* ptr;
    ptr = (Node*)malloc(sizeof(Node));
    ptr->data = value;
    ptr->pNext = NULL;
    return ptr;
}

void SwapLists(List* list1, List* list2)
{
    Node* tmp_list;
    HANDLE arrhandles[2];
    arrhandles[0] = list1->hMutex;
    arrhandles[1] = list2->hMutex;
    WaitForMultipleObjects(2, arrhandles, TRUE, INFINITE);
    tmp_list = list1->pHead;
    list1->pHead = list2->pHead;
    list2->pHead = tmp_list;
    ReleaseMutex(arrhandles[0]);
    ReleaseMutex(arrhandles[1]);
}

int main()
{
    HANDLE hThrd[2];
    DWORD threadId;
    int i;
    List* pList1 = createList();
    List* pList2 = createList();
    List* arr[] = { pList1, pList2 };

    clock_t start = clock();

    pList1->pHead = createNode(1);
    pList2->pHead = createNode(2);

    for (i = 0; i < 2; i++)
    {
        if (i == 0) {
            hThrd[i] = CreateThread(NULL,
                0,
                ThreadFunc_A,
                (LPVOID)arr,
                0,
                &threadId);
        }

        if (i == 1) {
            hThrd[i] = CreateThread(NULL,
                0,
                ThreadFunc_B,
                (LPVOID)arr,
                0,
                &threadId);
        }

        if (hThrd[i])
        {
            printf("Thread launched %d\n", i);
            // CloseHandle(hThrd);
        }
        else { // 스레드 생성에 실패하면 hThrd == NULL
            printf("Error! while creating a thread\n");
            return 0;
        }
    }

    WaitForMultipleObjects(2, hThrd, TRUE, INFINITE); // 모든 스레드가 종료되어야 넘어감, 배열 이름을 바로 쓰면 첫번 째 데이터값의 주소, 3번째 인자 true면 5개 전부, false면 or -> 1개
    for (i = 0; i < 2; i++) {
        CloseHandle(hThrd[i]); // 1. 스레드 실행 종료 2. CloseHandle() 스레드 KO를 소멸
    }
    clock_t end = clock();
    double time = double(end - start) / CLOCKS_PER_SEC;
    printf("경과시간 : %0.3lf\n", time);
    return EXIT_SUCCESS;
}

DWORD WINAPI ThreadFunc_A(LPVOID ptr)
{
    List* pList1 = ((List**)ptr)[0];
    List* pList2 = ((List**)ptr)[1];
    while (true) {
        SwapLists(pList1, pList2);
        printf("Thread A swap complete\n");
    }
    return 0;
}

DWORD WINAPI ThreadFunc_B(LPVOID ptr)
{
    List* pList1 = ((List**)ptr)[0];
    List* pList2 = ((List**)ptr)[1];
    while (true) {
        SwapLists(pList2, pList1);
        printf("Thread B swap complete\n");
    }
    return 0;
}