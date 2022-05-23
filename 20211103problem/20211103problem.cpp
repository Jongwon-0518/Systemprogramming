// 20211103problem.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

DWORD WINAPI ThreadFunc(LPVOID);

//구조체 Node
typedef struct node {
    int data;
    struct node* pNext;
} Node;
//구조체 List
typedef struct list {
    Node* pHead;
} List;
//함수: createNode()
//입력: data값
//출력: 생성한 노드의 포인터
//노드의 데이터값은 입력값, pNext = NULL
Node* createNode(int value)
{
    Node* ptr;
    ptr = (Node*)malloc(sizeof(Node));
    ptr->data = value;
    ptr->pNext = NULL;
    return ptr;
}
void countLL(List* pList) {
    Node* ptr = pList->pHead;
    int i = 0;
    while (ptr != NULL) {
        i++;
        ptr = ptr->pNext;
    }
    printf("%d\n", i);
}
//함수: insertHead()
//입력: 헤드노드포인터, 새 노드 포인터
//출력: 없음
void insertHead(List* pList, Node* newNode) {
    newNode->pNext = pList->pHead;//#1
    pList->pHead = newNode;//#2
}
//현재 insertNode()함수는 정상 수행하지 않음
//다음 시간까지 insertNode()가 정상적으로 수행하도록 수정하세요


int main()
{
    HANDLE hThrd[5];
    DWORD threadId;
    int i;
    List list;
    List* pList = &list;
    pList->pHead = NULL;

    for (i = 0; i < 5; i++)
    {
        hThrd[i] = CreateThread(NULL,
            0,
            ThreadFunc,
            (LPVOID)pList,
            0,
            &threadId);
        if (hThrd[i])
        {
            printf("Thread launched %d\n", i);
            //CloseHandle(hThrd);
        }
        else {
            printf("Thread launched %d\n", i);
            return 0;
        }
    }
    // Wait for the threads to complete.
    // We'll see a better way of doing this later.
    WaitForMultipleObjects(5, hThrd, TRUE, INFINITE);
    for (i = 0; i < 5; i++) {

    }
    Sleep(2000);
    countLL(pHead);

    return EXIT_SUCCESS;
}

DWORD WINAPI ThreadFunc(LPVOID n)
{
    Node*+ ppHead = (Node**) ptr;
    for (int i = 0; i < 1000000; i++)
        insertHead(&ppHead, createNode(100));
    return 0;
}

