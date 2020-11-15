// 线索二叉树
#include <stdio.h>
#include <stdlib.h>

// 线索存储标志位
// Link(0):表示指向左右孩子的指针
// Thread(1):表示指向前屈后继的线索
typedef enum {Link, Thread} PointerTag;

typedef struct BiThrNode {
	char data;
	struct BiThrNode *lchild, *rchild;
	PointerTag ltag, rtag;
}BiThrNode, *BiThrTree;

// 全局变量，始终指向刚刚访问过的结点
BiThrTree g_pre;

// 先序遍历
void preOder(BiThrNode *root) {
	if (root == NULL) {
		printf("_");
		return;
	}

	printf("%c", root->data);
	preOder(root->lchild);
	preOder(root->rchild);

	return;
}

// 中序遍历线索
void InThreadingOder(BiThrNode *root) {
	if (root == NULL){
		return;
	}

	InThreadingOder(root->lchild);

	// 如果该结点无左孩子，设置ltag为1,并lchild指向刚刚访问的结点
	if (!root->lchild) { 
		root->ltag = Thread;
		root->lchild = g_pre;
	}

	if (!root->rchild) {
		g_pre->rtag = Thread;
		g_pre->rchild = root;
	}

	g_pre = root;

	InThreadingOder(root->rchild);

	return;
}

/*
	    A
	 B     E
   C   D     F

	前序: ABC__D__E_F__
*/
// 创建二叉树，前序遍历创建
void CreateBiThrTree(BiThrTree *T) {

	char c;
	scanf("%c", &c);

	if (' ' == c) {
		*T = NULL;
	} else {
		*T = (BiThrNode *)malloc(sizeof(BiThrNode));
		(*T)->data = c;
		(*T)->ltag = Link;
		(*T)->rtag = Link;
		CreateBiThrTree(&((*T)->lchild));
		CreateBiThrTree(&((*T)->rchild));
	}
}

void InThreading(BiThrTree *p, BiThrTree T) {

	g_pre = (BiThrNode *)malloc(sizeof(BiThrNode));
	g_pre->ltag = Link;
	g_pre->rtag = Thread;
	g_pre->rchild = g_pre;

	if (!T) {
		g_pre->lchild = g_pre;
	} else {
		g_pre->lchild = T;
		g_pre = T;
		InThreadingOder(T);
		g_pre->rchild = T;
		g_pre->rtag = Thread;
		T->rchild = g_pre;
	}
}

int main(int argc, char const *argv[]) {
	BiThrTree tree = NULL;
	CreateBiThrTree(&tree);

	preOder(tree);
	printf("\n");
	// InThreading(tree);

	return 0;
}

