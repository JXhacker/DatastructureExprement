//
// Created by aSUSS on 2018/11/1.
//

#include "iostream"

//堆用数组进行存储
// 该函数根据输入的节点的对应序号自上而下对堆进行维护
//data[]堆中数据 loc需要调整的节点的位置，从1开始 datalen数据长度
void HeapAdjust(int data[], int loc, int dataLen) {
    int nextLoc = 2 * loc;
    int temp;
    for (; nextLoc <= dataLen; loc = nextLoc) {
        if (dataLen >= nextLoc + 1 && data[nextLoc + 1] < data[nextLoc]) {
            nextLoc = nextLoc + 1;
        }
        if (data[loc] > data[nextLoc]) {
            temp = data[loc];
            data[loc] = data[nextLoc];
            data[nextLoc] = temp;
        } else {
            break;
        }
    }
}

//data[]未初始化的数据 datalen堆大小
void HeapInit(int data[],int dataLen) {
    for (int i = dataLen; i >= 1; --i) {
        HeapAdjust(data,i,dataLen);
    }
}

//int main(){
//    int bigData[]={25 ,11 ,22 ,10 ,13 ,39 ,16 ,75 ,55 ,21 ,63 ,76 ,57 ,94 ,14 ,20 ,30 ,45 ,19 ,69,99 ,15 ,81 ,98 ,17 ,78 ,23 ,84 ,12 ,72 ,90 ,38 ,40 ,79 ,54 ,24 ,56 ,60 ,74 ,47 };
//    int data[6];
//    for (int i = 1; i <= 5; ++i) {
//        data[i]=bigData[i-1];
//    }
//    HeapInit(data,5);
//    for (int j = 5; j < 40; ++j) {
//        if (bigData[j]>data[1])
//        data[1]=bigData[j];
//        HeapAdjust(data,1,5);
//    }
//
//    for (int k = 1; k <=5 ; ++k) {
//        printf("%d ",data[k]);
//    }
//
//}

