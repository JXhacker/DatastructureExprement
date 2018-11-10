//
// Created by aSUSS on 2018/10/28.
//
#include <iostream>

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
    if (file == NULL) {
        return;
    }
    while (fscanf(file, "%d", &key) != EOF) {
        printf("%d ", key);
        InsertTree(bst, key);
    }
}

BSTree SearchBST(BSTree bst, keyType key) {
    BSTree q;
    q = bst;
    while (q) {
        q->flag = 1;
        if (q->key == key) {
            q->flag = 2;
            return q;
        }
        if (q->key > key)
            q = q->lchild;
        else
            q = q->rchild;
    }
    return nullptr;
}

int main() {
    BSTree bsTree;
    char data[] = "..\\BST\\data.txt";
    CreateBST(&bsTree, data);
    BSTree bst_find = SearchBST(bsTree, 19);
    if (bst_find != nullptr) {
        cout << bst_find->key << endl;
    }




}