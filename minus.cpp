#define _CRT_SECURE_NO_WARNINGS

#include "minus.h"
#include<cstdio>

bool judge(char a[], char b[])
{
	double aa,bb;
	int temp1=sscanf(a, "%lf", &aa);
	int temp2=sscanf(b, "%lf", &bb);
	if (aa >= bb)
		return true;
	else
		return false;
}

void fminus(char aa[], char bb[],char balence[])
{
	double a;
	int temp1=sscanf(aa,"%lf", &a);
	double b;
	int temp2=sscanf(bb, "%lf", &b);
	double ans = a - b;
	sprintf(balence, "%.1lf", ans);
}