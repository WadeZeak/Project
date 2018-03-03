#pragma once
class QQMessage
{
public:
	QQMessage();
	~QQMessage();

	//������ ����ģʽ ֻ������һ��ʵ������
	static QQMessage *Instance()
	{
		static QQMessage object;//��������
		return &object;
	}

	//��ں���
	void Start(const wchar_t *msg);

private:
	static unsigned int	 WINAPI	RunThreadProc(void *param);//��ʼ�߳�
	
	//���͵ĺ���
	void SendAll();

	//�ҵ�QQ���� ���
	HWND FindQQWindow();

	//ģ�ⰴ�� �ô���ʵ��
	void PressKey(BYTE vkey);//vkey ���̵������ֵ


	void SendMsg();//������Ϣ

	 //���ƺ��� ��ѡ�������ݱ��浽���а�
	void AddTextToClipboard();

private:
	CString m_msg;
};


