#pragma once
class QQMessage
{
public:
	QQMessage();
	~QQMessage();

	//类的入口 单例模式 只允许创建一个实例对象
	static QQMessage *Instance()
	{
		static QQMessage object;//创建对象
		return &object;
	}

	//入口函数
	void Start(const wchar_t *msg);

private:
	static unsigned int	 WINAPI	RunThreadProc(void *param);//开始线程
	
	//发送的函数
	void SendAll();

	//找到QQ窗口 句柄
	HWND FindQQWindow();

	//模拟按键 用代码实现
	void PressKey(BYTE vkey);//vkey 键盘的虚拟键值


	void SendMsg();//发送消息

	 //复制函数 将选定的内容保存到剪切板
	void AddTextToClipboard();

private:
	CString m_msg;
};


