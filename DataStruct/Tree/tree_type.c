#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 二叉链表法
typedef struct BiTree
{
	int data;
	struct BiTree *lchild, *rchild;
}BiTree, *pBiTree;

// 三叉链表法
typedef struct TriTree
{
	int data;
	struct BiTree *lchild, *rchild;
	struct BiTree *parent;
}TriTree, *pTriTree;

// 双亲链表法
#define MAX_TREE_SIZE 100
typedef struct BPTNode
{
	int data;
	int parentPosition;// 指向双亲的指针，数组下标
	char LRTab;// 左右孩子标签域
}BPTNode, *pBPTNode;

typedef struct BPTree
{
	BPTNode nodes[MAX_TREE_SIZE];
	int num_node;// 节点数目
	int root;// 根结点数目
}BPTree, *pBPTree;

int main(int argc, char const *argv[])
{
#if 0
	BiTree t1, t2, t3, t4, t5;
	t1.data = 1;
	t2.data = 2;
	t3.data = 3;
	t4.data = 4;
	t5.data = 5;
	
	t1.lchild = &t2;
	t1.rchild = &t3;
	t2.lchild = &t4;
	t3.lchild = &t5;
#endif

	BPTree tree;

	tree.nodes[0].parentPosition = 1000;

	tree.nodes[1].parentPosition = 0;
	tree.nodes[1].data = 'B';
	tree.nodes[1].LRTab = 'r';
	
	tree.nodes[2].parentPosition = 0;
	tree.nodes[2].data = 'C';
	tree.nodes[2].LRTab = 'r';
	
	return 0;
}
