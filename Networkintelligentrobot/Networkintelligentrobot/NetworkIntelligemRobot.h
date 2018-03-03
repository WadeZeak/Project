/////////////////////////////////////////////////////////////////////////////////////////
// ��Ŀ���ƣ���������ˣ��������棩
// ���뻷����Visual Studio 2013
// �ļ����ƣ�NetworkIntelligent.h
// �������ߣ����� ����
// �޸����ڣ�2017-04-13
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

bool analyUrl(char *url)          // ����URL
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

void regexGetimage(string &allHtml)  // ������ʽ��ȡͼƬURL
{
	smatch mat;
	regex pattern("src=\"(.*?\.jpg)\"");
	string::const_iterator start = allHtml.begin();      // ��������ʼ
	string::const_iterator end = allHtml.end();          // ����������

	// ����������ʽ
	while (regex_search(start, end, mat, pattern))
	{
		string msg(mat[1].first, mat[1].second);
		photoUrl.push_back(msg);
		start = mat[0].second;
	}
}

void regexGetcom(string &allHtml)      // ��ȡ��ҳ�е�http://��URL
{
	smatch mat;
	regex pattern("href=\"(http://[^\s'\"]+)\"");
	string::const_iterator start = allHtml.begin();
	string::const_iterator end = allHtml.end();

	// ����������ʽ
	while (regex_search(start, end, mat, pattern))
	{
		string msg(mat[1].first, mat[1].second);
		comUrl.push_back(msg);
		start = mat[0].second;
	}
}

void preConnect()          // Socket��������
{
	WSADATA wd;
	WSAStartup(MAKEWORD(2, 2), &wd);          // Windows�첽�׽�����������

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		cout << "����socket�׽���ʧ�ܣ�ϵͳ�������:" << WSAGetLastError() << endl;
		return;
	}

	sockaddr_in sa = { AF_INET };
	int n = bind(sock, (sockaddr*)&sa, sizeof(sa));       //���׽���
	if (n == SOCKET_ERROR)
	{
		cout << "��bind������ʧ�ܣ�ϵͳ�������:" << WSAGetLastError() << endl;
		return;
	}

	struct hostent *p = gethostbyname(host);            // �����������Ƶõ�������Ϣ
	if (p == NULL)
	{
		cout << "�����޷�������IP��ַ��ϵͳ�������:" << WSAGetLastError() << endl;
		return;
	}
	sa.sin_port = htons(80);
	memcpy(&sa.sin_addr, p->h_addr, 4);
	n = connect(sock, (sockaddr*)&sa, sizeof(sa));     // ������������
	if (n == SOCKET_ERROR){
		cout << "����connect����ʧ�ܣ�ϵͳ�������:" << WSAGetLastError() << endl;
		return;
	}

	// �����������GET����ģ������������� ����ͼƬ
	string reqInfo = "GET" + (string)othPath + " HTTP/1.1\r\nHost: " + (string)host + "\r\nConnection:Close\r\n\r\n";
	if (SOCKET_ERROR == send(sock, reqInfo.c_str(), reqInfo.size(), 0))
	{
		cout << "����send����ʧ�ܣ�ϵͳ�������:" << WSAGetLastError() << endl;
		return;
	}
}

void OutImage(string imageUrl)        // ��ͼƬ�����洢��Ŀ¼��
{
	int n;
	char temp[800];
	strcpy(temp, imageUrl.c_str());
	analyUrl(temp);                       // ֧��HTTPЭ�飬������������IP��ַ
	preConnect();                         // socket��������
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

void PutImagetoSet()             // ��������html����
{
	int n;
	char buf[1024];
	while ((n = recv(sock, buf, sizeof(buf) - 1, 0)) > 0)
	{
		buf[n] = '\0';
		allHtml += string(buf);
	}
	regexGetimage(allHtml);         // ������ʽ��ȡͼƬURL
	regexGetcom(allHtml);           // ��ȡ��ҳ�е�http://��URL
}

void BFS(string beginUrl);          // ���������������������ҳ

