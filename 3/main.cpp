#include <iostream>
#include <windows.h>
#include <ctime>

using namespace std;

int main() {
    try {
        srand(time(NULL));
        cout << "Enter quantity of strings" << endl;
        int quantityOfStrings;
        cin >> quantityOfStrings;
        if(quantityOfStrings<=4){
            throw 1;
        }
        int randLength[quantityOfStrings];
        for(int i=0;i<quantityOfStrings;i++) {
            randLength[i] = rand() % 10 + 1;
            cout << "length[" << i << "]=" << randLength[i] << endl;
        }
        HANDLE heap;
        heap=HeapCreate(0,0x01000,0);
        if(heap==NULL){
            throw 2;
        }
        int **array;
        array=(int**)HeapAlloc(heap,0, sizeof(int)*quantityOfStrings);
        for(int i=0;i<quantityOfStrings;i++){
            array[i]=(int*)HeapAlloc(heap,0, sizeof(int)*(randLength[i]));
        }
        for(int i=0;i<quantityOfStrings;i++){
            for(int j=0;j<randLength[i];j++){
                array[i][j]=rand()%9+1;
            }
        }
        for(int i=0;i<quantityOfStrings;i++){
            for(int j=0;j<randLength[i];j++){
                cout << array[i][j] << " ";
            }
            cout << endl;
        }
        for(int i=1;i<quantityOfStrings;i++){
            for(int j=0;j<quantityOfStrings-i;j++) {
                if(HeapSize(heap,0,array[j])>HeapSize(heap,0,array[j+1])){
                    int *copyA, size1,size2;
                    size1=HeapSize(heap,0,array[j]);
                    size2=HeapSize(heap,0,array[j+1]);
                    copyA=(int*)malloc(sizeof(int)*size1);
                    memcpy(copyA,array[j],size1);
                    array[j]=(int*)HeapReAlloc(heap,0,array[j],size2);
                    memcpy(array[j],array[j+1],size2);
                    array[j+1]=(int*)HeapReAlloc(heap,0,array[j+1],size1);
                    memcpy(array[j+1],copyA,size1);
                    free(copyA);
                }
            }
        }
        cout << "Sorted array:" << endl;
        for(int i=0;i<quantityOfStrings;i++){
            for(int j=0;j<HeapSize(heap,0,array[i])/ sizeof(int);j++){
                cout << array[i][j] << " ";
            }
            cout << endl;
        }
        for(int i=0;i<quantityOfStrings;i++) {
            if (HeapFree(heap, 0, array[i]) == 0) {
                throw 4;
            }
            HeapFree(heap, 0, array[i]);
        }
        if(HeapDestroy(heap)==0){
            throw 5;
        }
        HeapDestroy(heap);
    }catch (int i){
        if(i==1){
            cout << "Enter strings more than 4" << endl;
        }
        if(i==2){
            cout << "Heap don't create" << endl;
        }
        if(i==3){
            cout << "Don't allocate memory" << endl;
        }
        if(i==4){
            cout << "Memory not free" << endl;
        }
        if(i==5){
            cout << "Error delete heap" << endl;
        }
    }
    return 0;
}