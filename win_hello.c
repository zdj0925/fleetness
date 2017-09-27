#include <windows.h> 
//#include<iostream> 
//using namespace std;
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
void BeDaemon()
{
	pid_t ppid;
	ppid = fork();
	if(ppid)
	{
		exit(1);
	}
	
}
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	pid_t ppid = getpid();
	char a[15];
	MessageBox (NULL, "Hello", "Hello Demo0", MB_OK);
	sprintf(a, "%d",ppid);
	MessageBox (NULL, a, "Hello Demo1", MB_OK);
	BeDaemon();
	ppid = getpid();
	sprintf(a, "%d",ppid);
	MessageBox (NULL, a, "Hello Demo2", MB_OK);
	return (0);
}

