
// KuWoDlg.h : 头文件
//

#pragma once

typedef struct UIITEM
{
	//每个小方片在界面中的位置
	int x;
	int y;

	//每个小方片的大小
	int width;
	int height;

	//每个小方片在PNG图中的坐标
	int SrcX;
	int SrcY;

	//图片是否显示
	bool Show;

}UITEM,*PUITEM;


//对每一个小图片进行封装
typedef struct KUGOUUI 
{
	UITEM main;//中间的图形
	UITEM left;//左边的图形
	UITEM right; //右边的图形
	UITEM bottom;//底部的图形
	UITEM top;//顶部的图形
	UITEM item[5];//图形中间的小图标

	//整个界面的大小
	int height;
	int width;

}KUGOUUI,*PKUGOUUI;




// CKuWoDlg 对话框
class CKuWoDlg : public CDialogEx
{
// 构造
public:
	CKuWoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_KUWO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	//定义变量
	KUGOUUI m_kugouUI;//定义的界面变量
	Image *m_pSrcImage; //添加资源图片  用来保存图片的指针
	bool m_Play;//判断鼠标是否在中心位置(对话框区域)





	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void InitUI();
	// 用来对每个小方片进行处理
	UIITEM MakeUiItem(int x, int y, int height, int width, int SrcX, int SrcY,bool Show);
	// 用来从个资源文件中获取图片
	int LoadRecImage(int nRecID, Image* img);
};
