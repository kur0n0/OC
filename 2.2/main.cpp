#include <iostream>
#include <windows.h>

#define LENGTH 9

using namespace std;

void getInfo(MEMORY_BASIC_INFORMATION mbi){
    if(mbi.State==MEM_COMMIT){cout << "Memory of commited area is commited" << endl;}
    if(mbi.State==MEM_RESERVE){cout << "Memory of area after commited is reserved" << endl;}
    if(mbi.Protect==PAGE_NOACCESS){cout << "Protect of commited area is no access" << endl;}
    if(mbi.Protect==PAGE_READONLY){cout << "Protect of commited area is read only" << endl;}
    if(mbi.Protect==PAGE_READWRITE){cout << "Protect of commited area is read and write" << endl;}
    if(mbi.Protect==PAGE_EXECUTE){cout << "Protect of area after commited is execute" << endl;}
    if(mbi.Protect==PAGE_EXECUTE_READ){cout << "Protect of area after commited is execute read" << endl;}
    if(mbi.Protect==PAGE_EXECUTE_READWRITE){cout << "Protect of area after commited is execute read and write" << endl;}
    if(mbi.Protect==PAGE_WRITECOPY){cout << "Protect of area after commited is writecopy" << endl;}
    if(mbi.Protect==PAGE_EXECUTE_WRITECOPY){cout << "Protect of area after commited is execute writecopy" << endl;}
    if(mbi.Protect==NULL){cout << "Protect of area after commited is unkwnown" << endl;}
}

int main() {
    try {
        cout << "------------ Task number 1 ------------" << endl;
        int quantityToReserve, array[LENGTH] = {10, 20, 30, 40, 50, 60, 70, 80, 90};
        cout << "Enter quantity of pages: " << endl;
        cin >> quantityToReserve;
        void *pReserve;
        SYSTEM_INFO siSysInfo;
        GetSystemInfo(&siSysInfo);
        pReserve = VirtualAlloc(NULL, siSysInfo.dwPageSize * quantityToReserve, MEM_RESERVE, PAGE_READWRITE);
        if(pReserve == NULL){
            throw 1;
        }
        cout << "Address on first reserved page: " << pReserve << endl;
        cout << "------------ Task number 2 ------------" << endl;
        int quantityToCommit, kToCommit;
        cout << "Enter quantity of page with phys mem" << endl;
        cin >> quantityToCommit;
        cout << "Enter index of page to commit" << endl;
        cin >> kToCommit;
        if(kToCommit+quantityToCommit>quantityToReserve){
            throw 3;
        }
        void *pCommit;
        pCommit = VirtualAlloc(LPVOID(DWORD(pReserve) + kToCommit * siSysInfo.dwPageSize),
                               siSysInfo.dwPageSize * quantityToCommit, MEM_COMMIT, PAGE_READWRITE);
        if(pCommit == NULL){
            throw 1;
        }
        cout << "Address of first commited page: " << pCommit << endl;
        cout << "------------ Task number 3 ------------" << endl;
        memcpy_s(pCommit, siSysInfo.dwPageSize * quantityToCommit, array, sizeof(array));
        int *pArray = (int *) pCommit;
        for (int i = 0; i < LENGTH; i++) {
            cout << i + 1 << ". " << pArray[i] << endl;
        }
        cout << "------------ Task number 4 ------------" << endl;
        MEMORY_BASIC_INFORMATION mbi;
        VirtualQuery(pCommit, &mbi, sizeof(mbi));
        cout << "Information about commited area: " << endl;
        getInfo(mbi);
        cout << "Address of commited area: " << pCommit << endl;
        cout << "\n";
        VirtualQuery(pReserve, &mbi, sizeof(mbi));
        cout << "Information about reserved area: " << endl;
        getInfo(mbi);
        cout << "Address of reserved area: " << pReserve << endl;
        cout << "------------ Task number 5 ------------" << endl;
        void *pCommitAfter;
        pCommitAfter = VirtualAlloc(pCommit, siSysInfo.dwPageSize, MEM_COMMIT,
                                    PAGE_READONLY);
        if(pCommitAfter == NULL){
            throw 1;
        }
        VirtualQuery(pCommitAfter, &mbi, sizeof(mbi));
        cout << "Information about reserved area: " << endl;
        getInfo(mbi);
        cout << "Address of reserved area: " << pCommitAfter << endl;
        cout << "------------ Task number 6 ------------" << endl;
        cout << "Enter index of page to free: " << endl;
        int kToFree;
        cin >> kToFree;
        if(kToFree>quantityToReserve){
            throw 3;
        }
        VirtualFree(pCommit, siSysInfo.dwPageSize * kToFree, MEM_DECOMMIT);
        cout << "Address after decommit: " << pCommit << endl;
        VirtualQuery(pCommit, &mbi, sizeof(mbi));
        cout << "Information of decommited area: " << endl;
        getInfo(mbi);
        cout << "------------ Task number 7 ------------" << endl;
        VirtualFree(pReserve, siSysInfo.dwPageSize * quantityToReserve, MEM_RELEASE);
        cout << "Address after dereserve area: " << pReserve << endl;
        cout << "---------------------------------------" << endl;
    }catch (int i){
        if(i==1){
            cout << "Error VirtualAlloc" << endl;
        }
        if(i==2){
            cout << "Error VirtualFree" << endl;
        }
        if(i==3){
            cout << "Enter other index of quantity of pages" << endl;
        }
    }
    return 0;
}