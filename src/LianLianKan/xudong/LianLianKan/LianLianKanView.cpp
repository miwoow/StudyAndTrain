// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// LianLianKanView.cpp : CLianLianKanView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "LianLianKan.h"
#endif

#include "LianLianKanDoc.h"
#include "LianLianKanView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLianLianKanView

IMPLEMENT_DYNCREATE(CLianLianKanView, CView)

BEGIN_MESSAGE_MAP(CLianLianKanView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CLianLianKanView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CLianLianKanView 构造/析构

CLianLianKanView::CLianLianKanView()
{
	// TODO: 在此处添加构造代码
	m_nCols = 12;
	m_nRows = 4;
	m_map = new int[m_nCols * m_nRows];
	m_nX1 = m_nY1 = BLANK_STATE;
}

CLianLianKanView::~CLianLianKanView()
{
	delete[] m_map;
}

BOOL CLianLianKanView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	
	return CView::PreCreateWindow(cs);
}

// CLianLianKanView 绘制

void CLianLianKanView::OnDraw(CDC* pDC)
{
	CLianLianKanDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	if (m_memDC != NULL)
	{
		GameDraw(&m_memDC);

		pDC->BitBlt(0, 0, m_nCols * ONE_WIDTH, m_nRows * ONE_HEIGHT, &m_memDC, 0, 0, SRCCOPY);
	}
}

void CLianLianKanView::GameDraw(CDC *pDC)
{
	pDC->FillSolidRect(0, 0, m_nCols * ONE_WIDTH, m_nRows * ONE_HEIGHT, BKCOLOR);

	for (int i=0; i< m_nRows; i++)
	{
		for (int j=0; j< m_nCols; j++)
		{
			if (m_map[i*m_nCols+j] == BLANK_STATE)
			{
				continue;
			}

			pDC->BitBlt(j*ONE_WIDTH, i*ONE_HEIGHT, ONE_WIDTH, ONE_HEIGHT, &m_memPicDC, m_map[i*m_nCols +j] * ONE_WIDTH, 0, SRCCOPY);
		}
	}
}


// CLianLianKanView 打印


void CLianLianKanView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CLianLianKanView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CLianLianKanView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CLianLianKanView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CLianLianKanView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CLianLianKanView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CLianLianKanView 诊断

#ifdef _DEBUG
void CLianLianKanView::AssertValid() const
{
	CView::AssertValid();
}

void CLianLianKanView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLianLianKanDoc* CLianLianKanView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLianLianKanDoc)));
	return (CLianLianKanDoc*)m_pDocument;
}
#endif //_DEBUG


// CLianLianKanView 消息处理程序


void CLianLianKanView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	CDC *pWndDC = GetDC();

	m_memPicDC.CreateCompatibleDC(pWndDC);
	m_memPicBitMap.LoadBitmap(IDB_BITMAP1);
	m_memPicDC.SelectObject(m_memPicBitMap);

	m_memDC.CreateCompatibleDC(pWndDC);
	m_memBitMap.CreateCompatibleBitmap(pWndDC, m_nCols * ONE_WIDTH, m_nRows * ONE_HEIGHT);
	m_memDC.SelectObject(m_memBitMap);

	ResetForNewGame();
}


int CLianLianKanView::ResetForNewGame(void)
{
	for (int i=0; i< m_nRows * m_nCols; i++)
	{
		m_map[i] = BLANK_STATE;
	}
	srand(time(NULL));
	CDWordArray tmpMap;
	for (int i=0; i< m_nRows * m_nCols / 4; i++)
	{
		for (int j=0; j< 4; j++)
		{
			tmpMap.Add(j);
		}
	}

	for (int i=0; i< m_nRows * m_nCols; i++)
	{
		int nIndex = (int(rand() * 0.1 + rand() * 0.01 + rand())) % tmpMap.GetSize();
		m_map[i] = tmpMap[nIndex];
		tmpMap.RemoveAt(nIndex);
	}

	Invalidate(TRUE);
	return 0;
}


