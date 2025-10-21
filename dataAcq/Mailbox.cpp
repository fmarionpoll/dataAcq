#include "StdAfx.h"
#include "Mailbox.h"

static std::string WUtf16ToUtf8(const std::wstring& w)
{
    if (w.empty()) return {};
    int n = WideCharToMultiByte(CP_UTF8, 0, w.c_str(), (int)w.size(), nullptr, 0, nullptr, nullptr);
    std::string s(n, '\0');
    WideCharToMultiByte(CP_UTF8, 0, w.c_str(), (int)w.size(), &s[0], n, nullptr, nullptr);
    return s;
}

static std::wstring NowIso8601Z()
{
    SYSTEMTIME st; GetSystemTime(&st);
    wchar_t buf[32];
    swprintf(buf, 32, L"%04u-%02u-%02uT%02u:%02u:%02uZ",
        st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
    return buf;
}

std::wstring BuildSessionDir(const std::wstring& sessionUuid)
{
    PWSTR docs = nullptr;
    if (FAILED(SHGetKnownFolderPath(FOLDERID_Documents, 0, NULL, &docs)))
        return L".\\";
    std::wstring base = docs;
    CoTaskMemFree(docs);
    SYSTEMTIME st; GetLocalTime(&st);
    wchar_t y[8], d[16];
    swprintf(y, 8, L"%04u", st.wYear);
    swprintf(d, 16, L"%04u-%02u-%02u", st.wYear, st.wMonth, st.wDay);
    std::wstring dir = base + L"\\dbwave\\acquisition\\" + y + L"\\" + d + L"\\session-" + sessionUuid + L"\\";
    SHCreateDirectoryExW(NULL, dir.c_str(), NULL);
    return dir;
}

std::wstring ManifestPath(const std::wstring& sessionUuid)
{
    return BuildSessionDir(sessionUuid) + L"manifest.txt";
}

std::wstring DiaryPath(const std::wstring& sessionUuid)
{
    return BuildSessionDir(sessionUuid) + L"diary.txt";
}

ScopedManifestMutex::ScopedManifestMutex(const std::wstring& sessionUuid)
{
    const std::wstring name = L"Global\\dbwave_manifest_" + sessionUuid;
    h_ = CreateMutexW(nullptr, FALSE, name.c_str());
    if (h_)
    {
        DWORD rc = WaitForSingleObject(h_, INFINITE);
        acquired_ = (rc == WAIT_OBJECT_0 || rc == WAIT_ABANDONED);
    }
}

ScopedManifestMutex::~ScopedManifestMutex()
{
    if (h_) { ReleaseMutex(h_); CloseHandle(h_); }
}

static bool WriteAll(HANDLE h, const void* buf, DWORD len)
{
    DWORD wr = 0; return WriteFile(h, buf, len, &wr, nullptr) && wr == len;
}

bool AppendManifestLine(const std::wstring& sessionUuid, const std::wstring& absolutePathUtf16)
{
    ScopedManifestMutex lock(sessionUuid);
    if (!lock.acquired()) return false;

    const std::wstring path = ManifestPath(sessionUuid);
    HANDLE h = CreateFileW(path.c_str(), FILE_APPEND_DATA | SYNCHRONIZE, 0, nullptr,
        OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH, nullptr);
    if (h == INVALID_HANDLE_VALUE) return false;

    std::string u8 = WUtf16ToUtf8(absolutePathUtf16);
    const char crlf[] = "\r\n";
    bool ok = WriteAll(h, u8.data(), (DWORD)u8.size()) && WriteAll(h, crlf, 2);
    FlushFileBuffers(h); CloseHandle(h);
    return ok;
}

bool AppendDiaryLine(const std::wstring& sessionUuid, const std::wstring& textUtf16)
{
    const std::wstring path = DiaryPath(sessionUuid);
    HANDLE h = CreateFileW(path.c_str(), FILE_APPEND_DATA, FILE_SHARE_READ, nullptr,
        OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH, nullptr);
    if (h == INVALID_HANDLE_VALUE) return false;

    std::wstring line = NowIso8601Z() + L" " + textUtf16 + L"\r\n";
    std::string u8 = WUtf16ToUtf8(line);
    bool ok = WriteAll(h, u8.data(), (DWORD)u8.size());
    FlushFileBuffers(h); CloseHandle(h);
    return ok;
}


