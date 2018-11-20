//
// Created by aSUSS on 2018/10/28.
//
#include <iostream>
#include <queue>

using namespace std;


typedef int keyType;

typedef struct node {
    keyType key;
    struct node *lchild;
    struct node *rchild;
    int flag;
} BSTNode, *BSTree;

bool InsertTree(BSTree *bst, keyType key) {
    if ((*bst) == nullptr) {
        *bst = (BSTree) malloc(sizeof(BSTNode));
        (*bst)->key = key;
        (*bst)->lchild = nullptr;
        (*bst)->rchild = nullptr;
        (*bst)->flag = 0;
    } else {
        if (key < (*bst)->key) {
            InsertTree(&(*bst)->lchild, key);
        }
        if (key > (*bst)->key) {
            InsertTree(&(*bst)->rchild, key);
        }
        if (key == (*bst)->key) {
            return false;//插入二叉排序树已经有的数据
        }
    }
    return true;
}

void visit(BSTNode bsn) {
    printf("%d ", bsn.key);
}

void PreOrder(BSTree bst) {
    if (bst != nullptr) {
        visit(*bst);
        PreOrder(bst->lchild);
        PreOrder(bst->rchild);
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

//构建排序二叉树，数据从文件中读取
void CreateBST(BSTree *bst, char *filename) {
    FILE *file = fopen(filename, "r+");
    keyType key;
    *bst = nullptr;
    if (file == nullptr) {
        return;
    }
    while (fscanf(file, "%d", &key) != EOF) {
        InsertTree(bst, key);
    }
}

BSTree SearchBST(BSTree bst, keyType key) {
    BSTree q;
    q = bst;
    while (q) {
        q->flag = 1;
        if (q->key == key) {
            q->flag = 3;
            return q;
        }
        if (q->key > key) {
            q->flag = 2;
            q = q->lchild;
        } else {
            q->flag = 2;
            q = q->rchild;
        }
    }
    return nullptr;
}

//层次遍历二叉树
void CreateDotFile(BSTree bst, char *filename) {
    FILE *file = fopen(filename, "w");
    queue<BSTree> bst_queue;
    fprintf(file, "digraph G{\n");
    fprintf(file, "node [fontname = Verdana,shape=record, height=.1];\n");
    fprintf(file, "edge [fontname = Verdana,style=solid];\n");
    if (bst == nullptr) {
        return;
    }
    bst_queue.push(bst);
    fprintf(file, "%d[label=\"<l>%c|<d>%d|<r>%c\",color=yellow];\n", bst->key, ' ', bst->key, ' ');
    while (!bst_queue.empty()) {
        BSTNode *bstNode_current = bst_queue.front();
        bst_queue.pop();
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
        } else {
            //fprintf(file, "%d->Null[shape=box];\n", bstNode_current->key);
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
        } else {
            //fprintf(file, "%d->Null[shape=circle];\n", bstNode_current->key);
        }
    }
    fprintf(file, "}\n");
    fclose(file);
}


//int main() {
//    BSTree bsTree;
//    char data[] = "..\\BST\\data.txt";
//    char dotFile[] = "..\\BST\\graph.dot";
//    CreateBST(&bsTree, data);
//    BSTree bst_find = SearchBST(bsTree, 725);
//    if (bst_find != nullptr) {
//        cout << bst_find->key << endl;
//    }
//    CreateDotFile(bsTree, dotFile);
//}