void CLianLianKanView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	int x = point.x / ONE_WIDTH + (point.x % ONE_WIDTH ? 1 : 0) - 1;
	int y = point.y / ONE_HEIGHT + (point.y % ONE_HEIGHT ? 1 : 0) -1;

	if (x<m_nCols && y<m_nRows && m_map[y*m_nCols + x] != BLANK_STATE)
	{
		if (m_nX1 == BLANK_STATE)
		{
			m_nX1 = x;
			m_nY1 = y;
			
			CDC *pWndDC = GetDC();
			CPen myPen;
			CPen *pOldPen;
			myPen.CreatePen(PS_SOLID, 4, RGB(255,0,0));
			pOldPen = pWndDC->SelectObject(&myPen);

			pWndDC->MoveTo(x*ONE_WIDTH, y*ONE_HEIGHT);
			pWndDC->LineTo(x*ONE_WIDTH, (y+1)*ONE_HEIGHT);
			pWndDC->LineTo((x+1)*ONE_WIDTH, (y+1)*ONE_HEIGHT);
			pWndDC->LineTo((x+1)*ONE_WIDTH, y*ONE_HEIGHT);
			pWndDC->SelectObject(pOldPen);
		} else {
			if ((m_nX1 != x || m_nY1 != y) && m_map[m_nY1*m_nCols + m_nX1] == m_map[y*m_nCols + x])
			{
				if (IsLink(m_nX1, m_nY1, x, y))
				{
					m_map[m_nY1*m_nCols + m_nX1] = BLANK_STATE;
					m_map[y*m_nCols + x] = BLANK_STATE;
				}
			}
			m_nX1 = m_nY1 = BLANK_STATE;
			Invalidate(FALSE);

			if (IsWin())
			{
				MessageBox(_T("恭喜您，您已经成功完成了！"), _T("成功"), MB_OK);
				ResetForNewGame();
			}
		}
	}

	CView::OnLButtonDown(nFlags, point);
}

bool CLianLianKanView::IsWin()
{
	bool m_bResult = true;
	for (int i=0; i<m_nCols*m_nRows; i++)
	{
		if (m_map[i] != BLANK_STATE)
		{
			m_bResult = false;
			break;
		}
	}
	return m_bResult;
}

bool CLianLianKanView::IsLink(int x1, int y1, int x2, int y2)
{
	// 判断直连
	if (PointToPointByLine(CPoint(x1, y1), CPoint(x2, y2)))
	{
		return true;
	}
	// 判断单个拐点
	if (OneCorner(CPoint(x1, y1), CPoint(x2, y2)))
	{
		return true;
	}

	// 判断两个拐点
	if (TwoCorner(CPoint(x1, y1), CPoint(x2, y2)))
	{
		return true;
	}

	return false;
}

/*
 * X和Y两个方向上的延伸。
 * 首先判断X方向上的延伸。
 * 然后再判断Y方向上的延伸。
 * 每次延伸又一点为分界点，分为左右两个方向
 *
 */
