//
// Created by aSUSS on 2018/10/28.
//
#include <iostream>
#include <queue>

using namespace std;


typedef int keyType;
/*
 * key表示节点的数据域
 * lchild和rchild表示节点左右孩子
 * flag在数据查找时做标记作用
 * */
typedef struct node {
    keyType key;
    struct node *lchild;
    struct node *rchild;
    int flag;
} BSTNode, *BSTree;
/*
 * 该函数用于将节点插入到指定的排序二叉树中
 * bst为指向二叉排序树头指针的一个指针
 * key 为欲插入节点的数据域的值
 * 返回值true为插入成功 false为插入失败
 * */
bool InsertTree(BSTree *bst, int key) {
    if ((*bst) == nullptr) {
        *bst = (BSTree) malloc(sizeof(BSTNode));//分配空间
        (*bst)->key = key;
        (*bst)->lchild = nullptr;
        (*bst)->rchild = nullptr;
        (*bst)->flag = 0;
    } else {
        if (key < (*bst)->key) {//若插入节点小于该节点，插入到节点的左子树中
            InsertTree(&(*bst)->lchild, key);
        }
        if (key > (*bst)->key) {//若插入节点大于该节点，插入到节点的右子树中
            InsertTree(&(*bst)->rchild, key);
        }
        if (key == (*bst)->key) {//插入二叉排序树已经有的数据
            return false;
        }
    }
    return true;
}
//访问二叉树中的节点
void visit(BSTNode bsn) {
    printf("%d ", bsn.key);
}
//中序遍历二叉树
void InOrder(BSTree bst) {
    if (bst != nullptr) {//终止条件
        InOrder(bst->lchild);
        visit(*bst);
        InOrder(bst->rchild);
    }
}

BSTNode *DelBSTNode(BSTree t, keyType k) {
    BSTNode *p;
    BSTNode *f;
    BSTNode *s;
    BSTNode *q;
    p = t;
    f = nullptr;
    while (p) {
        if (p->key == k) break;
        f = p;
        if (p->key > k) {
            p = p->lchild;
        } else {
            p = p->rchild;
        }
    }
    if (p == nullptr) {
        return t;//找不到返回原来的二叉排序树
    }
    if (p->lchild == nullptr) {
        if (f == nullptr) {
            t = p->rchild;
        } else {
            if (f->lchild == p)  /*p是f的左孩子*/
            {
                f->lchild = p->rchild;  /*将p的右子树链到f的左链上*/
            } else  /*p是f的右孩子*/
            {
                f->rchild = p->rchild;  /*将p的右子树链到f的右链上*/
            }
        }
        free(p);
    } else {
        q = p;
        s = p->lchild;
        while (s->rchild)  /*在p的左子树中查找最右下结点*/
        {
            q = s;
            s = s->rchild;
        }
        if (q == p) {
            q->lchild = s->lchild;  /*将s的左子树链到q上*/
        } else {
            q->rchild = s->lchild;
        }
        p->key = s->key;  /*将s的值赋给p*/
        free(s);
    }
    return t;
}
/*
 * 该函数用于构建排序二叉树，数据从文件中读取
 * bst为指向二叉排序树头指针的一个指针
 * filename是数据所在文件名
 * */
void CreateBST(BSTree *bst, char *filename) {
    FILE *file = fopen(filename, "r+");
    keyType key;
    *bst = nullptr;//二叉排序树初始化
    if (file == nullptr) {//判断是否获得文件句柄
        return;
    }
    while (fscanf(file, "%d", &key) != EOF) {//逐个读入数据
        InsertTree(bst, key);//逐个插入二叉排序树
    }
}
/*
 * 根据关键字key再排序二叉树中搜索目标节点
 * bst为指向二叉排序树头指针的一个指针
 * key 为欲搜索节点的数据域的值
 * 返回值：找到则返回指向该节点的指针，否则返回空
 * */
BSTree SearchBST(BSTree bst, keyType key) {
    BSTree q;
    q = bst;
    while (q) {
        q->flag = 1;
        if (q->key == key) {//若找到节点，将该节点flag标志为3
            q->flag = 3;
            return q;
        }
        if (q->key > key) {//若未找到，将搜索过程中遇到的节点标2
            q->flag = 2;
            q = q->lchild;
        } else {
            q->flag = 2;
            q = q->rchild;
        }
    }
    return nullptr;
}

//层次遍历二叉树打印节点和边，目标节点颜色是红色，寻找过程路线上的节点是黄色，其余节点标黑色
void CreateDotFile(BSTree bst, char *filename) {
    FILE *file = fopen(filename, "w");
    queue<BSTree> bst_queue;
    fprintf(file, "digraph G{\n");
    fprintf(file, "node [fontname = Verdana,shape=record, height=.1];\n");
    fprintf(file, "edge [fontname = Verdana,style=solid];\n");
    if (bst == nullptr) { return; }
    bst_queue.push(bst);
    fprintf(file, "%d[label=\"<l>%c|<d>%d|<r>%c\",color=yellow];\n", bst->key, ' ', bst->key, ' ');
    while (!bst_queue.empty()) {
        BSTNode *bstNode_current = bst_queue.front();bst_queue.pop();
        if (bstNode_current->lchild != nullptr) {
            bst_queue.push(bstNode_current->lchild);
            if (bstNode_current->lchild->flag == 3) {
                fprintf(file, "%d[label=\"<l>%c|<d>%d|<r>%c\",color=red];\n", bstNode_current->lchild->key, ' ',
                        bstNode_current->lchild->key, ' ');
            } else if (bstNode_current->lchild->flag == 2) {
                fprintf(file, "%d[label=\"<l>%c|<d>%d|<r>%c\",color=yellow];\n", bstNode_current->lchild->key, ' ',
                        bstNode_current->lchild->key, ' ');
            } else {
                fprintf(file, "%d[label=\"<l>%c|<d>%d|<r>%c\"];\n", bstNode_current->lchild->key, ' ',
                        bstNode_current->lchild->key, ' ');
            }
            fprintf(file, "%d:l:sw->%d:d;\n", bstNode_current->key, bstNode_current->lchild->key);
        }
        if (bstNode_current->rchild != nullptr) {
            bst_queue.push(bstNode_current->rchild);
            if (bstNode_current->rchild->flag == 3) {
                fprintf(file, "%d[label=\"<l>%c|<d>%d|<r>%c\",color=red];\n", bstNode_current->rchild->key, ' ',
                        bstNode_current->rchild->key, ' ');
            } else if (bstNode_current->rchild->flag == 2) {
                fprintf(file, "%d[label=\"<l>%c|<d>%d|<r>%c\",color=yellow];\n", bstNode_current->rchild->key, ' ',
                        bstNode_current->rchild->key, ' ');
            } else {
                fprintf(file, "%d[label=\"<l>%c|<d>%d|<r>%c\"];\n", bstNode_current->rchild->key, ' ',
                        bstNode_current->rchild->key, ' ');
            }
            fprintf(file, "%d:r:se->%d:d;\n", bstNode_current->key, bstNode_current->rchild->key);
        }
    }
    fprintf(file, "}\n");fclose(file);
}


int main() {
    BSTree bsTree;
    char data[] = "..\\BST\\data.txt";
    char dotFile[] = "..\\BST\\graph.dot";
    CreateBST(&bsTree, data);
    BSTree bst_find = SearchBST(bsTree, 558);
    printf("二叉排序树中序遍历结果:\n");
    InOrder(bsTree);
    CreateDotFile(bsTree, dotFile);
}