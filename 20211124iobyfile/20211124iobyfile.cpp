// 20211124iobyfile.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

/*
 * IoByFile.c
 *
 * Sample code for Multithreading Applications in Win32
 * This is from Chapter 6, Listing 6-1
 *
 * Demonstrates how a file handle becomes signaled
 * when an overlapped operation on the handle's file
 * is completed.  Notice that sometimes the operation
 * is completed immediately. The operation is only
 * queued, or pended, if ERROR_IO_PENDING is returned.
 */

#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

 //
 // Constants
 //
#define READ_SIZE       512

//
// Function prototypes
//
void CheckOsVersion();


int main()
{
    BOOL rc;
    HANDLE hFile;
    DWORD numread;
    OVERLAPPED overlap;
    char buf[READ_SIZE];
    WCHAR szPath[MAX_PATH] = L"c:\\test.mp4";
    
    //CheckOsVersion();

    //GetWindowsDirectory(szPath, sizeof(szPath));
    //strcat(szPath, "\\WINHLP32.EXE");
    // Open the file for overlapped reads
    hFile = CreateFile(szPath, //파일 생성 경로
        GENERIC_READ, //파일을 열거나 쓰기 등을 할 때의 엑세스 권한 지정
        FILE_SHARE_READ | FILE_SHARE_WRITE, //파일 공유 모드 지정
        NULL, //보안관련 NULL하면됨
        OPEN_EXISTING, //파일의 해당 위치에 존재하는지에 따른 행동
        FILE_FLAG_OVERLAPPED, //비동기화 입출력을 사용하는 key! FILE_FLAG_OVERLAPPED쓰면됨
        NULL // NULL
    );
    if (hFile == INVALID_HANDLE_VALUE)
    {
        printf("Could not open %s\n", szPath);
        return -1;
    }

    // Initialize the OVERLAPPED structure
    memset(&overlap, 0, sizeof(overlap));
    overlap.Offset = 1500;

    // Request the data
    rc = ReadFile(
        hFile, //파일이나 장치의 핸들
        buf, //읽은 데이터를 받아올 버퍼의 포인터
        READ_SIZE, //읽어들일 데이터의 길이
        &numread, //실제 읽은 크기
        &overlap //오버랩된 정보의 포인터주소
    );
    printf("Issued read request\n");

    // Was the operation queued?
    if (rc)
    {
        // The data was read successfully
        printf("Request was returned immediately\n");
    }
    else
    {
        if (GetLastError() == ERROR_IO_PENDING)
        {
            // We could do something else for awhile here...

            printf("Request queued, waiting...\n");
            WaitForSingleObject(hFile, INFINITE);
            printf("Request completed.\n");

            rc = GetOverlappedResult(
                hFile,
                &overlap,
                &numread,
                FALSE
            );
            printf("Result was %d\n", rc);
        }
        else
        {
            // We should check for memory and quota
            // errors here and retry. See the samples
            // IoByEvnt and IoByAPC.

            // Something went wrong
            printf("Error reading file\n");
        }
    }

    CloseHandle(hFile);

    return EXIT_SUCCESS;
}

//
// Make sure we are running under an operating
// system that supports overlapped I/O to files.
//
void CheckOsVersion()
{
    OSVERSIONINFO   ver;
    BOOL            bResult;

    ver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    bResult = GetVersionEx((LPOSVERSIONINFO)&ver);

    if ((!bResult) ||
        (ver.dwPlatformId != VER_PLATFORM_WIN32_NT))
    {
        fprintf(stderr, "IoByFile must be run under Windows NT.\n");
        exit(EXIT_FAILURE);
    }

}
