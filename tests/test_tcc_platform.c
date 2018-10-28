/*
./build_Darwin_x86_64/tcc -B build_Darwin_x86_64 -I . -run tests/test_tcc_platform.c
*/

#include "tcc_platform.h"
#include "tcc_libc.h"

void ppff(char* fmt, ...){
	va_list ap;
	va_start(ap, fmt);
	TCC(vprintf)(fmt, ap);
	va_end(ap);
}

int main(int argc, char **argv)
{
	// CURRENT
	ppff("%s = %s\n", "__TCC_CPU__", TCC_QUOTE(__TCC_CPU__));
	ppff("%s = %s\n", "__TCC_CPU_BIT__", TCC_QUOTE(__TCC_CPU_BIT__));
	ppff("%s = %s\n", "__TCC_OS__", TCC_QUOTE(__TCC_OS__));

	//CC
	ppff("%s = %s\n", "__TCC_CC__", TCC_QUOTE(__TCC_CC__));

	// FOR TCC BUILD TARGET
	ppff("%s = %s\n", "__TCC_TARGET_CPU__", TCC_QUOTE(__TCC_TARGET_CPU__));
	ppff("%s = %s\n", "__TCC_TARGET_CPU_BIT__", TCC_QUOTE(__TCC_TARGET_CPU_BIT__));
	ppff("%s = %s\n", "__TCC_TARGET_OS__", TCC_QUOTE(__TCC_TARGET_OS__));
	
	//FMT
	ppff("%s = %s\n", "__TCC_TARGET_FORMAT__", TCC_QUOTE(__TCC_TARGET_FORMAT__));

	// IS IT CROSS BUILD TODO USE strcmp in program later??
	//ppff("%s = %s\n", "__TCC_TARGET_CROSS__", TCC_QUOTE(__TCC_TARGET_CROSS__));

	return 42;
}
