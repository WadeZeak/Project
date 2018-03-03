/////////////////////////////////////////////////////////////////////////////////////////
// 项目名称：网络机器人（网络爬虫）
// 编译环境：Visual Studio 2013
// 文件名称：NetworkIntelligentRobot.cpp
/////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include <iostream>
using namespace std;

#include "NetworkIntelligent.h"

void BFS(string beginURL)         // 宽度优先搜索遍历网页
{
	queue < string> q;
	q.push(beginURL);
	while (!q.empty())
	{
		string cur = q.front();
		mp[cur]++;
		q.pop();
		
		char tmp[800];
		strcpy(tmp, cur.c_str());
		analyUrl(tmp);
		preConnect();
		PutImagetoSet();

		vector<string>::iterator ita = photoUrl.begin();
		for (ita; ita != photoUrl.end(); ++ita)
		{
			OutImage(*ita);
		}
		photoUrl.clear();

		vector<string>::iterator it = comUrl.begin();
		for (it; it != comUrl.end(); ++it)
		{
			if (mp[*it] == 0)
				q.push(*it);
		}
		comUrl.clear();
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	int i = 0;
	string surl;
	cout << "请输入要抓取URL地址:";
	cin >> surl;
	CreateDirectoryA("./img", 0);
	BFS(surl);
	system("pause");
	return 0;
}

