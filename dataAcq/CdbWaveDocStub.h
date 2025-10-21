#pragma once

class AcqDataDoc; // forward decl

class CdbWaveDoc : public CDocument
{
	DECLARE_DYNCREATE(CdbWaveDoc)
public:
	CdbWaveDoc() noexcept {}
	AcqDataDoc* open_current_data_file() { return nullptr; }
protected:
	DECLARE_MESSAGE_MAP()
};
