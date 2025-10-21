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
    ON_COMMAND(ID_APP_EXIT, CWinApp::OnAppExit)
END_MESSAGE_MAP()

BOOL CdataAcqApp::InitInstance()
{
    CWinApp::InitInstance();
    AfxEnableControlContainer();

    // Register document template (SDI)
    CSingleDocTemplate* pDocTemplate;
    pDocTemplate = new CSingleDocTemplate(
        IDR_MAINFRAME,
        RUNTIME_CLASS(CdataAcqDoc),
        RUNTIME_CLASS(CMainFrame),
        RUNTIME_CLASS(CdataAcqView));
    if (!pDocTemplate)
        return FALSE;
    AddDocTemplate(pDocTemplate);

    // Create main window and first document
    CCommandLineInfo cmdInfo;
    ParseCommandLine(cmdInfo);
    if (!ProcessShellCommand(cmdInfo))
        return FALSE;

    m_pMainWnd->ShowWindow(SW_SHOW);
    m_pMainWnd->UpdateWindow();
    return TRUE;
}

int CdataAcqApp::ExitInstance()
{
    return CWinApp::ExitInstance();
}


