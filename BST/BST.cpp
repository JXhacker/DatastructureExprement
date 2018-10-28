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
        PreOrder(bst->lchild);
        visit(*bst);
        PreOrder(bst->rchild);
    }
}

BSTree SearchBST(BSTree bst, keyType key) {
    if (bst != nullptr) {
        if (bst->key > key) {
            return SearchBST(bst->lchild, key);
        }
        if (bst->key < key) {
            return SearchBST(bst->rchild, key);
        }
        if (bst->key == key) {
            return bst;
        }
    } else {
        return nullptr;
    }
}

int main(int argc, char *argv[]) {
    BSTree bsTree = nullptr;
    keyType keys[11] = {63, 90, 70, 55, 67, 42, 98, 83, 10, 45, 58};
    for (int key : keys) {
        InsertTree(&bsTree, key);
    }
    BSTree bst_find=SearchBST(bsTree,42);
    if (bst_find!= nullptr){
        cout<<bst_find->rchild->key<<endl;
    }
}