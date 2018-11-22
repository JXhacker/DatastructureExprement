//
// Created by aSUSS on 2018/11/1.
//

#include "iostream"

int K = 10;

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
void HeapInit(int data[], int dataLen) {
    for (int i = dataLen; i >= 1; --i) {
        HeapAdjust(data, i, dataLen);
    }
}

void CreateDotFile(char *path, int a[], int insertData, int oldData) {
    FILE *file = fopen(path, "w");
    fprintf(file, "digraph G {\n");

    fprintf(file, "edge [fontname = \"Microsoft YaHei\", style=solid, arrowsize=0.7];\n");
    for (int i = 1; i <= K; ++i) {
        if (a[i] == insertData) {
            fprintf(file, "%d[shape=circle,color=red];\n", insertData);
        } else {
            fprintf(file, "%d[shape=circle];\n", a[i]);
        }
        if (i == 1) {
            fprintf(file, "%d[label=\"<l>%c|<m>%d|<r>%c\",shape=record,color=red];\n", a[1], ' ', a[1], ' ');
        }
        int left_index = 2 * i;
        if (left_index <= K) {
            fprintf(file, "%d->%d;\n", a[i], a[left_index]);
        }
        int right_index = 2 * i + 1;
        if (right_index <= K) {
            fprintf(file, "%d->%d;\n", a[i], a[right_index]);
        }
    }

    fprintf(file, "%d%c[shape=circle,color=red,shape=Mcircle];\n", insertData, '.');
    fprintf(file, "%d%c:e->%d:l:w;\n", insertData, '.', a[1]);
    fprintf(file, "%d%c[shape=circle,color=red,shape=Mcircle];\n", oldData, '.');
    fprintf(file, "%d:r:e->%d%c:w;\n", a[1], oldData, '.');
    fprintf(file, "}");
    fclose(file);
}

void initHeap(int *heap, char *filename) {
    FILE *file = fopen(filename, "r+");
    if (file == nullptr) {
        return;
    }
    int data = fscanf(file, "%d", &data);
    for (int i = 1, data = 120; i <= K; fscanf(file, "%d", &data)) {// != EOF
        heap[i] = data;
        i++;
    }
    HeapInit(heap, K);
}
//从文件中读取数据heap表示存储小顶堆的数组，filename表示数据文件位置
void TopK(int *heap, char *filename) {
    int bigData;
    int oldData;
    FILE *file = fopen(filename, "r+");
    int count = 0;
    for (int j = 0; j < 10; ++j) {
        fscanf(file, "%d", &bigData);
    }
    for (; fscanf(file, "%d", &bigData) != EOF;) {//逐个比较直至文件数据读取完
        oldData = heap[1];
        if (bigData > heap[1]) {
            heap[1] = bigData;
            HeapAdjust(heap, 1, K);
        }
        if (count > 10 && count < 20) {
            char dotFile[100];// = "..\\Heap\\graph.dot";
            sprintf(dotFile, "..\\Heap\\graph%d.dot", count);
            CreateDotFile(dotFile, heap, bigData, oldData);//dot文件创建函数
        }//取出第10-20次的比较结果图
        printf("第%d次迭代heap：",count+1);
        for (int i = 1; i <= K; ++i) {
            printf("%d ", heap[i]);
        }
        printf("\n");
        count++;
    }
}

//int main() {
//
//    char datafile[] = "..\\Heap\\data.txt";
//    char dotFile[] = "..\\Heap\\graph.dot";
//    int heap[10000] = {0};
//    initHeap(heap, datafile);
//    for (int i = 1; i <= K; ++i) {
//        printf("%d ", heap[i]);
//    }
//    printf("\n");
//    TopK(heap, datafile);
//}

