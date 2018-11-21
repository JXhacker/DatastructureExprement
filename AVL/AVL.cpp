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

        if (A->bf == -2 && B->bf == -1) {//RR型的情况的调整
            A->rchild = B->lchild;//将B的左子树挂到A的右子树上
            B->lchild = A;//将A挂到B的左子树上
            A->bf = 0;
            B->bf = 0;
            if (fa == nullptr) {
                *avlt = B;
            } else if (A == fa->lchild) {
                fa->lchild = B;
            } else {
                fa->rchild = B;
            }
        } else if (A->bf == 2 && B->bf == 1) {//LL型的情况的调整
            A->lchild = B->rchild;//将B的右子树挂到A的左子树上
            B->rchild = A;//将A挂到B的右子树上
            A->bf = 0;
            B->bf = 0;
            if (fa == nullptr) {
                *avlt = B;
            } else if (A == fa->lchild) {
                fa->lchild = B;
            } else {
                fa->rchild = B;
            }
        } else if (A->bf == 2 && B->bf == -1) {//LR型的情况的调整
            C = B->rchild;//C是B的右孩子
            B->rchild = C->lchild;//将C的左子树挂到B的右子树上
            A->lchild = C->rchild;//将C的右子树挂到A的左子树上
            C->lchild = B;//将B挂到C的左子树上
            C->rchild = A;//将A挂到C的右子树上
            if (key < C->key) {//平衡因子调整
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
        } else if (A->bf == -2 && B->bf == 1) {//RL型的情况的调整
            C = B->lchild;//C是B的左孩子
            B->lchild = C->rchild;//将C的右子树挂带B的左子树
            A->rchild = C->lchild;//将C的左子树挂到A的右子树
            C->lchild = A;//将A挂到C的左子树
            C->rchild = B;//将B挂到C的右子树
            if (key < C->key) {//平衡因子调整
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

int getRchildMin(AVLTree *TreeRoot) {
    if ((*TreeRoot)->lchild == NULL) {
        return (*TreeRoot)->key;
    } else {
        return getRchildMin(&((*TreeRoot)->lchild));
    }
}

// 求树的深度
int GetHeight(AVLTree TreeRoot) {
    if (TreeRoot == NULL) return 0;
    return 1 + max(GetHeight(TreeRoot->lchild), GetHeight(TreeRoot->rchild));
}

// 计算节点的平衡因子
int updateBF(AVLTree *TreeRoot) {
    return GetHeight((*TreeRoot)->lchild) - GetHeight((*TreeRoot)->rchild);
}
// 左旋转
void LL_Rotation(AVLTree *TreeRoot) {
    AVLTree temp = (*TreeRoot)->lchild;
    (*TreeRoot)->lchild = temp->rchild;
    temp->rchild = *TreeRoot;
    *TreeRoot = temp;
    (*TreeRoot)->bf = max(GetHeight((*TreeRoot)->lchild), GetHeight((*TreeRoot)->rchild));
    temp->bf = max(GetHeight(temp->lchild), GetHeight(temp->rchild));
}
// 右旋转
void RR_Rotation(AVLTree *TreeRoot) {
    AVLTree temp = (*TreeRoot)->rchild;
    (*TreeRoot)->rchild = temp->lchild;
    temp->lchild = *TreeRoot;
    *TreeRoot = temp;
    (*TreeRoot)->bf = max(GetHeight((*TreeRoot)->lchild), GetHeight((*TreeRoot)->rchild));
    temp->bf = max(GetHeight(temp->lchild), GetHeight(temp->rchild));
}

// 先右旋，后左旋
void RL_Rotation(AVLTree *TreeRoot) {
    LL_Rotation(&((*TreeRoot)->rchild));
    RR_Rotation(&(*TreeRoot));
}


// 先左旋，后右旋
void LR_Rotation(AVLTree *TreeRoot) {
    RR_Rotation(&((*TreeRoot)->lchild));
    LL_Rotation(&(*TreeRoot));
}


void AVLTreeFix(AVLTree *TreeRoot, int data, int type) {
    if (type == 1) { // 插入后进行调整
        if (updateBF(&(*TreeRoot)) >= 2) {
            if (data < (*TreeRoot)->lchild->key) { // LL
                LL_Rotation(&(*TreeRoot));
            } else {                                // LR
                LR_Rotation(&(*TreeRoot));
            }
        }
        if (updateBF(&(*TreeRoot)) <= -2) {
            if (data > (*TreeRoot)->rchild->key) { // RR
                RR_Rotation(&(*TreeRoot));
            } else {                                // RL
                RL_Rotation(&(*TreeRoot));
            }
        }
    }

    if (type == 0) { // 删除后进行调整
        if (updateBF(&(*TreeRoot)) >= 2) {
            // 删除与插入要判断的符号逆向
            if (updateBF(&((*TreeRoot)->lchild)) <= -1) { // LR
                LR_Rotation(&(*TreeRoot));
            } else {                                // LL
                LL_Rotation(&(*TreeRoot));
            }
        }
        if (updateBF(&(*TreeRoot)) <= -2) {
            if (updateBF(&((*TreeRoot)->rchild)) >= 1) { // RL
                RL_Rotation(&(*TreeRoot));
            } else {                                // RR
                RR_Rotation(&(*TreeRoot));
            }
        }
    }
}


AVLTree DeleteAVL(AVLTree *TreeRoot, int data) {
    if (TreeRoot == NULL) {
        return NULL;
    }
    if (data < (*TreeRoot)->key) {
        (*TreeRoot)->lchild = DeleteAVL(&((*TreeRoot)->lchild), data);
    } else if (data > (*TreeRoot)->key) {
        (*TreeRoot)->rchild = DeleteAVL(&((*TreeRoot)->rchild), data);
    } else {
        if ((*TreeRoot)->lchild != NULL && (*TreeRoot)->rchild != NULL) {
            // 删除的节点有两个孩子
            (*TreeRoot)->key = getRchildMin(&((*TreeRoot)->rchild));
            (*TreeRoot)->rchild = DeleteAVL(&((*TreeRoot)->rchild), (*TreeRoot)->key);
        } else {
            // 删除的节点只有一个孩子或者没有孩子
            AVLTree temp = *(TreeRoot);
            (*TreeRoot) = ((*TreeRoot)->lchild != NULL) ? (*TreeRoot)->lchild : (*TreeRoot)->rchild;
            free(temp);
        }
    }

    // 恢复二叉树的平衡
    if (*TreeRoot == NULL) {
        return *TreeRoot;
    }
    (*TreeRoot)->bf = updateBF(&(*TreeRoot));
    AVLTreeFix(&(*TreeRoot), data, 0);

    return *TreeRoot;
}
//层次遍历二叉树打印节点和边，目标节点颜色是红色，寻找过程路线上的节点是黄色，其余节点标黑色
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
        insert_AVLTree(avlt, key);//AVL插入算法
    }
}

int main() {
    AVLTree avlTree = nullptr;
    char data[] = "..\\AVL\\data.txt";
    char dotFile[] = "..\\AVL\\graph.dot";
    CreateAVL(&avlTree,data);
    AVL_InOrder(avlTree);
    CreateAVLDotFile(avlTree,dotFile);
}