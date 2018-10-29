#include "tcc_libdl.h"

void* test_dlopen(const char* lib){
	return tcc_libdl_open(lib);
}

int main(){
	test_dlopen("libdl.so");
	return 42;
}
