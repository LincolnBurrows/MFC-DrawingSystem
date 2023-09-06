
// DrawingSystemDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "DrawingSystem.h"
#include "DrawingSystemDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:

};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)

END_MESSAGE_MAP()


// CDrawingSystemDlg 对话框

CDrawingSystemDlg::CDrawingSystemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DRAWINGSYSTEM_DIALOG, pParent)
	, LineWidth(0)
	, m_LineType(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDrawingSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, LineWidth);
	DDX_Text(pDX, IDC_EDIT3, insertText);
	DDV_MinMaxInt(pDX, LineWidth, 0, 20);
	DDX_Radio(pDX, IDC_RADIO1, m_LineType);
	DDX_Control(pDX, IDC_COMBO1, m_fill);
	DDX_Control(pDX, IDC_COMBO2, m_drawStyle);
	DDX_Control(pDX, IDC_IMG, m_img);
}

BEGIN_MESSAGE_MAP(CDrawingSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDrawingSystemDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDrawingSystemDlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT1, &CDrawingSystemDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_RADIO1, &CDrawingSystemDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CDrawingSystemDlg::OnBnClickedRadio2)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDrawingSystemDlg::OnCbnSelchangeCombo1)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_CBN_SELCHANGE(IDC_COMBO2, &CDrawingSystemDlg::OnCbnSelchangeCombo2)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON3, &CDrawingSystemDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDrawingSystemDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CDrawingSystemDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CDrawingSystemDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CDrawingSystemDlg 消息处理程序

BOOL CDrawingSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	LineColor = RGB(0, 0, 255); // 线条颜色初始化为蓝色
	ShapeColor = RGB(255, 0, 0); // 图形颜色初始化为红色

	PenType = PS_SOLID; // 画笔线类型， 默认实线， 虚线为PS_DASH

	LineWidth = 5; // 线条粗细初始化为5
	UpdateData(false);

	m_fill.AddString(TEXT("有填充"));
	m_fill.AddString(TEXT("无填充"));
	m_fill.SetCurSel(0);

	isfilled = true; // 是否被填充 false： 无填充， true：有填充

	m_drawStyle.AddString(TEXT("点"));
	m_drawStyle.AddString(TEXT("线"));
	m_drawStyle.AddString(TEXT("圆"));
	m_drawStyle.AddString(TEXT("矩形"));
	m_drawStyle.AddString(TEXT("自由绘制"));
	m_drawStyle.SetCurSel(0);

	buttonDown = false; // 初始化， 鼠标没按下

	mode = pointMode;  // 初始化绘制模式为点模式

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDrawingSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDrawingSystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDrawingSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 设置线条颜色
void CDrawingSystemDlg::OnBnClickedButton1()
{ 
	// 创建颜色对话框
	CColorDialog colorDlg(LineColor);  // 构造对话框，传入初始颜色值   

	if (IDOK == colorDlg.DoModal()) // 显示对话框并判断是否点击“确定”   
	{
		LineColor = colorDlg.GetColor();    // 获取颜色对话框中选择的颜色值   
	}
}

// 设置图形颜色
void CDrawingSystemDlg::OnBnClickedButton2()
{
	// 创建颜色对话框
	CColorDialog colorDlg(ShapeColor);  // 构造对话框，传入初始颜色值   

	if (IDOK == colorDlg.DoModal()) // 显示对话框并判断是否点击“确定”   
	{
		ShapeColor = colorDlg.GetColor();    // 获取颜色对话框中选择的颜色值   
	}
}


 // 线条宽度改变事件
void CDrawingSystemDlg::OnEnChangeEdit1()
{
	UpdateData(true);
}

// 线条类型 实线
void CDrawingSystemDlg::OnBnClickedRadio1()
{
	LineType = false;
	m_LineType = false;
	if (!LineType)
	{
		PenType = PS_SOLID; // 实线
	}
}

// 线条类型 虚线
void CDrawingSystemDlg::OnBnClickedRadio2()
{
	LineType = true;
	m_LineType = true;
	if (LineType)
	{
		PenType = PS_DASH; // 虚线
		LineWidth = 1;  // 虚线宽度不可以更改， 必须为1
		UpdateData(false);
	}
}


void CDrawingSystemDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
    int index = m_fill.GetCurSel();
	if (index == 0)
	{
		isfilled = true;
	}
	if (index == 1)
	{
		isfilled = false;
	}
}

