
// StudentSystemView.cpp: CStudentSystemView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "StudentSystem.h"
#endif

#include "StudentSystemDoc.h"
#include "StudentSystemView.h"
#include "DataChange.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStudentSystemView

IMPLEMENT_DYNCREATE(CStudentSystemView, CView)

BEGIN_MESSAGE_MAP(CStudentSystemView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_DELETE, &CStudentSystemView::OnDelete)
END_MESSAGE_MAP()

// CStudentSystemView 构造/析构

CStudentSystemView::CStudentSystemView() noexcept
{
	// TODO: 在此处添加构造代码
	//MessageBox(TEXT("子视图打开"));
}

CStudentSystemView::~CStudentSystemView()
{
}

BOOL CStudentSystemView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CStudentSystemView 绘图

void CStudentSystemView::OnDraw(CDC* pDC)
{
	CStudentSystemDoc* pDoc = GetDocument();//从这里得到了文件
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	//这里是VIEW中的绘制数据的函数体

	//GetDocument()可以获得相应的文档对象

	//pDC->TextOut(0, 0, TEXT("hello"));//可以在屏幕上显示出固定的文字

	//CString out;
	//out.Format(_T("%s"), (std::to_string(current_student)).c_str());
	//MessageBox(out);
	CFont *old_font = (CFont*)pDC->SelectStockObject(ANSI_FIXED_FONT);
	for (int i(0), len(pDoc->GetNumOfStudent()); i < len; ++i)
	{
		CString output;
		//output.Format("%s", "hello");
		//output.Format(200, "%s%s%s%s", "hello", "you", "son", "shit");
		//output = "hello";
		output.Format(_T("%-20.20s%-20.20s%-5.5s%-5.5s"),
			pDoc->data[i].name, pDoc->data[i].num, pDoc->data[i].sex, pDoc->data[i].age);
		if (i != current_student)
		{
			pDC->SetTextColor(RGB(0, 0, 0));
			pDC->SetBkColor(RGB(255, 255, 255));
		}
		else
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkColor(RGB(0, 0, 0));
		}
		
		pDC->TextOut(0, i * 20, output);
	}
	pDC->SelectObject(old_font);
}


// CStudentSystemView 打印

BOOL CStudentSystemView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CStudentSystemView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CStudentSystemView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CStudentSystemView 诊断

#ifdef _DEBUG
void CStudentSystemView::AssertValid() const
{
	CView::AssertValid();
}

void CStudentSystemView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CStudentSystemDoc* CStudentSystemView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStudentSystemDoc)));
	return (CStudentSystemDoc*)m_pDocument;
}
#endif //_DEBUG


// CStudentSystemView 消息处理程序


void CStudentSystemView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnLButtonDown(nFlags, point);
	current_student = point.y / 20;
	//OnUpdate;
	//OnDraw(WM_PAINT);
	RedrawWindow();
	//MessageBox("OUT");
}


void CStudentSystemView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnLButtonDblClk(nFlags, point);

	current_student = point.y / 20;

	CStudentSystemDoc* pDoc = GetDocument();//从这里得到了文件
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	
	if (current_student < pDoc->data.size())
	{
		DataChange dlg;
		//MessageBox("HOW");
		dlg.name = pDoc->data[current_student].name;
		dlg.num = pDoc->data[current_student].num;
		dlg.age = pDoc->data[current_student].age;

		//dlg.sex_index.SetCurSel(0);
		//if (pDoc->data[current_student].sex == "男")
			//dlg.sex_index.SetCurSel(0);
		//MessageBox("HOW");
		//else
			//dlg.sex_index.SetCurSel(1);

		UpdateData(FALSE);
		dlg.DoModal();

		if (dlg.change)
		{
			pDoc->DataChange(current_student, dlg.name, dlg.num, dlg.sex, dlg.age);
			pDoc->SetModifiedFlag(1);
		}
	}
	RedrawWindow();
}


void CStudentSystemView::OnDelete()
{
	// TODO: 在此添加命令处理程序代码
	CStudentSystemDoc* pDoc = GetDocument();//从这里得到了文件
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//与文件关联

	if (current_student < pDoc->data.size())
	{
		//只有有效的时候才进行这个操作
		pDoc->data.erase(pDoc->data.begin() + current_student);
		RedrawWindow();
	}
	return;
}
