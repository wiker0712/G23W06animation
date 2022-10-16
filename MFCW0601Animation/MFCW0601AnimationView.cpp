
// MFCW0601AnimationView.cpp: CMFCW0601AnimationView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCW0601Animation.h"
#endif

#include "MFCW0601AnimationDoc.h"
#include "MFCW0601AnimationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCW0601AnimationView

IMPLEMENT_DYNCREATE(CMFCW0601AnimationView, CView)

BEGIN_MESSAGE_MAP(CMFCW0601AnimationView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)

	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CMFCW0601AnimationView 생성/소멸

CMFCW0601AnimationView::CMFCW0601AnimationView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFCW0601AnimationView::~CMFCW0601AnimationView()
{
}

BOOL CMFCW0601AnimationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCW0601AnimationView 그리기

void CMFCW0601AnimationView::OnDraw(CDC* pDC)
{
	CMFCW0601AnimationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);

	CRect rect;
	GetClientRect(&rect);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());

	CBitmap* old = memDC.SelectObject(&bmp);

	DrawBitmap(&memDC);

	pDC->BitBlt(0, 0,
		rect.Width(), rect.Height(),
		&memDC,
		0, 0,
		SRCCOPY);

	memDC.SelectObject(old);
}


// CMFCW0601AnimationView 인쇄

BOOL CMFCW0601AnimationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCW0601AnimationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCW0601AnimationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCW0601AnimationView 진단

#ifdef _DEBUG
void CMFCW0601AnimationView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCW0601AnimationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCW0601AnimationDoc* CMFCW0601AnimationView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCW0601AnimationDoc)));
	return (CMFCW0601AnimationDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCW0601AnimationView 메시지 처리기
void CMFCW0601AnimationView::DrawBitmap(CDC* pDC)
{
	static int nAnimate = 0;

	CDC bmpDC;
	bmpDC.CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.LoadBitmapW(IDB_BACK);
	BITMAP info;
	bmp.GetBitmap(&info);

	CBitmap* oldBmp = bmpDC.SelectObject(&bmp);

	pDC->BitBlt(0, 0,
		info.bmWidth, info.bmHeight,
		&bmpDC,
		0, 0,
		SRCCOPY);

	bmpDC.SelectObject(oldBmp);

	//------------------------------------
	CDC maskDC;
	maskDC.CreateCompatibleDC(pDC);
	CBitmap mask;
	mask.LoadBitmapW(IDB_MASK);

	CBitmap* oldMask = maskDC.SelectObject(&mask);

	pDC->BitBlt(300, 300,
		62, 64,
		&maskDC,
		62 * nAnimate, 0,
		SRCAND);

	maskDC.SelectObject(oldMask);

	//-------------------------------------
	CDC aniDC;
	aniDC.CreateCompatibleDC(pDC);
	CBitmap ani;
	ani.LoadBitmapW(IDB_ANI);

	CBitmap* oldAni = aniDC.SelectObject(&ani);

	pDC->BitBlt(300, 300,
		62, 64,
		&aniDC,
		62 * nAnimate, 0,
		SRCPAINT);

	aniDC.SelectObject(oldAni);

	nAnimate = ++nAnimate % 3;
}


void CMFCW0601AnimationView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	SetTimer(0, 200, NULL);
}


void CMFCW0601AnimationView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	Invalidate();

	CView::OnTimer(nIDEvent);
}


void CMFCW0601AnimationView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	KillTimer(0);
}


BOOL CMFCW0601AnimationView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//return CView::OnEraseBkgnd(pDC);
	return TRUE;
}