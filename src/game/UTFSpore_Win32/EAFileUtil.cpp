// src/game/UTFSpore_Win32/EAFileUtil.cpp -- migrated from slice(s) s00931460 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EAFileUtil.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/IO/FileStream.h"

// unnamed retail callees and globals (address in the comment)
extern wchar_t gTempPath[];   // 0x01668f28 cached temp path (empty until first use)
#include <windows.h>
#include <string.h>
#include <wchar.h>
#include <direct.h>
#include <sys/stat.h>

// ---- items of slice s00931460 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct FixedPathString {
    wchar_t* mpBegin;      // +0x00
    wchar_t* mpEnd;        // +0x04
    wchar_t* mpCapacity;   // +0x08
    int      mAllocPad;    // +0x0c
    wchar_t* mpFixed;      // +0x10  the in-object buffer
    wchar_t  mBuffer[260]; // +0x14

    FixedPathString() {
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + 260;
        mpFixed = mBuffer;
        mBuffer[0] = 0;
    }
    void assign(const wchar_t* b, const wchar_t* e);           // 0x0088c3d0
    void make_lower();                                         // 0x005e8e80
    void erase(unsigned pos, unsigned n);                      // 0x008e3a70
    void DeallocateSelf() {
        wchar_t* b = mpBegin;
        if ((int)((int)mpCapacity - (int)b & 0xfffffffeU) > 2 && b && b != mpFixed)
            operator delete[](b);
    }
};
bool operator==(const FixedPathString& s, const wchar_t* p);   // 0x006ab760
static __forceinline int StrLenDo(const wchar_t* s) { return (int)wcslen(s); }
extern wchar_t gTempPath[];   // 0x01668f28 cached temp path (empty until first use)
bool EnsureTrailingPathSeparator(wchar_t* path, int len);
// ---- items of slice s00931460 end

// @ 0x00931fa0
namespace EA {
namespace IO {
namespace File {
bool Exists(wchar_t const * path)
{
    if (path && *path) {
        DWORD a = GetFileAttributesW(path);
        if (a != 0xffffffff && (a & 0x10) == 0)
            return true;
        return false;
    }
    return false;
}
}
}
}  // namespace EA::IO::File

// @ 0x00931fd0
namespace EA {
namespace IO {
namespace File {
bool Remove(wchar_t const * path)
{
    return DeleteFileW(path) != 0;
}
}
}
}  // namespace EA::IO::File

// @ 0x00931ff0
namespace EA {
namespace IO {
namespace File {
bool Move(wchar_t const * from, wchar_t const * to, bool overwrite)
{
    if (!overwrite && to && *to) {
        DWORD a = GetFileAttributesW(to);
        if (a != 0xffffffff && (a & 0x10) == 0)
            return false;
    }
    return MoveFileExW(from, to, 3) != 0;
}
}
}
}  // namespace EA::IO::File

// @ 0x00932030
namespace File {
bool Copy(const wchar_t* from, const wchar_t* to, bool overwrite)
{
    return CopyFileW(from, to, overwrite == 0) != 0;
}
}  // namespace File

// @ 0x00932060
namespace EA {
namespace IO {
namespace File {
unsigned int GetSize(wchar_t const * path)
{
    WIN32_FIND_DATAW fd;
    DWORD size = 0xffffffff;
    HANDLE h = FindFirstFileW(path, &fd);
    if (h != INVALID_HANDLE_VALUE) {
        size = fd.nFileSizeLow;
        FindClose(h);
    }
    return size;
}
}
}
}  // namespace EA::IO::File

// @ 0x009320a0
namespace EA {
namespace IO {
namespace File {
bool SetAttributes(wchar_t const * path, int mask, bool set)
{
    DWORD orig = GetFileAttributesW(path);
    DWORD a = orig;
    if (mask & 2) {
        if (set)
            a &= 0xfffffffe;
        else
            a |= 1;
    }
    if (mask & 8)
        return false;
    if (mask & 0x10)
        return false;
    if (mask & 0x20) {
        if (set)
            a |= 0x20;
        else
            a &= 0xffffffdf;
    }
    if (mask & 0x40) {
        if (set)
            a |= 2;
        else
            a &= 0xfffffffd;
    }
    if (mask & 0x80) {
        if (set)
            a |= 4;
        else
            a &= 0xfffffffb;
    }
    if (a == orig)
        return true;
    return SetFileAttributesW(path, a) != 0;
}
}
}
}  // namespace EA::IO::File

// @ 0x00932130
namespace File {
int64_t GetTime(const wchar_t* path, int type)
{
    struct _stat64i32 st;
    if (_wstat64i32(path, &st) == 0) {
        if (type == 1)
            return st.st_ctime;
        if (type == 2)
            return st.st_mtime;
        if (type == 4)
            return st.st_atime;
    }
    return 0;
}
}  // namespace File

// @ 0x00932190
int GetTempDirectoryPath(wchar_t* out)
{
    if (gTempPath[0]) {
        const wchar_t* s = gTempPath;
        wchar_t* d = out;
        do {
        } while ((*d++ = *s++) != 0);
        return (int)wcslen(out);
    }
    DWORD n = GetTempPathW(0x100, out);
    if (n != 0) {
        n = GetLongPathNameW(out, out, 0x100);
        if (EnsureTrailingPathSeparator(out, -1))
            n = n + 1;
        return n;
    }
    return -1;
}

// @ 0x00932220
namespace EA {
namespace IO {
int GetDriveSerialNumber(wchar_t const * path, wchar_t * out)
{
    wchar_t volume[260];
    DWORD serial;
    DWORD flags;
    if (GetVolumePathNameW(path, volume, 260) &&
        GetVolumeInformationW(volume, 0, 0, &serial, 0, &flags, 0, 0)) {
        wsprintfW(out, L"%04X-%04X", serial >> 16, serial & 0xffff);
        return 10;
    }
    *out = 0;
    return 0;
}
}
}  // namespace EA::IO

// @ 0x009322b0
namespace Directory {
bool Exists(const wchar_t* path)
{
    if (path && *path) {
        DWORD a = GetFileAttributesW(path);
        if (a != 0xffffffff && (a & 0x10))
            return true;
        return false;
    }
    return false;
}
}  // namespace Directory

// @ 0x009322e0
bool DirectoryCreate(const wchar_t* path)
{
    wchar_t tmp[260];
    if (*path != 0) {
        unsigned last = path[wcslen(path) - 1];
        if (last == '\\' || last == '/' || last == ':') {
            tmp[wcslen(path)] = 0;
            return CreateDirectoryW(path, 0) != 0;
        }
        return CreateDirectoryW(path, 0) != 0;
    }
    return false;
}

// @ 0x00932370
namespace EA {
namespace IO {
namespace Directory {
int GetCurrentWorkingDirectory(wchar_t * out)
{
    if (_wgetcwd(out, 0xff)) {
        EnsureTrailingPathSeparator(out, -1);
        return StrLenDo(out);
    }
    return -1;
}
}
}
}  // namespace EA::IO::Directory
