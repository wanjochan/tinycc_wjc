#include "tcc_dl.h"

int fib(n)
{
	if (n <= 2)
		return 1;
	else
		return fib(n-1) + fib(n-2);
}

int main(int argc, char **argv)
{
	char buf[2048]={'\0'};

	TCC(fprintf)(stderr, "%s\n", buf);
	TCC(fflush)(stderr);
	
	//TCC_DL_IMPORT(c);//libc
	//TCC_DL_IMPORT(qt);//libqt

	int n;
	if (argc < 2) {
		TCC(printf)("usage: fib n\n" "Compute nth Fibonacci number\n");
		return 1;
	}

	n = (int) TCC(atoi)(argv[1]);
	TCC(printf)("fib(%d) = %d\n", n, fib(n, 2));
	return 0;
}
