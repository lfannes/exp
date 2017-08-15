#include <iostream>

using namespace std;

int som(int a, int b);
int product(int p, int q);
int bereken(int x, int y, int (*fp) (int, int));
int* max(int x, int y);

int main()
{
	int (*prut) (int, int);
	int* resultatMax = max(56, 78);
	cout << *resultatMax << endl;

	cout << bereken(45, 15, som) << endl;
	cout << bereken(12, 10, product) << endl;
	prut = product;
	cout << prut(10, 10) << endl;
	return 0;
}

int som(int a, int b)
{
	return (a + b);
}

int product(int p, int q)
{
	return(p * q);
}

int* max(int x, int y)
{
	int* maxNumber;
	if (x < y)
	{
		maxNumber = &y;
	}
	else
	{
		maxNumber = &x;
	}
	return maxNumber;
}

int bereken(int x, int y, int (*fp) (int, int))
{
	return fp(x, y);
}