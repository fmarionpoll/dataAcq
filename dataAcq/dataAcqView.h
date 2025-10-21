#pragma once

#include "resource.h"

class CdataAcqView : public CFormView
{
    DECLARE_DYNCREATE(CdataAcqView)
public:
    enum { IDD = IDD_FORMVIEW };
    CdataAcqView() noexcept : CFormView(IDD) {}
protected:
    void DoDataExchange(CDataExchange* pDX) override { CFormView::DoDataExchange(pDX); }
    void OnInitialUpdate() override { CFormView::OnInitialUpdate(); }
    DECLARE_MESSAGE_MAP()
};


