all:
	i686-w64-mingw32-gcc win_hello.c -o hello.exe -mwindows -Wimplicit-function-declaration -Wint-conversion 
