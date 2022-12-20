
// CircleWindowDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "CircleWindow.h"
#include "CircleWindowDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCircleWindowDlg 대화 상자



CCircleWindowDlg::CCircleWindowDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CIRCLEWINDOW_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCircleWindowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCircleWindowDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CCircleWindowDlg 메시지 처리기

BOOL CCircleWindowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.
	
	CRgn rgn;
	rgn.CreateEllipticRgn(0, 0, 200, 200);
	SetWindowRgn(rgn, TRUE);

	SetBackgroundColor(RGB(0, 200, 255));

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCircleWindowDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CCircleWindowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCircleWindowDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_is_clicked == 0)
	{
		m_is_clicked = 1;
		GetCursorPos(&m_prev_pos); // 전체 윈도우 기준으로 좌표값 가져와줌
		SetCapture(); // 내 윈도우 밖으로 마우스가 빠져나가더라도 계속 마우스 메시지를 받을수있게해줌
	}
	
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CCircleWindowDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_is_clicked == 1)
	{
		m_is_clicked = 0;
		ReleaseCapture(); // SetCapture 해제
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CCircleWindowDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_is_clicked == 1)
	{
		CRect r;
		GetWindowRect(r);

		CPoint pos;
		GetCursorPos(&pos);

		SetWindowPos(NULL, r.left + pos.x - m_prev_pos.x, r.top + pos.y - m_prev_pos.y, 0, 0, SWP_NOSIZE);
		m_prev_pos = pos;
	}

	CDialogEx::OnMouseMove(nFlags, point);
}
