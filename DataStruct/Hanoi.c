// 汉诺塔
#include <stdio.h>

// 将n个盘子从x借助y移动到z
void move(int n, char x, char y, char z) {
	if ( 1 == n ) {
		printf("%c --> %c\n", x, z);
	}else{
		move(n-1, x, z, y);
		printf("%c --> %c\n", x, z);
		move(n-1, y, x, z);
	}
}

int main(int argc, char const *argv[])
{	
	move(3, 'x', 'y', 'z');
	return 0;
}
