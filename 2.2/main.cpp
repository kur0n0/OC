#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    cout << "------------ Task number 1 ------------" << endl;
    int length, i, quantity, k, array[9]={10,20,30,40,50,60,70,80,90};
    cout << "Enter quntity of pages" << endl;
    cin >> length;
    void *p[length];
    SYSTEM_INFO siSysInfo;
    GetSystemInfo(&siSysInfo);
    for(i=0;i<length;i++) {
        p[i] = VirtualAlloc(NULL, siSysInfo.dwPageSize, MEM_RESERVE, PAGE_READWRITE);
    }
    for(i=0;i<length;i++) {
        cout << i+1 << ". " << p[i] << endl;
    }
    cout << "------------ Task number 2 ------------" << endl;
    cout << "Enter quantity of page with phys mem" << endl;
    cin >> quantity;
    cout << "Enter index" << endl;
    cin >>k;
    for(i=0;i<quantity;i++){
        p[i+k-1]=VirtualAlloc(NULL, siSysInfo.dwPageSize, MEM_COMMIT, PAGE_READWRITE);
    }
    for(i=0;i<length;i++){
        cout << i+1 << ". " << p[i] << endl;
    }
    cout << "------------ Task number 3 ------------" << endl;
    memcpy_s(p, sizeof(p), array, 9* sizeof(int));
    for(i=0;i<length;i++){
        cout << i+1 << ". " << int(p[i]) << endl;
    }
    cout << "------------ Task number 4 ------------" << endl;
    MEMORY_BASIC_INFORMATION info;
    for(i=0;i<quantity;i++){
        VirtualQuery(p[i+k-1], &info, sizeof(info));
        cout << "State: " << info.State << endl;
        cout << "Protect: " << info.Protect << endl;
    }
    cout << "---------------------------------------" << endl;
    for(i=k;i<length;i++){
        VirtualQuery(p[i], &info, sizeof(info));
        cout << "State: " << info.State << endl;
        cout << "Protect: " << info.Protect << endl;
    }
    return 0;
}