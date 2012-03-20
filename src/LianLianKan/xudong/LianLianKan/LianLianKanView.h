// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// LianLianKanView.h : CLianLianKanView ��Ľӿ�
//

#pragma once

#define ONE_WIDTH 110
#define ONE_HEIGHT 170
#define BKCOLOR RGB(128, 128, 128)
#define BLANK_STATE -1


class CLianLianKanView : public CView
{
protected: // �������л�����
	CLianLianKanView();
	DECLARE_DYNCREATE(CLianLianKanView)

// ����
public:
	CLianLianKanDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
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
	bool PointToPointByLine(CPoint pt1, CPoint pt2); // ���������ͬһֱ���ϵĽڵ��Ƿ������ͨ

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // LianLianKanView.cpp �еĵ��԰汾
inline CLianLianKanDoc* CLianLianKanView::GetDocument() const
   { return reinterpret_cast<CLianLianKanDoc*>(m_pDocument); }
#endif

