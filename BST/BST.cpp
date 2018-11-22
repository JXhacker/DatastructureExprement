//
// Created by aSUSS on 2018/10/28.
//
#include <iostream>
#include <queue>

using namespace std;


typedef int keyType;
/*
 * key��ʾ�ڵ��������
 * lchild��rchild��ʾ�ڵ����Һ���
 * flag�����ݲ���ʱ���������
 * */
typedef struct node {
    keyType key;
    struct node *lchild;
    struct node *rchild;
    int flag;
} BSTNode, *BSTree;
/*
 * �ú������ڽ��ڵ���뵽ָ���������������
 * bstΪָ�����������ͷָ���һ��ָ��
 * key Ϊ������ڵ���������ֵ
 * ����ֵtrueΪ����ɹ� falseΪ����ʧ��
 * */
bool InsertTree(BSTree *bst, int key) {
    if ((*bst) == nullptr) {
        *bst = (BSTree) malloc(sizeof(BSTNode));//����ռ�
        (*bst)->key = key;
        (*bst)->lchild = nullptr;
        (*bst)->rchild = nullptr;
        (*bst)->flag = 0;
    } else {
        if (key < (*bst)->key) {//������ڵ�С�ڸýڵ㣬���뵽�ڵ����������
            InsertTree(&(*bst)->lchild, key);
        }
        if (key > (*bst)->key) {//������ڵ���ڸýڵ㣬���뵽�ڵ����������
            InsertTree(&(*bst)->rchild, key);
        }
        if (key == (*bst)->key) {//��������������Ѿ��е�����
            return false;
        }
    }
    return true;
}
//���ʶ������еĽڵ�
void visit(BSTNode bsn) {
    printf("%d ", bsn.key);
}
//�������������
void InOrder(BSTree bst) {
    if (bst != nullptr) {//��ֹ����
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
        return t;//�Ҳ�������ԭ���Ķ���������
    }
    if (p->lchild == nullptr) {
        if (f == nullptr) {
            t = p->rchild;
        } else {
            if (f->lchild == p)  /*p��f������*/
            {
                f->lchild = p->rchild;  /*��p������������f��������*/
            } else  /*p��f���Һ���*/
            {
                f->rchild = p->rchild;  /*��p������������f��������*/
            }
        }
        free(p);
    } else {
        q = p;
        s = p->lchild;
        while (s->rchild)  /*��p���������в��������½��*/
        {
            q = s;
            s = s->rchild;
        }
        if (q == p) {
            q->lchild = s->lchild;  /*��s������������q��*/
        } else {
            q->rchild = s->lchild;
        }
        p->key = s->key;  /*��s��ֵ����p*/
        free(s);
    }
    return t;
}
/*
 * �ú������ڹ�����������������ݴ��ļ��ж�ȡ
 * bstΪָ�����������ͷָ���һ��ָ��
 * filename�����������ļ���
 * */
void CreateBST(BSTree *bst, char *filename) {
    FILE *file = fopen(filename, "r+");
    keyType key;
    *bst = nullptr;//������������ʼ��
    if (file == nullptr) {//�ж��Ƿ����ļ����
        return;
    }
    while (fscanf(file, "%d", &key) != EOF) {//�����������
        InsertTree(bst, key);//����������������
    }
}
/*
 * ���ݹؼ���key�����������������Ŀ��ڵ�
 * bstΪָ�����������ͷָ���һ��ָ��
 * key Ϊ�������ڵ���������ֵ
 * ����ֵ���ҵ��򷵻�ָ��ýڵ��ָ�룬���򷵻ؿ�
 * */
BSTree SearchBST(BSTree bst, keyType key) {
    BSTree q;
    q = bst;
    while (q) {
        q->flag = 1;
        if (q->key == key) {//���ҵ��ڵ㣬���ýڵ�flag��־Ϊ3
            q->flag = 3;
            return q;
        }
        if (q->key > key) {//��δ�ҵ��������������������Ľڵ��2
            q->flag = 2;
            q = q->lchild;
        } else {
            q->flag = 2;
            q = q->rchild;
        }
    }
    return nullptr;
}

//��α�����������ӡ�ڵ�ͱߣ�Ŀ��ڵ���ɫ�Ǻ�ɫ��Ѱ�ҹ���·���ϵĽڵ��ǻ�ɫ������ڵ���ɫ
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
    printf("��������������������:\n");
    InOrder(bsTree);
    CreateDotFile(bsTree, dotFile);
}