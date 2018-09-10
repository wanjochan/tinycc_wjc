#include <windows.h>

#include <stdio.h>
//#include "tcc.h"
//#include "libtcc.c"
//
////#include "tcctools.c"
//
int libtcc_dll_main(int argc0, char **argv0);

int main(int argc0, char **argv0)
{
	//TCCState *s;
	//printf("Hello World\n");
	//return 0;
	return libtcc_dll_main(argc0,argv0);
}


//int libtcc_dll_main(int argc0, char **argv0)

//__declspec(dllimport) extern const char *hello_data;

//int WINAPI WinMain(
//    HINSTANCE hInstance,
//    HINSTANCE hPrevInstance,
//    LPSTR     lpCmdLine,
//    int       nCmdShow)
//{
//    hello_data = "Hello World!";
//    hello_func();
//    return 0;
//}

//#include <windows.h>
//
//int WINAPI WinMain(
//    HINSTANCE hInstance,
//    HINSTANCE hPrevInstance,
//    LPSTR     lpCmdLine,
//    int       nCmdShow)
//{
//    return 0;
//}
//
