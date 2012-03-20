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

// LianLianKanView.h : CLianLianKanView 类的接口
//

#pragma once

#define ONE_WIDTH 110
#define ONE_HEIGHT 170
#define BKCOLOR RGB(128, 128, 128)
#define BLANK_STATE -1


class CLianLianKanView : public CView
{
protected: // 仅从序列化创建
	CLianLianKanView();
	DECLARE_DYNCREATE(CLianLianKanView)

// 特性
public:
	CLianLianKanDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CLianLianKanView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CDC m_memDC, m_memPicDC;  
	CBitmap m_memBitMap, m_memPicBitMap;  

	int m_nCols, m_nRows;
	int m_nX1, m_nY1;

	bool IsLink(int x1, int y1, int x2, int y2);
	bool IsWin();
	bool X1LinkX2(int x, int y1, int y2);
	bool Y1LinkY2(int y, int x1, int x2);
	bool OneCorner(CPoint pt1, CPoint pt2);
	bool TwoCorner(CPoint pt1, CPoint pt2);


private:
	int *m_map;

	bool PointIsBlank(CPoint pt);
	bool PointToPointByLine(CPoint pt1, CPoint pt2); // 检测两个在同一直线上的节点是否可以连通

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	int ResetForNewGame(void);
	void GameDraw(CDC *pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // LianLianKanView.cpp 中的调试版本
inline CLianLianKanDoc* CLianLianKanView::GetDocument() const
   { return reinterpret_cast<CLianLianKanDoc*>(m_pDocument); }
#endif

