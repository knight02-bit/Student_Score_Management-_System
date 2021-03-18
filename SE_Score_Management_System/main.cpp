
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <windows.h>
#include"fuctionState.h"
#include"dealInfor.cpp"
#include"searchInfor.cpp"

int main()
{
	Stu* pHead = (Stu*)malloc(sizeof(Stu));
	memset(pHead, 0, sizeof(Stu));
	pHead->next = NULL;

	Load_data(pHead);//МгдиЪ§Он 
	Select_fuction(pHead); 
	
	free(pHead);
	return 0;
}
