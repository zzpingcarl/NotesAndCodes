#include <stdio.h>
int main(void)
{
	int i = 10;
	int k = 20;
	int m;

	m = (3>2) || (k=0);//k为0是为假，k不是0时为真
	printf("m = %d,k = %d\n", m, k);
	return 0;
}