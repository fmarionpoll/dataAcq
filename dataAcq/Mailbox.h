#pragma once

#include <windows.h>
#include <shlobj.h>
#include <string>

// Session folder helpers
std::wstring BuildSessionDir(const std::wstring& sessionUuid);
std::wstring ManifestPath(const std::wstring& sessionUuid);
std::wstring DiaryPath(const std::wstring& sessionUuid);

// Append-only writers
bool AppendManifestLine(const std::wstring& sessionUuid, const std::wstring& absolutePathUtf16);
bool AppendDiaryLine(const std::wstring& sessionUuid, const std::wstring& textUtf16);

// Named mutex to serialize manifest edits across processes
class ScopedManifestMutex {
public:
    explicit ScopedManifestMutex(const std::wstring& sessionUuid);
    ~ScopedManifestMutex();
    bool acquired() const { return acquired_; }
private:
    HANDLE h_ { nullptr };
    bool acquired_ { false };
};


