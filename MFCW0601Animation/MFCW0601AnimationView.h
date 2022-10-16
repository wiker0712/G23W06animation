
// MFCW0601AnimationView.h: CMFCW0601AnimationView 클래스의 인터페이스
//

#pragma once


class CMFCW0601AnimationView : public CView
{
protected:
	void DrawBitmap(CDC* pDC);

protected: // serialization에서만 만들어집니다.
	CMFCW0601AnimationView() noexcept;
	DECLARE_DYNCREATE(CMFCW0601AnimationView)

// 특성입니다.
public:
	CMFCW0601AnimationDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMFCW0601AnimationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // MFCW0601AnimationView.cpp의 디버그 버전
inline CMFCW0601AnimationDoc* CMFCW0601AnimationView::GetDocument() const
   { return reinterpret_cast<CMFCW0601AnimationDoc*>(m_pDocument); }
#endif

