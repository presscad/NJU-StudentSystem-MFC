// CDlgHowToPlay.cpp: 实现文件
//

#include "stdafx.h"
#include "StudentSystem.h"
#include "CDlgHowToPlay.h"
#include "afxdialogex.h"


// CDlgHowToPlay 对话框

IMPLEMENT_DYNAMIC(CDlgHowToPlay, CDialogEx)

CDlgHowToPlay::CDlgHowToPlay(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HOWTOPLAY, pParent)
{

}

CDlgHowToPlay::~CDlgHowToPlay()
{
}

void CDlgHowToPlay::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgHowToPlay, CDialogEx)
	//ON_COMMAND(ID_HOWTOPLAY, &CDlgHowToPlay::OnHowtoplay)
END_MESSAGE_MAP()


// CDlgHowToPlay 消息处理程序


