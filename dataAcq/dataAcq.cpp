#include "StdAfx.h"
#include "dataAcq.h"
#include "MainFrm.h"
#include "dataAcqDoc.h"
#include "dataAcqView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CdataAcqApp theApp;

BEGIN_MESSAGE_MAP(CdataAcqApp, CWinApp)
END_MESSAGE_MAP()

BOOL CdataAcqApp::InitInstance()
{
    CWinApp::InitInstance();
    AfxEnableControlContainer();

    // Create main frame
    auto* pFrame = new CMainFrame;
    if (!pFrame->LoadFrame(IDR_MAINFRAME))
        return FALSE;
    m_pMainWnd = pFrame;

    // Create a document and view
    CCreateContext ctx{};
    ctx.m_pNewViewClass = RUNTIME_CLASS(CdataAcqView);
    ctx.m_pNewDocTemplate = nullptr;
    ctx.m_pLastView = nullptr;
    ctx.m_pCurrentDoc = (CDocument*)RUNTIME_CLASS(CdataAcqDoc)->CreateObject();
    if (!ctx.m_pCurrentDoc)
        return FALSE;
    pFrame->InitialUpdateFrame(ctx.m_pCurrentDoc, TRUE);

    return TRUE;
}

int CdataAcqApp::ExitInstance()
{
    return CWinApp::ExitInstance();
}