// 点击鼠标，画点或者插入文本
void CDrawingSystemDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	DownPoint = point;
	buttonDown = true;
	CClientDC dc(this); // 用于绘制的设备上下文

	if (mode == pointMode)
	{
		
		dc.SetPixel(point.x, point.y, LineColor);
	}
	if (mode == textMode)
	{
		dc.TextOut(point.x, point.y, insertText, sizeof(insertText)); // 在指定位置绘制文本

		int index = m_drawStyle.GetCurSel();

		switch (index)
		{
		case 0:
			mode = pointMode;
			break;
		case 1:
			mode = lineMode;
			break;
		case 2:
			mode = ellipseMode;
			break;
		case 3:
			mode = rectangleMode;
			break;
		case 4:
			mode = freeMode;
			break;
		default:
			break;
		}



	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CDrawingSystemDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	CClientDC dc(this); // 用于绘制的设备上下文
	buttonDown = false;

	switch (mode)
	{
	case pointMode:
		break;
	case lineMode:
		{
			CPen pen;
			pen.CreatePen(PenType, LineWidth, LineColor);
			dc.SelectObject(&pen);

			dc.MoveTo(DownPoint.x, DownPoint.y);
			dc.LineTo(point.x, point.y);
		}
		break;
	case ellipseMode:
		{		
			// 定义画笔
			CPen MyPen, * OldPen;
			MyPen.CreatePen(PenType, LineWidth, LineColor);
			OldPen = dc.SelectObject(&MyPen);

			// 画刷
			CBrush MyBrush, * OldBrush;
			if (isfilled)
			{
				MyBrush.CreateSolidBrush(ShapeColor);
			}
			else 
			{
				MyBrush.CreateSolidBrush(RGB(180, 180, 180));
			}
			
			OldBrush = dc.SelectObject(&MyBrush);

			// 定义坐标点
			CPoint point1(DownPoint);
			CPoint point2(point);

			// 绘制椭圆
			dc.Ellipse(point1.x, point1.y, point2.x, point2.y);

			// 清除
			dc.SelectObject(OldPen);
			MyPen.DeleteObject();
			dc.SelectObject(OldBrush);
			MyBrush.DeleteObject();
		}
		break;			   
	case rectangleMode:
		{
			// 定义画笔绘制矩形
			CPen pen(PenType, LineWidth, LineColor); 
			dc.SelectObject(&pen);
			CBrush bush;
			if (isfilled)
			{
				bush.CreateSolidBrush(ShapeColor);
			}
			else
			{
				bush.CreateSolidBrush(RGB(180, 180, 180));
			}
		
			dc.SelectObject(bush);

			//定义坐标点
			CPoint point1(DownPoint);
			CPoint point2(point);

			//绘制矩形
			dc.Rectangle(point1.x, point1.y, point2.x, point2.y);
		}
		break;
	case freeMode:
		break;
	default:
		break;
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}

// 修改绘制类型
void CDrawingSystemDlg::OnCbnSelchangeCombo2()
{
	int index = m_drawStyle.GetCurSel();

	switch (index)
	{
		case 0:
			mode = pointMode;
			break;
		case 1:
			mode = lineMode;
			break;
		case 2:
			mode = ellipseMode;
			break;
		case 3:
			mode = rectangleMode;
			break;
		case 4:
			mode = freeMode;
			break;
		default:
			break;
	}
}


void CDrawingSystemDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this); // 用于绘制的设备上下文

	if (mode == freeMode && buttonDown == true)
	{
		CPen pen;
		pen.CreatePen(PenType, LineWidth, LineColor);
		dc.SelectObject(&pen);

		dc.MoveTo(DownPoint.x, DownPoint.y);
		dc.LineTo(point.x, point.y);

		DownPoint = point;
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CDrawingSystemDlg::OnBnClickedButton3()
{
	UpdateData(true);
	MessageBox(TEXT("请鼠标点击要插入的位置"), TEXT("提示"));
	mode = textMode;
}

// 插入图片
void CDrawingSystemDlg::OnBnClickedButton4()
{  
	// 设置过滤器   
	TCHAR szFilter[] = _T("图片(*.png)|*.png|所有文件(*.*)|*.*||");
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("png"), NULL, 0, szFilter, this);
	CString strFilePath;

	// 显示打开文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetPathName();

		CClientDC dc(this); // 用于绘制的设备上下文
		CRect rect;
		GetClientRect(&rect);
		CImage image;
		image.Load(strFilePath);
		image.BitBlt(dc, 0, 0, rect.Width(), rect.Height(), 0, 0);
		image.Destroy();    //没有Destroy()会有内存泄漏。Detach();不行的。
	}
}

// 清空画板
void CDrawingSystemDlg::OnBnClickedButton5()
{
	Invalidate(TRUE);
}


void CDrawingSystemDlg::OnBnClickedButton6()
{
	// 设置过滤器   
	TCHAR szFilter[] = _T("图片(*.png)|*.png|所有文件(*.*)|*.*||");
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("png"), NULL, 0, szFilter, this);
	CString strFilePath;

	//CStatic* pStatic = (CStatic*)GetDlgItem(IDC_IMG);//得到控件

	if (IDOK == fileDlg.DoModal()) {

		strFilePath = fileDlg.GetPathName();

		CImage image;
		image.Load(strFilePath);  //加载图片

		CRect zcRect;
		m_img.GetClientRect(&zcRect);   //得到尺寸

		image.Draw(m_img.GetDC()->m_hDC,
			zcRect.left,
			zcRect.top,
			zcRect.Width(),
			zcRect.Height());
		image.Destroy();
	}
	
}
