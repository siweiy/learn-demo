// 约瑟夫 --- 数3出局
#include <stdio.h>
#include <stdlib.h>

typedef struct Josephus {
	int data;
	struct Josephus *next;
}node;

node *create(int n) {
	node *p = NULL, *head;
	head = (node *)malloc(sizeof(node));
	p = head;

	node *s;
	int i = 1;

	if (0 != n) {
		while (i <= n) {
			s = (node *)malloc(sizeof(node));
			s->data = i++;
			p->next = s;
			p = s;
		}

		s->next = head->next;// 循环链表
	}

	free(head);

	return s->next;
}


int main(int argc, char const *argv[])
{
	int i;
	int n = 41;
	int m = 3;
	
	node *p = create(n);
	node *tmp;

	m = n % m;

	while (p != p->next) {
		for (i = 1; i < m; i++) {
			p = p->next;
		}

		printf("%d->", p->next->data);
		tmp = p->next;
		p->next = tmp->next;

		free(tmp);

		p = p->next;
	}

	printf("%d->", p->data);

	return 0;
}
