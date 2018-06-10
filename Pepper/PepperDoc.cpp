#include "stdafx.h"
#include "PepperDoc.h"

IMPLEMENT_DYNCREATE(CPepperDoc, CDocument)

BEGIN_MESSAGE_MAP(CPepperDoc, CDocument)
END_MESSAGE_MAP()

CPepperDoc::CPepperDoc()
{
	m_mapLibpeErrors = {
		{ CALL_LOADPE_FIRST, L"CALL_LOADPE_FIRST" },
	{ FILE_OPEN_FAILED, L"FILE_OPEN_FAILED" },
	{ FILE_SIZE_TOO_SMALL, L"FILE_SIZE_TOO_SMALL" },
	{ FILE_CREATE_FILE_MAPPING_FAILED, L"FILE_CREATE_FILE_MAPPING_FAILED" },
	{ FILE_MAP_VIEW_OF_FILE_FAILED, L"FILE_MAP_VIEW_OF_FILE_FAILED" },
	{ IMAGE_TYPE_UNSUPPORTED, L"IMAGE_TYPE_UNSUPPORTED" },
	{ IMAGE_DOS_SIGNATURE_MISMATCH, L"IMAGE_DOS_SIGNATURE_MISMATCH" },
	{ IMAGE_HAS_NO_DOS_HEADER, L"IMAGE_HAS_NO_DOS_HEADER" },
	{ IMAGE_HAS_NO_RICH_HEADER, L"IMAGE_HAS_NO_RICH_HEADER" },
	{ IMAGE_NT_SIGNATURE_MISMATCH, L"IMAGE_NT_SIGNATURE_MISMATCH" },
	{ IMAGE_HAS_NO_NT_HEADER, L"IMAGE_HAS_NO_NT_HEADER" },
	{ IMAGE_HAS_NO_FILE_HEADER, L"IMAGE_HAS_NO_FILE_HEADER" },
	{ IMAGE_HAS_NO_OPTIONAL_HEADER, L"IMAGE_HAS_NO_OPTIONAL_HEADER" },
	{ IMAGE_HAS_NO_DATA_DIRECTORIES, L"IMAGE_HAS_NO_DATA_DIRECTORIES" },
	{ IMAGE_HAS_NO_SECTIONS, L"IMAGE_HAS_NO_SECTIONS" },
	{ IMAGE_HAS_NO_EXPORT_DIR, L"IMAGE_HAS_NO_EXPORT_DIR" },
	{ IMAGE_HAS_NO_IMPORT_DIR, L"IMAGE_HAS_NO_IMPORT_DIR" },
	{ IMAGE_HAS_NO_RESOURCE_DIR, L"IMAGE_HAS_NO_RESOURCE_DIR" },
	{ IMAGE_HAS_NO_EXCEPTION_DIR, L"IMAGE_HAS_NO_EXCEPTION_DIR" },
	{ IMAGE_HAS_NO_SECURITY_DIR, L"IMAGE_HAS_NO_SECURITY_DIR" },
	{ IMAGE_HAS_NO_BASERELOC_DIR, L"IMAGE_HAS_NO_BASERELOC_DIR" },
	{ IMAGE_HAS_NO_DEBUG_DIR, L"IMAGE_HAS_NO_DEBUG_DIR" },
	{ IMAGE_HAS_NO_ARCHITECTURE_DIR, L"IMAGE_HAS_NO_ARCHITECTURE_DIR" },
	{ IMAGE_HAS_NO_GLOBALPTR_DIR, L"IMAGE_HAS_NO_GLOBALPTR_DIR" },
	{ IMAGE_HAS_NO_TLS_DIR, L"IMAGE_HAS_NO_TLS_DIR" },
	{ IMAGE_HAS_NO_LOADCONFIG_DIR, L"IMAGE_HAS_NO_LOADCONFIG_DIR" },
	{ IMAGE_HAS_NO_BOUNDIMPORT_DIR, L"IMAGE_HAS_NO_BOUNDIMPORT_DIR" },
	{ IMAGE_HAS_NO_IAT_DIR, L"IMAGE_HAS_NO_IAT_DIR" },
	{ IMAGE_HAS_NO_DELAY_IMPORT_DIR, L"IMAGE_HAS_NO_DELAY_IMPORT_DIR" },
	{ IMAGE_HAS_NO_COMDESCRIPTOR_DIR, L"IMAGE_HAS_NO_COMDESCRIPTOR_DIR" }
	};
}

BOOL CPepperDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (Getlibpe(&m_pLibpe) != S_OK)
	{
		MessageBoxW(0, L"Getlibpe() failed", L"Error", MB_ICONERROR);
		return FALSE;
	}

	HRESULT hr;
	if ((hr = m_pLibpe->LoadPe(lpszPathName)) != S_OK)
	{
		WCHAR str[MAX_PATH] { };
		std::wstring strError { };
		for (auto& i : m_mapLibpeErrors)
			if (i.first == hr)
				strError = i.second;
	
		swprintf_s(str, L"File load failed with error code: 0x0%X\n%s", hr, strError.c_str());

		MessageBoxW(0, str, L"File Load Failed", MB_ICONERROR);
		return FALSE;
	}

	UpdateAllViews(0);

	return TRUE;
}

void CPepperDoc::OnCloseDocument()
{
	if (m_pLibpe)
		m_pLibpe->Release();

	CDocument::OnCloseDocument();
}