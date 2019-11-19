#include <iostream>
#include <windows.h>

CRITICAL_SECTION critsect;

using namespace std;

DWORD WINAPI threadtask1(LPVOID args){
    char first[6]="first";
    for(int i=0;i<6;i++){
        Sleep(100);
        cout << first[i];
    }
    cout << endl;
}

DWORD WINAPI threadtask2(LPVOID args){
    char second[7]="second";
    for(int i=0;i<7;i++){
        Sleep(100);
        cout << second[i];
    }
    cout << endl;
}

DWORD WINAPI threadtask_31(LPVOID args){
    EnterCriticalSection(&critsect);
    char first[6]="first";
    for(int i=0;i<6;i++){
        Sleep(100);
        cout << first[i];
    }
    cout << endl;
    LeaveCriticalSection(&critsect);
}

DWORD WINAPI threadtask_32(LPVOID args){
    EnterCriticalSection(&critsect);
    char second[7]="second";
    for(int i=0;i<7;i++){
        Sleep(100);
        cout << second[i];
    }
    cout << endl;
    LeaveCriticalSection(&critsect);
}

DWORD WINAPI threadtask_41(LPVOID args){
    HANDLE mut;
    mut=CreateMutexA(NULL,FALSE,"first");
    char first[6]="first";
    Sleep(50);
    for (int i = 0; i < 6; i++) {
        cout << first[i];
    }
    ReleaseMutex(mut);
    cout << endl;
    CloseHandle(mut);
}

DWORD WINAPI threadtask_42(LPVOID args){
    HANDLE mut;
    mut=CreateMutexA(NULL,FALSE,"second");
    char second[7]="second";
    Sleep(50);
    for (int i = 0; i < 7; i++) {
        cout << second[i];
    }
    ReleaseMutex(mut);
    cout << endl;
    CloseHandle(mut);
}

DWORD WINAPI thread1(LPVOID args){
    cout << "first thread" << endl;
}

DWORD WINAPI thread2(LPVOID args){
    cout << "second thread" << endl;
}

int main() {
    while(1) {
        cout << "Enter number of task: " << endl;
        cout << "| ---------- (1) Task 1 ---------- |" << endl;
        cout << "| ---------- (2) Task 2 ---------- |" << endl;
        cout << "| ---------- (3) Task 3 ---------- |" << endl;
        cout << "| ---------- (4) Task 4 ---------- |" << endl;
        cout << "| ---------- (5)  Exit  ---------- |" << endl;
        char ch;
        cin >> ch;
        switch (ch) {
            case '1': {
                DWORD thread1Id, thread2Id;
                HANDLE hthread1, hthread2;
                int n;
                cout << "Enter quantity" << endl;
                cin >> n;
                for (int i = 0; i < n; i++) {
                    hthread1 = CreateThread(NULL, 0, thread1, NULL, 0, &thread1Id);
                    WaitForSingleObject(hthread1, 100);
                    hthread2 = CreateThread(NULL, 0, thread2, NULL, 0, &thread2Id);
                    WaitForSingleObject(hthread2, 100);
                }
                CloseHandle(hthread1);
                CloseHandle(hthread2);
                break;
            }
            case '2':{
                DWORD thread1Id, thread2Id;
                HANDLE hthread1, hthread2;
                int n;
                cout << "Enter quantity" << endl;
                cin >> n;
                for (int i = 0; i < n; i++) {
                    hthread1 = CreateThread(NULL, 0, threadtask1, NULL, 0, &thread1Id);
                    WaitForSingleObject(hthread1, 100);
                    hthread2 = CreateThread(NULL, 0, threadtask2, NULL, 0, &thread2Id);
                    WaitForSingleObject(hthread2, 100);
                }
                CloseHandle(hthread1);
                CloseHandle(hthread2);
                break;
            }
            case'3':{
                DWORD thread1Id, thread2Id;
                HANDLE hthread1, hthread2;
                int n;
                cout << "Enter quantity" << endl;
                cin >> n;
                InitializeCriticalSection(&critsect);
                for (int i = 0; i < n; i++) {
                    hthread1 = CreateThread(NULL, 0, threadtask_31, NULL, 0, &thread1Id);
                    WaitForSingleObject(hthread1, 700);
                    hthread2 = CreateThread(NULL, 0, threadtask_32, NULL, 0, &thread2Id);
                    WaitForSingleObject(hthread2, 700);
                }
                DeleteCriticalSection(&critsect);
                CloseHandle(hthread1);
                CloseHandle(hthread2);
                break;
            }
            case '4':{
                DWORD thread1Id, thread2Id;
                HANDLE hthread1, hthread2;
                int n;
                cout << "Enter quantity" << endl;
                cin >> n;
                for (int i = 0; i < n; i++) {
                    hthread1 = CreateThread(NULL, 0, threadtask_41, NULL, 0, &thread1Id);
                    WaitForSingleObject(hthread1,100);
                    hthread2 = CreateThread(NULL, 0, threadtask_42, NULL, 0, &thread2Id);
                    WaitForSingleObject(hthread2,100);
                }
                CloseHandle(hthread1);
                CloseHandle(hthread2);
                break;
            }
            case '5': {
                return 0;
            }
        }
    }
    return 0;
}