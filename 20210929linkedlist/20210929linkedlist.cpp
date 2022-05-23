// 20210929linkedlist.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <stdio.h>
#include <stdlib.h>
//구조체 Node
typedef struct node {
    int data;
    struct node* pNext;
} Node;
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
void printLL(Node* pHead) {
    Node* ptr = pHead;
    while (ptr != NULL) {
        printf("data = %d\n", ptr->data);
        ptr = ptr->pNext;
    }
}
//함수: insertHead()
//입력: 헤드노드포인터, 새 노드 포인터
//출력: 없음
void insertHead(Node** ppHead, Node* newNode) {
    newNode->pNext = *ppHead;//#1
    *ppHead = newNode;//#2
}
//현재 insertNode()함수는 정상 수행하지 않음
//다음 시간까지 insertNode()가 정상적으로 수행하도록 수정하세요
int main()
{
    Node* pHead=NULL;//연결리스트의 맨앞을 가리킨다.
    //pHead = createNode(10);
    //insertHead(pHead, createNode(20));
    for (int i = 0; i < 10; i++)
        insertHead(&pHead, createNode(i));
    printLL(pHead);

    return 0;
}

