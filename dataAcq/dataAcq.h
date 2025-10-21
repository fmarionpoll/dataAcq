#pragma once

#include "resource.h"

class CdataAcqApp : public CWinApp
{
public:
    CdataAcqApp() noexcept {}
    BOOL InitInstance() override;
    int ExitInstance() override;
protected:
    DECLARE_MESSAGE_MAP()
};

extern CdataAcqApp theApp;


