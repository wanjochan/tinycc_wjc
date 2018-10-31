//clang -ldl -Os examples/test_osx_dl.c 
//clang examples/test_osx_dl.c
//clang examples/test_osx_dl.c && DYLD_INSERT_LIBRARIES=/usr/lib/libdl.dylib && ./a.out

typedef struct __FILE FILE;

//#include "tcc_dl.h"

//already in OSX/DKR?
//extern void *dlsym (void * handle, const char * name);
void *dlsym(void*handle,const char*name);//...

//#include <dlfcn.h>

#if __APPLE__
# define RTLD_DEFAULT	((void*)-2)
#else
# define RTLD_DEFAULT ((void*)0)
#endif

static FILE* buf_stdout;

static void* d(const char* s){
	return dlsym(RTLD_DEFAULT,s);
}

static inline typeof(void*(*)()) dd(const char* s){
	return d(s);
}

static inline FILE* get_std(){
	if(0==buf_stdout){
		buf_stdout = d("stdout");
	}else return buf_stdout;
	if(0==buf_stdout){
		buf_stdout = d("__stdoutp");
	}
	return buf_stdout;
}

int main(){
	dd("printf")("loaded\n");
	
	(dd("printf"))("%d\n",get_std());

	//	dlsym(RTLD_DEFAULT,"stderr"),
	
	//((void*(*)())dlsym(RTLD_DEFAULT,"printf"))("loaded\n");
	//typeof(dlsym(RTLD_DEFAULT,"stderr")) f;
	//typeof(dlsym(RTLD_DEFAULT,"__stderrp")) p;
	//((void*(*)())dlsym(RTLD_DEFAULT,"printf"))("%d,%d\n",
	//	dlsym(RTLD_DEFAULT,"stderr"),
	//	dlsym(RTLD_DEFAULT,"__stderrp")
	//	//sizeof(dlsym(RTLD_DEFAULT,"stderr"))//8
	//	//sizeof(f),sizeof(p)//8, seems just the size of the pointer... no meaning at all
	//);

	return 42;
}
