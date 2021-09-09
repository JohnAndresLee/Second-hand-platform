#define _CRT_SECURE_NO_WARNINGS

#include "plus.h"
#include<iostream>
#include<cstring>

using namespace std;

int max(int a, int b)//考虑整数、0.……、.……
{
	if (a >= b)
		return a;
	else
		return b;
}
void input(char a[], char inte[], char deci[])//分别读入整数位、小数位
{
	int i = 0;
	if (a[i] == '.')
	{
		i++;
		inte[0] = '0';
	}
	else if (a[i] == '0')
	{
		inte[0] = '0';
		i += 2;
	}
	else
	{
		while (a[i] != '.' && a[i] != '\0')
		{
			inte[i] = a[i];
			i++;
		}
	}
	while (a[i] == '.')
		i++;
	if (a[i] == '\0')
		deci[0] = '0';
	else
	{
		int p = 0;
		while (a[i] != '\0')
			deci[p++] = a[i++];
	}
	return;
}
void completement1(char inte1[], char inte2[], int no1, int no2)//补整数部分位置
{
	if (no1 > no2)
	{
		int t = no1 - no2;
		for (int i = no2 - 1; i >= 0; --i)
			inte2[i + t] = inte2[i];
		for (int i = 0; i < t; ++i)
			inte2[i] = '0';
	}
	else
	{
		int t = no2 - no1;
		for (int i = no1 - 1; i >= 0; --i)
			inte1[i + t] = inte1[i];
		for (int i = 0; i < t; ++i)
			inte1[i] = '0';
	}
	return;
}
void completement2(char deci1[], char deci2[], int no1, int no2)//补小数部分位数
{
	if (no1 > no2)
	{
		for (int i = no2; i < no1; ++i)
			deci2[i] = '0';
	}
	else
	{
		for (int i = no1; i < no2; ++i)
			deci1[i] = '0';
	}
	return;
}
int calculate(char a[], char b[], char ans[], int no1, int no2, int k)
{
	int no = max(no1, no2);
	bool c[105] = { false };
	c[no] = k;
	for (int i = no - 1; i >= 0; --i)
	{
		ans[i] = a[i] + b[i] + c[i + 1] - 48;
		if (ans[i] >= 58)
		{
			c[i] = 1;
			ans[i] -= 10;
		}
	}
	return c[0];
}
void deletezero(char a[])
{
	int len = strlen(a), l = len;
	for (int i = len - 1; i >= 1; --i)
	{
		if (a[i] == '0')
		{
			a[i] = '\0';
			continue;
		}
		else break;
	}
	return;
}

void fplus(char a[], char b[], char balence[])
{
	char inte1[11] = { '\0' }, inte2[11] = { '\0' }, deci1[3] = { '\0' }, deci2[3] = { '\0' };
	input(a, inte1, deci1);
	input(b, inte2, deci2);
	int no1 = strlen(inte1), no2 = strlen(inte2);
	int len3 = strlen(deci1), len4 = strlen(deci2);
	if (no1 != no2)
		completement1(inte1, inte2, no1, no2);
	if (len3 != len4)
		completement2(deci1, deci2, len3, len4);
	char ansint[11] = { '\0' }, ansdeci[11] = { '\0' };
	int k1 = calculate(deci1, deci2, ansdeci, len3, len4, 0), k2 = calculate(inte1, inte2, ansint, no1, no2, k1);
	deletezero(ansdeci);
	if (k2 == 1)
	{
		balence[0] = '1';
		balence[1] = '\0';
	}
	else
		balence[0] = '\0';
	strcat(balence, ansint);
	strcat(balence,".");
	strcat(balence, ansdeci);
	
}