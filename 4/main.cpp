#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    try {
        STARTUPINFO spInfo;
        ZeroMemory(&spInfo, sizeof(STARTUPINFO));
        PROCESS_INFORMATION processInfo;
        if(CreateProcess("C:\\Windows\\System32\\notepad.exe", NULL, NULL, NULL, false, NULL, NULL, NULL, &spInfo, &processInfo)==FALSE){
            throw 1;
        }
        bool b=true;
        cout << "id of process: " << processInfo.dwProcessId << endl;
        while(b) {
            cout << "'S' Pause" << endl;
            cout << "'R' Restart" << endl;
            cout << "'T' Close" << endl;
            char ch;
            cin >> ch;
            switch(ch){
                case 's':{
                    SuspendThread(processInfo.hThread);
                    break;
                }
                case 'r':{
                    ResumeThread(processInfo.hThread);
                    break;
                }
                case 't':{
                    TerminateProcess(processInfo.hProcess, NO_ERROR);
                    b=false;
                }
            }
        }
        if(CreateProcess("C:\\Windows\\System32\\notepad.exe", NULL, NULL, NULL, false, CREATE_SUSPENDED, NULL, NULL, &spInfo, &processInfo)==FALSE){
            throw 1;
        }
        cout << "id of process: " << processInfo.dwProcessId << endl;
        Sleep(10000);
        ResumeThread(processInfo.hThread);
        cout << "priority of thread: " << GetThreadPriority(processInfo.hThread) << endl;
    }catch(int i){
        if(i==1){
            cout << "Process don't create" << endl;
        }
    }
    return 0;
}