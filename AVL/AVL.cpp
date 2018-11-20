//
// Created by aSUSS on 2018/10/28.
//
#include <queue>
#include "iostream"

using namespace std;

typedef int keyType;

typedef struct node {
    keyType key;
    int bf;//balance factor
    struct node *lchild;
    struct node *rchild;
} AVLNode, *AVLTree;

bool insert_AVLTree(AVLTree *avlt, keyType key) {
/*
 * 过程：先插入节点--->更新平衡因子-->判断类型-->调整
*/
    AVLNode *newNode;   //要插入的新节点
    AVLNode *A;         //指向离插入点最近的平衡因子不为0的一个节点
    AVLNode *fa;        //指向离插入点次最近的平衡因子不为0的点
    AVLNode *fp;        //指向插入点的前一个节点
    AVLNode *p;         //移动指针
    AVLNode *B;         //指向A的下一个节点
    AVLNode *C;         //B的右孩子
    newNode = (AVLNode *) malloc(sizeof(AVLNode));
    newNode->key = key;
    newNode->lchild = nullptr;
    newNode->rchild = nullptr;
    newNode->bf = 0;
    if (*avlt == nullptr) {
        *avlt = newNode;
        return true;
    } else {
        p = *avlt;
        A = *avlt;
        fa = nullptr;
        fp = nullptr;

        while (p != nullptr) {
            if (p->bf != 0) {
                A = p;
                fa = fp;
            }
            fp = p;
            if (key < p->key) {
                p = p->lchild;
            } else if (key > p->key) {
                p = p->rchild;
            } else {
                return false;
            }

        }


        if (key > fp->key) {
            fp->rchild = newNode;
        }
        if (key < fp->key) {
            fp->lchild = newNode;
        }

        if (key > A->key) {
            B = A->rchild;
            A->bf = A->bf - 1;
        }
        if (key < A->key) {
            B = A->lchild;
            A->bf = A->bf + 1;
        }
        p = B;
        while (p != newNode) {
            if (key < p->key) {
                p->bf = 1;
                p = p->lchild;
            }
            if (key > p->key) {
                p->bf = -1;
                p = p->rchild;
            }
        }

        if (A->bf == -2 && B->bf == -1) {
            A->rchild = B->lchild;
            B->lchild = A;
            A->bf = 0;
            B->bf = 0;
            if (fa == nullptr) {
                *avlt = B;
            } else if (A == fa->lchild) {
                fa->lchild = B;
            } else {
                fa->rchild = B;
            }
        } else if (A->bf == 2 && B->bf == 1) {
            A->lchild = B->rchild;
            B->rchild = A;
            A->bf = 0;
            B->bf = 0;
            if (fa == nullptr) {
                *avlt = B;
            } else if (A == fa->lchild) {
                fa->lchild = B;
            } else {
                fa->rchild = B;
            }
        } else if (A->bf == 2 && B->bf == -1) {
            C = B->rchild;
            B->rchild = C->lchild;
            A->lchild = C->rchild;
            C->lchild = B;
            C->rchild = A;
            if (key < C->key) {
                A->bf = -1;
                B->bf = 0;
                C->bf = 0;
            } else if (key > C->key) {
                A->bf = 0;
                B->bf = 1;
                C->bf = 0;
            } else {
                A->bf = 0;
                B->bf = 0;
            }
            if (fa == nullptr) {
                *avlt = C;
            } else if (A == fa->lchild) {
                fa->lchild = C;
            } else {
                fa->rchild = C;
            }
        } else if (A->bf == -2 && B->bf == 1) {
            C = B->lchild;
            B->lchild = C->rchild;
            A->rchild = C->lchild;
            C->lchild = A;
            C->rchild = B;
            if (key < C->key) {
                A->bf = 0;
                B->bf = -1;
                C->bf = 0;
            } else if (key > C->key) {
                A->bf = 1;
                B->bf = 0;
                C->bf = 0;
            } else {
                A->bf = 0;
                B->bf = 0;
            }
            if (fa == nullptr) {
                *avlt = C;
            } else if (A == fa->lchild) {
                fa->lchild = C;
            } else {
                fa->rchild = C;
            }
        }
        return true;
    }
}

void visit(AVLTree avlTree) {
    printf("%d ", avlTree->key);
}

void AVL_InOrder(AVLTree avlTree) {
    if (avlTree != nullptr) {
        AVL_InOrder(avlTree->lchild);
        visit(avlTree);
        AVL_InOrder(avlTree->rchild);
    }
}

void CreateAVLDotFile(AVLTree avl, char *filename) {
    FILE *file = fopen(filename, "w");
    queue<AVLTree> avl_queue;
    fprintf(file, "digraph G{\n");
    fprintf(file, "node [fontname = Verdana,shape=record, height=.1];\n");
    fprintf(file, "edge [fontname = Verdana,style=solid];\n");
    if (avl == nullptr) {
        return;
    }
    avl_queue.push(avl);
    fprintf(file, "%d[label=\"<l>%c|<d>%d|<r>%c\",color=yellow];\n", avl->key, ' ', avl->key, ' ');
    while (!avl_queue.empty()) {
        AVLNode *avlNode_current = avl_queue.front();
        avl_queue.pop();
        if (avlNode_current->lchild != nullptr) {
            avl_queue.push(avlNode_current->lchild);

            fprintf(file, "%d[label=\"<l>%c|<d>%d|<r>%c\",color=red];\n", avlNode_current->lchild->key, ' ', avlNode_current->lchild->key, ' ');

            fprintf(file, "%d:l:sw->%d:d;\n", avlNode_current->key,avlNode_current->lchild->key);
        }
        if (avlNode_current->rchild != nullptr) {
            avl_queue.push(avlNode_current->rchild);

                fprintf(file, "%d[label=\"<l>%c|<d>%d|<r>%c\",color=red];\n", avlNode_current->rchild->key, ' ',
                        avlNode_current->rchild->key, ' ');
            fprintf(file, "%d:r:se->%d:d;\n", avlNode_current->key, avlNode_current->rchild->key);
        }
    }
    fprintf(file, "}\n");
    fclose(file);
}

void CreateAVL(AVLTree *avlt, char *filename) {
    FILE *file = fopen(filename, "r+");
    keyType key;
    *avlt = nullptr;
    if (file == nullptr) {
        return;
    }
    while (fscanf(file, "%d", &key) != EOF) {
        insert_AVLTree(avlt, key);
    }
}

int main() {
    AVLTree avlTree = nullptr;
    char data[] = "..\\AVL\\data.txt";
    char dotFile[] = "..\\AVL\\graph.dot";
    CreateAVL(&avlTree,data);
    AVL_InOrder(avlTree);
    CreateAVLDotFile(avlTree,dotFile);
//        BSTree bsTree;
//    char data[] = "..\\BST\\data.txt";
//    char dotFile[] = "..\\BST\\graph.dot";
//    CreateBST(&bsTree, data);
//    BSTree bst_find = SearchBST(bsTree, 725);
//    if (bst_find != nullptr) {
//        cout << bst_find->key << endl;
//    }
//
}