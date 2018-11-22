//
// Created by aSUSS on 2018/11/2.
//
#include <limits.h>
#include "iostream"

using namespace std;

typedef struct node {
    int **matrix;   //存储图的邻接矩阵
    int n;          //顶点数
    int e;          //边数
} Graph;
/*
 * dijkstra算法
 * g表示存储图的邻接矩阵 dist存储最短路径长度 path存储到源节点最短路中前一个节点 source表示源节点
 * */
void Dijkstra(Graph g, int *dist, int *path, int source) {
    bool *visit = (bool *) malloc(sizeof(bool));

    for (int i = 0; i < g.n; ++i) {//初始化dist和path
        if (g.matrix[source][i] > 0) {
            dist[i] = g.matrix[source][i];
            path[i] = source;
        } else {
            dist[i] = INT_MAX;
            path[i] = -1;
        }
        visit[i] = false;
    }
    path[source] = source;
    dist[source] = 0;
    visit[source] = true;//标记节点是否被访问
    for (int i = 1; i < g.n; ++i) {//更新dist、path、visit的值
        int min = INT_MAX;
        int bestNode;
        for (int j = 0; j < g.n; ++j) {
            if (!visit[j] && dist[j] < min) {
                min = dist[j];
                bestNode = j;
            }
        }
        visit[bestNode] = true;
        for (int k = 0; k < g.n; ++k) {
            if (!visit[k] && g.matrix[bestNode][k] > 0 && (min + g.matrix[bestNode][k]) < dist[k]) {
                dist[k] = min + g.matrix[bestNode][k];
                path[k] = bestNode;
            }
        }
    }
}

void createDijkstraDotFile(Graph g, int *path, char *filename, int source, int dest) {
    FILE *file = fopen(filename, "w");
    if (file == nullptr) {
        printf("file open error");
        return;
    }
    int row = g.n;
    fprintf(file, "digraph Dijkstra {\nnode [shape=ellipse];\n");
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < row; ++j) {
            if (g.matrix[i][j] >= 0) {
                fprintf(file, "%d->%d[label=\"%d\"];\n", i, j, g.matrix[i][j]);
            }
        }
    }
    int tag1, tag2;
    tag1 = path[dest];
    tag2 = dest;
    fprintf(file, "%d->%d[color=red];\n", tag1, tag2);
    while (tag1) {
        tag2 = tag1;
        tag1 = path[tag2];
        fprintf(file, "%d->%d[color=red];\n", tag1, tag2);
    }
    fprintf(file, "}\n");
    fclose(file);

}

//int main() {
//    int dist[9];
//    int path[9];
//    Graph graph;
//    graph.n = 9;
//    graph.e = 11;
//    char dotFile[] = "..\\Dijkstra\\graph.dot";
//    //int a[6][6]={-1,-1,10,-1,30,100 ,-1,-1,5,-1,-1,-1,-1,-1,-1,50,-1,-1,-1,-1,-1,-1,-1,10,-1,-1,-1,20,-1,60,-1,-1,-1,-1,-1,-1};
//    int a[9][9] = {-1, 3, -1, -1, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 3, -1, -1, -1, 5,
//                   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2, -1, -1, 1, 6, -1, -1, -1, -1, 2, -1, -1, -1, -1,
//                   -1, 3, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 3, -1, -1,
//                   -1, -1, -1};
//
//    graph.matrix = (int **) malloc(sizeof(int *) * graph.n);
//    for (int i = 0; i < graph.n; i++)
//        graph.matrix[i] = (int *) malloc(sizeof(int) * graph.n);
//    for (int j = 0; j < graph.n; ++j) {
//        for (int i = 0; i < graph.n; ++i) {
//            graph.matrix[j][i] = a[j][i];
//        }
//    }
//    Dijkstra(graph, dist, path, 0);
//    for (int k = 0; k < graph.n; ++k) {
//        printf("%d ", path[k]);
//    }
//    printf("\n");
//    for (int k = 0; k < graph.n; ++k) {
//        printf("%d ", dist[k]);
//    }
//
//
//    createDijkstraDotFile(graph, path, dotFile, 0, 3);
//}