# include <stdio.h>

int main(void)
{
	int i = -5;
	printf("%#X\n", i);

	int j = 0xFFFFFFF5;
	printf("%d\n", j);

	char ch = 0x80;
	printf("%d\n", ch);

	ch = 128;// (0000 0000 0000 0000 0000 0000)(1000 0000)数据溢出，前三个字节会丢失，(1000 0000)为-128
	printf("%d\n", ch);

	ch = 129;// (0000 0000 0000 0000 0000 0000)(1000 0001)数据溢出，前三个字节会丢失，(1000 0001)为-127
	printf("%d\n", ch);

	ch = 130;// (0000 0000 0000 0000 0000 0000)(1000 0010)数据溢出，前三个字节会丢失，(1000 0010)为-126
	printf("%d\n", ch);

	return 0;
}