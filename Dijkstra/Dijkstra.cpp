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

void Dijkstra(Graph g, int *dist, int *path, int source) {
    bool *visit = (bool *) malloc(sizeof(bool));

    for (int i = 0; i < g.n; ++i) {
        if (g.matrix[source][i] > 0) {
            dist[i] = g.matrix[source][i];
            path[i] = source;
        } else {
            dist[i] = INT_MAX;
            path[i] = -1;
        }
        visit[i] = false;
    }
    visit[source] = true;
    for (int i = 1; i < g.n; ++i) {
        int min = INT_MAX;
        for (int j = 0; j < g.n; ++j) {
            if (!visit[j] && dist[j] < min) {
                min = dist[j];
                path[i] = j;
            }
        }
        visit[path[i]] = true;
        for (int k = 0; k < g.n; ++k) {
            if (!visit[k] && dist[])
        }
    }


}