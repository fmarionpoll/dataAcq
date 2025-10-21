#pragma once

class CMainFrame : public CFrameWnd
{
    DECLARE_DYNAMIC(CMainFrame)
public:
    CMainFrame() noexcept {}
    BOOL PreCreateWindow(CREATESTRUCT& cs) override;
protected:
    DECLARE_MESSAGE_MAP()
};


