/////////////////////////////////////////////////////////////////////////////////////////
// 项目名称：网络机器人（网络爬虫）
// 编译环境：Visual Studio 2013
// 文件名称：NetworkIntelligent.h
// 开发作者：张三 李四
// 修改日期：2017-04-13
/////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <regex>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

char   host[500];
int    num = 1;
char   othPath[800];
string allHtml;

vector<string> photoUrl;
vector<string> comUrl;
map   <string, int> mp;

SOCKET sock;

bool analyUrl(char *url)          // 分析URL
{
	char *pos = strstr(url, "http://");
	if (pos == NULL)
		return false;
	else
		pos = pos + 7;

	sscanf(pos, "%[^/]%s", host, othPath);
	cout << "Host:" << host << " repath:" << othPath << endl;

	return true;
}

void regexGetimage(string &allHtml)  // 正则表达式提取图片URL
{
	smatch mat;
	regex pattern("src=\"(.*?\.jpg)\"");
	string::const_iterator start = allHtml.begin();      // 迭代器开始
	string::const_iterator end = allHtml.end();          // 迭代器结束

	// 搜索正则表达式
	while (regex_search(start, end, mat, pattern))
	{
		string msg(mat[1].first, mat[1].second);
		photoUrl.push_back(msg);
		start = mat[0].second;
	}
}

void regexGetcom(string &allHtml)      // 提取网页中的http://的URL
{
	smatch mat;
	regex pattern("href=\"(http://[^\s'\"]+)\"");
	string::const_iterator start = allHtml.begin();
	string::const_iterator end = allHtml.end();

	// 搜索正则表达式
	while (regex_search(start, end, mat, pattern))
	{
		string msg(mat[1].first, mat[1].second);
		comUrl.push_back(msg);
		start = mat[0].second;
	}
}

void preConnect()          // Socket网络连接
{
	WSADATA wd;
	WSAStartup(MAKEWORD(2, 2), &wd);          // Windows异步套接字启动命令

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		cout << "建立socket套接字失败，系统错误编码:" << WSAGetLastError() << endl;
		return;
	}

	sockaddr_in sa = { AF_INET };
	int n = bind(sock, (sockaddr*)&sa, sizeof(sa));       //绑定套接字
	if (n == SOCKET_ERROR)
	{
		cout << "绑定bind函数已失败，系统错误编码:" << WSAGetLastError() << endl;
		return;
	}

	struct hostent *p = gethostbyname(host);            // 根据主机名称得到主机信息
	if (p == NULL)
	{
		cout << "主机无法解析出IP地址，系统错误编码:" << WSAGetLastError() << endl;
		return;
	}
	sa.sin_port = htons(80);
	memcpy(&sa.sin_addr, p->h_addr, 4);
	n = connect(sock, (sockaddr*)&sa, sizeof(sa));     // 发起连接请求
	if (n == SOCKET_ERROR){
		cout << "连接connect函数失败，系统错误编码:" << WSAGetLastError() << endl;
		return;
	}

	// 向服务器发送GET请求，模拟浏览器的请求 下载图片
	string reqInfo = "GET" + (string)othPath + " HTTP/1.1\r\nHost: " + (string)host + "\r\nConnection:Close\r\n\r\n";
	if (SOCKET_ERROR == send(sock, reqInfo.c_str(), reqInfo.size(), 0))
	{
		cout << "发送send函数失败，系统错误编码:" << WSAGetLastError() << endl;
		return;
	}
}

void OutImage(string imageUrl)        // 将图片命名存储到目录下
{
	int n;
	char temp[800];
	strcpy(temp, imageUrl.c_str());
	analyUrl(temp);                       // 支持HTTP协议，解析出主机和IP地址
	preConnect();                         // socket网络连接
	string photoname;
	photoname.resize(imageUrl.size());
	int k = 0;
	for (int i = 0; i < imageUrl.length(); i++){
		char ch = imageUrl[i];
		if (ch != '\\' && ch != '/'&& ch != ':'&& ch != '*'&& ch != '?'&& ch != '"'&& ch != '<'&& ch != '>'&& ch != '|')
			photoname[k++] = ch;
	}
	photoname = "./img/" + photoname.substr(0, k) + ".jpg";

	fstream file;
	file.open(photoname, ios::out | ios::binary);
	char buf[1024];
	memset(buf, 0, sizeof(buf));
	n = recv(sock, buf, sizeof(buf) - 1, 0);
	char *cpos = strstr(buf, "\r\n\r\n");

	file.write(cpos + strlen("\r\n\r\n"), n - (cpos - buf) - strlen("\r\n\r\n"));
	while ((n = recv(sock, buf, sizeof(buf) - 1, 0)) > 0)
	{
		file.write(buf, n);
	}
	file.close();
}

void PutImagetoSet()             // 解析整个html代码
{
	int n;
	char buf[1024];
	while ((n = recv(sock, buf, sizeof(buf) - 1, 0)) > 0)
	{
		buf[n] = '\0';
		allHtml += string(buf);
	}
	regexGetimage(allHtml);         // 正则表达式提取图片URL
	regexGetcom(allHtml);           // 提取网页中的http://的URL
}

void BFS(string beginUrl);          // 宽度优先搜索遍历整个网页

