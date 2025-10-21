#pragma once

class CdataAcqDoc : public CDocument
{
    DECLARE_DYNCREATE(CdataAcqDoc)
public:
    CdataAcqDoc() noexcept {}
    BOOL OnNewDocument() override { return CDocument::OnNewDocument(); }
protected:
    DECLARE_MESSAGE_MAP()
};


