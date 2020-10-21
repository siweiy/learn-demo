#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 二叉链表法
typedef struct BiTree
{
	int data;
	struct BiTree *lchild, *rchild;
} BiTree, *pBiTree;

// 先序遍历
void preOder(BiTree *root)
{
	if (root == NULL)
	{
		return;
	}

	printf("%d ", root->data);
	preOder(root->lchild);
	preOder(root->rchild);

	return;
}

// 中序遍历
void inOder(BiTree *root)
{
	if (root == NULL)
	{
		return;
	}

	preOder(root->lchild);
	printf("%d ", root->data);
	preOder(root->rchild);

	return;
}

// 后序遍历
void postOder(BiTree *root)
{
	if (root == NULL)
	{
		return;
	}

	preOder(root->lchild);
	preOder(root->rchild);
	printf("%d ", root->data);

	return;
}

// 求叶子结点
void countLeaf(BiTree *root, int *sum)
{
	if (root)
	{
		if (!root->lchild && !root->rchild) {
			(*sum)++;
		}
		if (root->lchild) {
			countLeaf(root->lchild, sum);
		}
		if (root->rchild) {
			countLeaf(root->lchild, sum);
		}
	}
}

// 树深度
int depth(BiTree *root)
{
	int deptLeft = 0;
	int deptRight = 0;
	int deptVal = 0;

	if (root == NULL) {
		deptVal = 0;
		return deptVal;	
	}

	deptLeft = depth(root->lchild);
	deptRight = depth(root->rchild);

	deptVal = 1 + (deptLeft > deptRight ? deptLeft:deptRight);

	return deptVal;
}

// 树拷贝
BiTree *CopyTree(BiTree *root)
{
	
	return NULL;
}

int main(int argc, char const *argv[])
{
	BiTree t1, t2, t3, t4, t5;
	memset(&t1, 0, sizeof(BiTree));
	memset(&t2, 0, sizeof(BiTree));
	memset(&t3, 0, sizeof(BiTree));
	memset(&t4, 0, sizeof(BiTree));
	memset(&t5, 0, sizeof(BiTree));

	t1.data = 1;
	t2.data = 2;
	t3.data = 3;
	t4.data = 4;
	t5.data = 5;

	t1.lchild = &t2;
	t1.rchild = &t3;
	t2.lchild = &t4;
	t3.lchild = &t5;

	preOder(&t1);
	printf("\n");
	inOder(&t1);
	printf("\n");
	postOder(&t1);
	printf("\n");

	int sum = 0;
	countLeaf(&t1, &sum);
	printf("sum = %d\n", sum);

	printf("depth = %d\n", depth(&t1));

	BiTree *cp_root = CopyTree(&t1);

	return 0;
}
