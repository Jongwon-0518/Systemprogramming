// HW2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>

#define MAX_THREADS 3 //최대스레드 3
#define BUF_SIZE 255 //버프사이즈 255

DWORD WINAPI MyThreadFunction(LPVOID lpParam);
void ErrorHandler(LPTSTR lpszFunction);

// Sample custom data structure for threads to use.
// 사용할 스레드의 샘플 사용자 지정 데이터 구조
// This is passed by void pointer so it can be any data type
// that can be passed using a single void pointer (LPVOID).
// 이것은 void 포인터에 의해 전달되므로
// 단일 void 포인터(LPVOID)를 사용하여 전달할 수 있는 모든 데이터 형식이 될 수 있다
typedef struct MyData {
    int val1;
    int val2;
} MYDATA, * PMYDATA;


int _tmain()
{
    PMYDATA pDataArray[MAX_THREADS];
    DWORD   dwThreadIdArray[MAX_THREADS];
    HANDLE  hThreadArray[MAX_THREADS];

    // Create MAX_THREADS worker threads.

    for (int i = 0; i < MAX_THREADS; i++)
    {
        // 스레드 데이터의 메모리 할당

        pDataArray[i] = (PMYDATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
            sizeof(MYDATA));

        if (pDataArray[i] == NULL)
        {
            // If the array allocation fails, the system is out of memory
            // so there is no point in trying to print an error message.
            // Just terminate execution.
            // 배열할당이 메모리부족으로 실패하면 실행 종료
            ExitProcess(2);
        }

        // Generate unique data for each thread to work with.
        // 각각의 스레드에 작동되도록 데이터 생성

        pDataArray[i]->val1 = i;
        pDataArray[i]->val2 = i + 100;

        // Create the thread to begin execution on its own.
        // 각각의 스레드에서 실행이 시작되도록 스레드 생성

        hThreadArray[i] = CreateThread(
            NULL,                   // default security attributes, 새 스레드에 대한 핸들의 보안 특성
            0,                      // use default stack size,  새 스레드의 초기 스택 크기
            MyThreadFunction,       // thread function name, 스레드의 이름
            pDataArray[i],          // argument to thread function, 스레드에 전달할 변수에 대한 포인터
            0,                      // use default creation flags, 스레드 생성을 제어하는 플래그 
            &dwThreadIdArray[i]);   // returns the thread identifier 스레드 식별자를 수신하는 변수에 대한 포인터


        // Check the return value for success.
        // 성공여부 체크
        // If CreateThread fails, terminate execution. 
        // 스레드 생성 실패서 실행 종료
        // This will automatically clean up threads and memory. 
        // 실행 종료되면 자동적으로 스레드와 메모리 삭제

        if (hThreadArray[i] == NULL)
        {
            ErrorHandler(TEXT("CreateThread"));
            ExitProcess(3);
        }
    } // End of main thread creation loop. 
    // 메인 스레드 생성 루프의 끝

    // Wait until all threads have terminated. 
    // 모든 스레드가 종료될때까지 기다림

    WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);

    // Close all thread handles and free memory allocations.
    // 스레드 모두 종료 및 메모리 방출

    for (int i = 0; i < MAX_THREADS; i++)
    {
        CloseHandle(hThreadArray[i]);
        if (pDataArray[i] != NULL)
        {
            HeapFree(GetProcessHeap(), 0, pDataArray[i]);
            pDataArray[i] = NULL;    // Ensure address is not reused, 주소가 재사용되지 않는지 확인
        }
    }

    return 0;
}


DWORD WINAPI MyThreadFunction(LPVOID lpParam)
{
    HANDLE hStdout;
    PMYDATA pDataArray;

    TCHAR msgBuf[BUF_SIZE];
    size_t cchStringSize;
    DWORD dwChars;

    // Make sure there is a console to receive output results.
    // 출력 결과를 수신할 콘솔이 있는지 확인

    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdout == INVALID_HANDLE_VALUE)
        return 1;

    // Cast the parameter to the correct data type.
    // The pointer is known to be valid because 
    // it was checked for NULL before the thread was created.
    // 매개변수를 올바른 데이터 형식으로 캐스팅하고
    // 포인터는 스레드가 만들어지기 전에 NULL이 확인되었기 때문에 유효한것

    pDataArray = (PMYDATA)lpParam;

    // Print the parameter values using thread-safe functions.
    // 스레드 세이프기능을 사용하여 파라미터값을 인쇄

    StringCchPrintf(msgBuf, BUF_SIZE, TEXT("Parameters = %d, %d\n"),
        pDataArray->val1, pDataArray->val2);
    StringCchLength(msgBuf, BUF_SIZE, &cchStringSize);
    WriteConsole(hStdout, msgBuf, (DWORD)cchStringSize, &dwChars, NULL);

    return 0;
}



void ErrorHandler(LPTSTR lpszFunction)
{
    // Retrieve the system error message for the last-error code.
    // 마지막 에러코드를 위한 시스템 에러 메시지 출력

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError();

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf,
        0, NULL);

    // Display the error message. 
    // 에러메세지 출력

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
    StringCchPrintf((LPTSTR)lpDisplayBuf,
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"),
        lpszFunction, dw, lpMsgBuf);
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

    // Free error-handling buffer allocations.
    // 에러를 다루는 버퍼의 할당량 방출

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
}