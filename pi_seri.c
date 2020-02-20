#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 1000
#define PI acos(-1)

double f(double x)
{
	return 4.0/(1.0+x*x);
}


int main(void)
{
	int i;
	double top=0.0;
	double h=1.0/(double)N;

	for(i=1; i<=N; i++)
	{
		top+= f(i*h);
	}

	top *=h;
	printf("Gerçek PI =%.16f\n",PI);
	printf("yAKLAŞIK PI =%.16f\n",top);

}



