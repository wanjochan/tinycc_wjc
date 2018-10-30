//#include "tcc_libc.h"
#include "tcc.h"

int main(){
	TCC(printf)("%s = %s\n", "__TCC_TARGET_CPU__", TCC_QUOTE(__TCC_TARGET_CPU__));
	TCC(printf)("%s = %s\n", "__TCC_TARGET_CPU_BIT__", TCC_QUOTE(__TCC_TARGET_CPU_BIT__));
	TCC(printf)("%s = %s\n", "__TCC_TARGET_OS__", TCC_QUOTE(__TCC_TARGET_OS__));

	//FMT
	TCC(printf)("%s = %s\n", "__TCC_TARGET_FORMAT__", TCC_QUOTE(__TCC_TARGET_FORMAT__));

	// IS IT CROSS BUILD TODO USE strcmp in program later??
	//TCC(printf)("%s = %s\n", "__TCC_TARGET_CROSS__", TCC_QUOTE(__TCC_TARGET_CROSS__));

	TCC(printf)("%s = %s\n", "TEST", TCC_QUOTE(xxx-__TCC_TARGET_CPU_BIT__-__TCC_TARGET_CPU__-__TCC_TARGET_OS__-__TCC_TARGET_FORMAT__));


	TCC(printf)("PTR_SIZE=%d\n",PTR_SIZE);
	TCC(printf)("%s=%d\n", "5 % 3",5 % 3);
	return 42;
}
