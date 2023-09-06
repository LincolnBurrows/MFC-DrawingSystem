
// DrawingSystemDlg.h: 头文件
//

#pragma once

enum drawMode
{
	pointMode,
	lineMode,
	ellipseMode,
	rectangleMode,
	freeMode,
	textMode
};

// CDrawingSystemDlg 对话框
class CDrawingSystemDlg : public CDialogEx
{
// 构造
public:
	CDrawingSystemDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRAWINGSYSTEM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	COLORREF LineColor;  // 线条颜色
	COLORREF ShapeColor; // 图形填充颜色
	CComboBox m_fill;
	CPoint DownPoint;
	CComboBox m_drawStyle; // 绘制类型
	bool isfilled; // 是否被填充 false： 无填充， true：有填充
	bool LineType;	// 线条类型 false：实线， true：虚线
	bool buttonDown; // 鼠标是否按下，true 按下; false 抬起
	int LineWidth;	// 线条宽度	
	int PenType;  // 画笔线类型， 默认实线， 虚线为PS_DASH
	int m_LineType;
	drawMode mode;
	CString insertText; // 要插入的文本	
						// 采用图片控件插入图片
	CStatic m_img; // 采用图片控件插入图片	
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
};
