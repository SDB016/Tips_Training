#include "pch.h"

#include<stdio.h> // For printf
#include<malloc.h> // For malloc, free

void __stdcall UserProc(int a_id) // Callback function
{

}

void AppRun(void(*ap_user_proc)(int))
{
	(*ap_user_proc)(3);
}

void OS()
{
	AppRun();
}

int main() 
{


	return 0;
}