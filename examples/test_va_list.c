#include "tcc_libc.h"
#include "tcc_stdarg.h"
//#include <stdarg.h>

void ppff(char* fmt, ...){
	va_list ap;
	va_start(ap, fmt);
	TCC(vprintf)(fmt, ap);
	//TCC(fputs)("Error: ", stderr);
	//TCC(vfprintf)(stderr, fmt, ap);
	va_end(ap);
}

//for typeof, It's a GNU extension, not c99
//#define typeof __typeof__
//typeof(va_list）
int main(int argc, char **argv)
{
	int n =33;
	TCC(printf)("(%d) = %d\n", n, 111);
	ppff("(%d) = %d\n", n, 333);
	return 0;
}