bool CLianLianKanView::TwoCorner(CPoint pt1, CPoint pt2)
{
	// 判断边界
	// 可以联通右边界
	if ((PointToPointByLine(pt1, CPoint(m_nCols-1, pt1.y)) && PointIsBlank(CPoint(m_nCols-1, pt1.y)) || pt1.x == m_nCols-1)
		&& (PointToPointByLine(pt2, CPoint(m_nCols-1, pt2.y)) && PointIsBlank(CPoint(m_nCols-1, pt2.y)) || pt2.x == m_nCols-1))
	{
		return true;
	}
	// 可以联通左边界
	if ((PointToPointByLine(pt1, CPoint(0, pt1.y)) && PointIsBlank(CPoint(0, pt1.y)) || pt1.x == 0)
		&& (PointToPointByLine(pt2, CPoint(0, pt2.y)) && PointIsBlank(CPoint(0, pt2.y)) || pt2.x == 0))
	{
		return true;
	}
	// 可以联通上边界
	if ((PointToPointByLine(pt1, CPoint(pt1.x, 0)) && PointIsBlank(CPoint(pt1.x,0)) || pt1.y == 0)
		&& (PointToPointByLine(pt2, CPoint(pt2.x, 0)) && PointIsBlank(CPoint(pt2.x, 0)) || pt2.y == 0))
	{
		return true;
	}
	// 可以联通下边界
	if ((PointToPointByLine(pt1, CPoint(pt1.x, m_nRows-1)) && PointIsBlank(CPoint(pt1.x, m_nRows-1)) || pt1.x == m_nRows-1)
		&& (PointToPointByLine(pt2, CPoint(pt2.x, m_nRows-1)) && PointIsBlank(CPoint(pt2.x, m_nRows-1)) || pt2.x == m_nRows-1))
	{
		return true;
	}

	// 以pt1为标准X轴方向延伸
	// 向右扩展
	for (int i=pt1.x+1; i<m_nCols; i++)
	{
		if (PointIsBlank(CPoint(i, pt1.y)) && PointIsBlank(CPoint(i, pt2.y))
			&& PointToPointByLine(CPoint(i, pt1.y), CPoint(i, pt2.y))
			&& PointToPointByLine(CPoint(i, pt2.y), pt2))
		{
			return true;
		}
	}
	// 向左扩展
	for (int i=pt1.x-1; i>=0; i--)
	{
		if (PointIsBlank(CPoint(i, pt1.y)) && PointIsBlank(CPoint(i, pt2.y))
			&& PointToPointByLine(CPoint(i, pt1.y), CPoint(i, pt2.y))
			&& PointToPointByLine(CPoint(i, pt2.y), pt2))
		{
			return true;
		}
	}
	// 以pt1为准，向Y方向扩展
	// 向上扩展
	for (int i=pt1.y-1; i>=0; i--)
	{
		if (PointIsBlank(CPoint(pt1.x, i)) && PointIsBlank(CPoint(pt2.x, i))
			&& PointToPointByLine(CPoint(pt1.x, i), CPoint(pt2.x, i))
			&& PointToPointByLine(CPoint(pt2.x, i), pt2))
		{
			return true;
		}
	}
	// 向下扩展
	for (int i=pt1.y+1; i<m_nCols; i++)
	{
		if (PointIsBlank(CPoint(pt1.x, i)) && PointIsBlank(CPoint(pt2.x, i))
			&& PointToPointByLine(CPoint(pt1.x, i), CPoint(pt2.x, i))
			&& PointToPointByLine(CPoint(pt2.x, i), pt2))
		{
			return true;
		}
	}
	return false;
}


bool CLianLianKanView::PointIsBlank(CPoint pt)
{
	return m_map[pt.y*m_nCols+pt.x] == BLANK_STATE;
}

bool CLianLianKanView::OneCorner(CPoint pt1, CPoint pt2)
{
	CPoint m_CornerPoint1, m_CornerPoint2;

	m_CornerPoint1.x = pt1.x;
	m_CornerPoint1.y = pt2.y;
	m_CornerPoint2.x = pt2.x;
	m_CornerPoint2.y = pt1.y;

	if (PointIsBlank(m_CornerPoint1) && PointToPointByLine(m_CornerPoint1, pt1) && PointToPointByLine(m_CornerPoint1, pt2))
	{
		return true;
	}
	if (PointIsBlank(m_CornerPoint2) && PointToPointByLine(m_CornerPoint2, pt1) && PointToPointByLine(m_CornerPoint2, pt2))
	{
		return true;
	}

	return false;
}

bool CLianLianKanView::PointToPointByLine(CPoint pt1, CPoint pt2)
{
	if (pt1.x == pt2.x)
	{
		if (X1LinkX2(pt1.x, pt1.y, pt2.y))
		{
			return true;
		}
	} else if (pt1.y == pt2.y)
	{
		if (Y1LinkY2(pt1.y, pt1.x, pt2.x))
		{
			return true;
		}
	}
	return false;
}


bool CLianLianKanView::X1LinkX2(int x, int y1, int y2)
{
	int tmp;

	if (y1>y2)
	{
		tmp = y2;
		y2 = y1;
		y1 = tmp;
	}

	for (int i=y1+1; i<y2; i++)
	{
		if (m_map[i*m_nCols+x] != BLANK_STATE)
		{
			return false;
		}
	}
	return true;
}

bool CLianLianKanView::Y1LinkY2(int y, int x1, int x2)
{
	int tmp;

	if (x1>x2)
	{
		tmp = x2;
		x2 = x1;
		x1 = tmp;
	}

	for (int i=x1+1; i<x2; i++)
	{
		if (m_map[y*m_nCols + i] != BLANK_STATE)
		{
			return false;
		}
	}
	return true;
}