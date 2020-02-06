#include "pch.h"

#include<stdio.h> // For printf
#include<malloc.h> // For malloc, free



void UserProc(int a_id) // Callback function
{

}

struct WINDCLASS
{
	int size;
	void (*p_user_proc)(int);
};

struct WINDCLASSEX
{
	int size;
	void (*p_user_proc)(int);
	int data;
};

void AppRun(WINDCLASS *ap_wnd_class)
{
	ap_wnd_class->p_user_proc(3);
}

void OS()
{
	AppRun();
}

int main() 
{


	return 0;
}